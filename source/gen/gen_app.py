#!/usr/bin/env python3

import argparse
import bisect
import csv
import hashlib
import json
import random
import re
import subprocess
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

PAYLOAD_START = 0x08010400
VECTOR_END = 0x08010500
TEXT_START = 0x08010500
TEXT_END = 0x0802E760
RODATA_START = 0x0802E760
RODATA_END = 0x0807E3D8
IMAGE_VMA = PAYLOAD_START
CACHE_VERSION = "disasm-v1"
PAYLOAD_REGIONS = ("vector", "text", "rodata")
NAMED_DATA_REGIONS = ("ram", "mmio")

ASM_RESERVED = {
    "default", "section", "text", "data", "bss", "globl", "global", "set",
    "equ", "word", "short", "byte", "long", "align", "balign", "org",
    "include", "incbin", "macro", "endm", "func", "endfunc", "if", "ifdef",
    "ifndef", "else", "elseif", "endif", "end", "file", "loc", "type",
    "size", "space", "fill", "string", "ascii", "asciz", "zero", "skip",
    "sp", "lr", "pc", "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7",
    "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15",
}
GENERATED_PREFIXES = ("L_", "P_", "fn_", "data_", "rodata_", "sym_", "__app_",
                      "target_text_")
LINKER_SCRIPT_OWNED = {"flash_data_region_start": "the SDK text base"}
BLOB_ANCHORS = ((0x0807E14C, "__app_data_init"),)

BRANCH_MNEMONICS = {
    "bez", "bf", "bhsz", "bhz", "blsz", "blz", "bnez", "bnezad",
    "br", "bsr", "bt", "jmp", "jsr",
}


def die(msg):
    raise SystemExit(msg)


def sha256_file(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


class RangeSet:
    def __init__(self, ranges, label):
        self.label = label
        self.ranges = ranges
        self.starts = [a for a, _ in ranges]

    def __contains__(self, addr):
        i = bisect.bisect_right(self.starts, addr) - 1
        return i >= 0 and addr < self.ranges[i][1]

    def overlaps(self, start, end):
        i = bisect.bisect_right(self.starts, start) - 1
        if i >= 0 and start < self.ranges[i][1]:
            return True
        i += 1
        return i < len(self.ranges) and self.ranges[i][0] < end

    def bytes(self):
        return sum(b - a for a, b in self.ranges)


def load_ranges(path, lo, hi, label):
    path = Path(path)
    if not path.exists():
        die("missing %s map: %s" % (label, path))
    ranges = []
    for lineno, line in enumerate(path.read_text().splitlines(), 1):
        line = line.split("#")[0].strip()
        if not line:
            continue
        parts = line.split()
        if len(parts) < 2:
            die("%s:%d: expected 'start end'" % (path, lineno))
        try:
            start, end = int(parts[0], 16), int(parts[1], 16)
        except ValueError:
            die("%s:%d: malformed range" % (path, lineno))
        if end <= start:
            die("%s:%d: empty range" % (path, lineno))
        if not (lo <= start and end <= hi):
            die("%s:%d: 0x%08X-0x%08X is outside 0x%08X-0x%08X" %
                (path, lineno, start, end, lo, hi))
        if ranges and start < ranges[-1][1]:
            die("%s:%d: ranges overlap or are unsorted" % (path, lineno))
        ranges.append((start, end))
    if not ranges:
        die("%s: no ranges" % path)
    return RangeSet(ranges, label)


def check_map_meta(meta_path, maps):
    meta_path = Path(meta_path)
    if not meta_path.exists():
        return None
    meta = json.loads(meta_path.read_text())
    for key, (path, rangeset) in maps.items():
        entry = meta.get(key, {})
        if entry.get("sha256") and entry["sha256"] != sha256_file(path):
            die("%s hash differs from %s" % (key, meta_path))
        if entry.get("ranges") and entry["ranges"] != len(rangeset.ranges):
            die("%s range count differs from %s" % (key, meta_path))
        if entry.get("bytes") and entry["bytes"] != rangeset.bytes():
            die("%s byte count differs from %s" % (key, meta_path))
    return meta


def ident(name):
    return bool(re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", name))


def sanitize(name):
    s = re.sub(r"[^A-Za-z0-9_]", "_", name)
    s = re.sub(r"_+", "_", s).strip("_")
    if not s:
        s = "sym"
    if s[0].isdigit():
        s = "s_" + s
    return s


def make_unique(name, addr, used):
    s = sanitize(name)
    if s in ASM_RESERVED or s in used or s.startswith(GENERATED_PREFIXES):
        s = "%s_%08X" % (s, addr)
    base = s
    n = 2
    while s in used:
        s = "%s_%d" % (base, n)
        n += 1
    used.add(s)
    return s


def parse_functions(path):
    funcs = []
    with open(path, newline="") as f:
        for row in csv.DictReader(f):
            start = int(row["body_start"], 16)
            end = int(row["body_end"], 16) + 1
            size = int(row["size_bytes"])
            if not (TEXT_START <= start < end <= TEXT_END):
                die("function out of text range: %s %s" % (row["name"], row["body_start"]))
            if size > end - start:
                die("function size exceeds span: %s 0x%X > 0x%X" % (row["name"], size, end - start))
            funcs.append({
                "start": start,
                "end": end,
                "name": row["name"],
                "instructions": int(row["instructions"]),
                "comment": row["comment"],
            })
    funcs.sort(key=lambda f: f["start"])
    prev = VECTOR_END
    for f in funcs:
        if f["start"] < prev:
            die("overlapping function at 0x%08X" % f["start"])
        prev = f["end"]
    funcs[0]["is_first"] = True
    return funcs


def disassemble_one(objdump, image, start, end):
    cmd = [
        str(objdump), "-D", "-b", "binary", "-m", "csky",
        "--adjust-vma=0x%X" % IMAGE_VMA,
        "--start-address=0x%X" % start,
        "--stop-address=0x%X" % end,
        str(image),
    ]
    out = subprocess.run(cmd, check=True, capture_output=True, text=True).stdout
    items = []
    for line in out.splitlines():
        m = re.match(r"^\s*([0-9a-fA-F]+):\s+([0-9a-fA-F]+)\s+(.*?)\s*$", line)
        if not m:
            continue
        addr = int(m.group(1), 16)
        if not (start <= addr < end):
            continue
        raw = m.group(3)
        lit = None
        lm = re.search(r"//\s*0x([0-9a-fA-F]+)", raw)
        if lm:
            lit = int(lm.group(1), 16)
        text = raw.split("//")[0].strip()
        text = re.sub(r"\s+", " ", text)
        if items and items[-1][0] == addr:
            continue
        items.append([addr, len(m.group(2)) // 2, text, lit])
    if not items or items[0][0] != start:
        die("disassembly does not start at 0x%08X" % start)
    for i in range(len(items) - 1):
        items[i][1] = items[i + 1][0] - items[i][0]
    items[-1][1] = end - items[-1][0]
    return items


def load_disassembly(objdump, image, funcs, cache_path):
    key = CACHE_VERSION + ":" + hashlib.sha256(image.read_bytes()).hexdigest()
    key += ":" + hashlib.sha256(
        "".join("%X-%X" % (f["start"], f["end"]) for f in funcs).encode()
    ).hexdigest()
    if cache_path.exists():
        try:
            cached = json.loads(cache_path.read_text())
            if cached.get("key") == key:
                return cached["functions"]
        except (ValueError, KeyError):
            pass

    def work(f):
        f = dict(f)
        f["insns"] = disassemble_one(objdump, image, f["start"], f["end"])
        return f

    with ThreadPoolExecutor(max_workers=16) as pool:
        result = list(pool.map(work, funcs))
    cache_path.parent.mkdir(parents=True, exist_ok=True)
    cache_path.write_text(json.dumps({"key": key, "functions": result}, separators=(",", ":")))
    return result


def load_raw(path):
    raw = set()
    if path and path.exists():
        for line in path.read_text().splitlines():
            line = line.split("#")[0].strip()
            if line:
                raw.add(int(line, 16))
    return raw


def friendly_names(funcs):
    used = set()
    names = {}
    counts = {}
    for f in funcs:
        counts[f["name"]] = counts.get(f["name"], 0) + 1
    for f in funcs:
        name = f["name"]
        if counts[name] == 1 and ident(name) and name not in ASM_RESERVED and not name.startswith(GENERATED_PREFIXES):
            cand = name
        else:
            cand = "%s_%08X" % (sanitize(name), f["start"])
        base = cand
        n = 2
        while cand in used:
            cand = "%s_%d" % (base, n)
            n += 1
        used.add(cand)
        names[f["start"]] = cand
    return names, used


def lrw_bracket(text, lit, pool_set):
    """Return `lrw rX, [P_<lit>]` when the pool word has a label, else None.

    The bracket form makes the pool slot explicit: gas does not allocate or
    merge a literal, it just emits the displacement to the label. `lrw rX, 0x…`
    would build its own pool and `lrw rX, <label>` would load the label's
    address instead of the word stored there.
    """
    if lit is None or lit not in pool_set:
        return None
    toks = text.split()
    if len(toks) != 3 or not re.fullmatch(r"r\d+,", toks[1]):
        return None
    return "lrw %s [P_%08X]" % (toks[1], lit)


def convert_instruction(text, labels, externals):
    toks = text.split()
    if not toks:
        return None
    mn = toks[0]
    if mn == "lrw" or mn.startswith(".") or "(bad)" in text or "<undef" in text:
        return None
    if mn in BRANCH_MNEMONICS:

        def repl(m):
            target = int(m.group(1), 16)
            if target not in labels:
                externals.add(target)
            return "L_%08X" % target

        text = re.sub(r"0x([0-9a-fA-F]+)", repl, text)
    return text


def bytes_at(image, addr, size):
    off = addr - IMAGE_VMA
    return image[off:off + size]


def word_at(image, addr):
    return int.from_bytes(bytes_at(image, addr, 4), "little")


def region(value):
    if PAYLOAD_START <= value < VECTOR_END:
        return "vector"
    if TEXT_START <= value < TEXT_END:
        return "text"
    if RODATA_START <= value < RODATA_END:
        return "rodata"
    if RODATA_END <= value < 0x08096000:
        return "free"
    if 0x08096000 <= value < 0x08100000:
        return "persistent"
    if 0x08010000 <= value < PAYLOAD_START:
        return "app_header"
    if 0x20000000 <= value < 0x20050000:
        return "ram"
    if 0x40000000 <= value < 0x40100000:
        return "mmio"
    if value == 0:
        return "zero"
    return "other"


def target_symbol(value):
    r = region(value)
    if r in ("vector", "text"):
        return "target_text_%08X" % value
    if r == "rodata":
        return "rodata_%08X" % value
    return None


def branch_targets(text):
    toks = text.split()
    if not toks or toks[0] not in BRANCH_MNEMONICS:
        return []
    return [int(m.group(1), 16) for m in re.finditer(r"0x([0-9a-fA-F]+)", text)]


def build_site_map(body, dis, funcs, text_data=None, packed_rodata=None,
                   anchors=None, sdk_owned=frozenset()):
    insn_starts = set()
    insn_spans = []
    for f in dis:
        for addr, size, _, _ in f["insns"]:
            insn_starts.add(addr)
            insn_spans.append((addr, addr + size))

    data_lrw = 0
    lrw_all = []
    lrw_sites = {}
    pool_other = {}
    for f in dis:
        for addr, size, text, lit in f["insns"]:
            toks = text.split()
            if not toks or toks[0] != "lrw" or lit is None:
                continue
            if text_data is not None and text_data.overlaps(addr, addr + size):
                data_lrw += 1
                continue
            if not (TEXT_START <= lit < TEXT_END):
                die("lrw literal outside text at 0x%08X: 0x%08X" % (addr, lit))
            if lit % 4:
                die("lrw literal not 4-byte aligned at 0x%08X: 0x%08X" % (addr, lit))
            value = word_at(body, lit)
            lrw_all.append((addr, lit, value))
            target = lrw_sites if region(value) in PAYLOAD_REGIONS else pool_other
            rec = target.setdefault(lit, {"value": value, "refs": []})
            if rec["value"] != value:
                die("conflicting lrw values at pool 0x%08X" % lit)
            rec["refs"].append(addr)

    long_sites = {}
    for f in dis:
        for addr, size, text, lit in f["insns"]:
            toks = text.split()
            if not toks or not toks[0].startswith(".long") or size != 4:
                continue
            if addr % 4:
                continue
            value = word_at(body, addr)
            if region(value) in PAYLOAD_REGIONS:
                long_sites[addr] = {"value": value, "text": text}

    text_sites = {}
    for site, rec in lrw_sites.items():
        text_sites[site] = dict(rec, kind="lrw_pool")
    for site, rec in long_sites.items():
        if site in text_sites:
            text_sites[site]["function_data"] = True
        else:
            text_sites[site] = dict(rec, kind="function_data", refs=[])

    vector_sites = {}
    for i in range(64):
        addr = PAYLOAD_START + i * 4
        value = word_at(body, addr)
        if region(value) in PAYLOAD_REGIONS:
            vector_sites[addr] = {"value": value, "index": i, "kind": "vector"}

    rodata_sites = {}
    excluded_rodata = {}
    for addr in range(RODATA_START, RODATA_END - 3, 4):
        value = word_at(body, addr)
        if region(value) not in PAYLOAD_REGIONS:
            continue
        if packed_rodata is not None and packed_rodata.overlaps(addr, addr + 4):
            excluded_rodata[addr] = {"value": value, "kind": "packed_rodata"}
        else:
            rodata_sites[addr] = {"value": value, "kind": "rodata_word"}

    span_sorted = sorted(insn_spans)
    span_starts = [a for a, _ in span_sorted]

    def inside_instruction(lit):
        i = bisect.bisect_right(span_starts, lit) - 1
        return i >= 0 and span_starts[i] < lit < span_sorted[i][1]

    pool_labels = sorted(lit for lit in set(lrw_sites) | set(pool_other)
                         if not inside_instruction(lit))
    pool_rejected = sorted((lit for lit in set(lrw_sites) | set(pool_other)
                            if inside_instruction(lit)))

    text_targets = set()
    rodata_targets = set()
    for recs in (text_sites, vector_sites, rodata_sites):
        for rec in recs.values():
            v = rec["value"]
            if region(v) in ("vector", "text"):
                text_targets.add(v)
            elif region(v) == "rodata":
                rodata_targets.add(v)

    data_branches = 0
    branch_set = set()
    for f in dis:
        for addr, size, text, lit in f["insns"]:
            toks = text.split()
            if not toks or toks[0] not in BRANCH_MNEMONICS:
                continue
            if text_data is not None and text_data.overlaps(addr, addr + size):
                data_branches += 1
                continue
            branch_set.update(branch_targets(text))
    missing_branches = {t for t in branch_set if t not in insn_starts}
    extra_text = {t for t in text_targets if t not in insn_starts}
    extra_text |= {t for t in missing_branches if PAYLOAD_START <= t < TEXT_END}
    extra_text = sorted(extra_text)
    absolute_sites = {}
    absolute_rejected = {}
    unsafe_word = set()
    for f in dis:
        for addr, size, text, lit in f["insns"]:
            if size <= 4 and addr % 4 == 0:
                continue
            lo, hi = addr, addr + size
            for a in range(lo & ~3, hi, 4):
                if not (lo >= a and hi <= a + 4):
                    unsafe_word.add(a)
    if anchors:
        claimed = set(text_sites) | set(vector_sites) | set(rodata_sites)
        for lit, rec in sorted(pool_other.items()):
            name = anchors.get(rec["value"])
            if name is None or lit in claimed:
                continue
            r = region(rec["value"])
            if r not in NAMED_DATA_REGIONS:
                continue
            if name in sdk_owned:
                absolute_rejected[lit] = "sdk_owned_name"
                continue
            if text_data is not None and not text_data.overlaps(lit, lit + 4):
                absolute_rejected[lit] = "not_marked_data"
                continue
            if lit in unsafe_word:
                absolute_rejected[lit] = "instruction_spans_word"
                continue
            if any(lit < t < lit + 4 for t in text_targets | set(extra_text)):
                absolute_rejected[lit] = "label_inside_word"
                continue
            absolute_sites[lit] = {"value": rec["value"], "name": name,
                                   "refs": rec["refs"], "kind": "lrw_" + r}

    text_site_addrs = sorted(text_sites)
    rodata_site_addrs = sorted(rodata_sites)

    def inside(sorted_sites, addr):
        i = bisect.bisect_right(sorted_sites, addr) - 1
        return i >= 0 and addr < sorted_sites[i] + 4

    for addr in text_site_addrs:
        if addr < TEXT_START:
            die("symbolic text site 0x%08X is outside .text" % addr)
        if addr in insn_starts and addr < VECTOR_END:
            die("symbolic site at vector entry 0x%08X" % addr)
    for a, b in zip(text_site_addrs, text_site_addrs[1:]):
        if b < a + 4:
            die("overlapping symbolic text sites 0x%08X and 0x%08X" % (a, b))
    for a, b in zip(rodata_site_addrs, rodata_site_addrs[1:]):
        if b < a + 4:
            die("overlapping symbolic rodata sites 0x%08X and 0x%08X" % (a, b))

    for f in dis:
        for addr, size, text, lit in f["insns"]:
            if inside(text_site_addrs, addr):
                s = text_site_addrs[bisect.bisect_right(text_site_addrs, addr) - 1]
                if addr + size > s + 4:
                    die("instruction 0x%08X extends past pool word 0x%08X" % (addr, s))

    for t in text_targets:
        if inside(text_site_addrs, t) and t not in text_sites:
            die("text target 0x%08X falls inside a pool word" % t)
    for t in rodata_targets:
        if inside(rodata_site_addrs, t) and t not in rodata_sites:
            die("rodata target 0x%08X falls inside a rodata pointer word" % t)
    for t in extra_text:
        if inside(text_site_addrs, t):
            die("extra text label 0x%08X falls inside a pool word" % t)
    if set(excluded_rodata) & set(rodata_sites):
        die("excluded packed words overlap symbolic rodata words")
    for addr in excluded_rodata:
        if not (RODATA_START <= addr < RODATA_END - 3):
            die("excluded packed word 0x%08X is outside .rodata" % addr)

    return {
        "insn_starts": insn_starts,
        "insn_spans": insn_spans,
        "lrw_all": lrw_all,
        "lrw_sites": lrw_sites,
        "long_sites": long_sites,
        "text_sites": text_sites,
        "vector_sites": vector_sites,
        "rodata_sites": rodata_sites,
        "excluded_rodata": excluded_rodata,
        "text_targets": text_targets,
        "rodata_targets": rodata_targets,
        "extra_text": extra_text,
        "missing_branches": sorted(t for t in missing_branches if t not in extra_text),
        "data_lrw": data_lrw,
        "data_branches": data_branches,
        "absolute_sites": absolute_sites,
        "absolute_rejected": absolute_rejected,
        "absolute_anchors": dict(anchors or {}),
        "pool_other": pool_other,
        "pool_labels": pool_labels,
        "pool_set": set(pool_labels),
        "pool_rejected": pool_rejected,
        "inside_text_site": lambda a: inside(text_site_addrs, a),
    }


def emit_bytes(out, image, start, end, note, em=None):
    addr = start
    while addr < end:
        if em is not None:
            em.pool_label(addr)
        nxt = end
        if em is not None:
            i = bisect.bisect_right(em.pool_labels, addr)
            if i < len(em.pool_labels):
                nxt = min(nxt, em.pool_labels[i])
        n = min(16, nxt - addr)
        data = bytes_at(image, addr, n)
        out.write("    .byte " + ", ".join("0x%02x" % b for b in data))
        out.write("    # %08X%s\n" % (addr, (" " + note) if note else ""))
        addr += n


def emit_raw(out, image, addr, size, comment):
    if size == 2:
        val = int.from_bytes(bytes_at(image, addr, 2), "little")
        out.write("    .short 0x%04x" % val)
    elif size == 4:
        val = int.from_bytes(bytes_at(image, addr, 4), "little")
        out.write("    .word 0x%08x" % val)
    elif size and size > 0:
        data = bytes_at(image, addr, size)
        out.write("    .byte " + ", ".join("0x%02x" % b for b in data))
    else:
        return
    out.write("    # %08X  %s\n" % (addr, comment))


class Emitter:
    def __init__(self, out, image, sym):
        self.out = out
        self.image = image
        self.sym = sym
        self.text_sites = sym["text_sites"]
        self.abs_sites = sym["absolute_sites"]
        self.sites = dict(self.text_sites)
        self.sites.update(self.abs_sites)
        self.text_targets = sym["text_targets"]
        self.extra_text = set(sym["extra_text"])
        self.text_names = sym["text_names"]
        self.pool_labels = sym["pool_labels"]
        self.pool_set = set(self.pool_labels)
        self.aliases = set()
        self.published = set()
        self.emitted_sites = set()
        self.placed_pools = set()

    def is_site(self, addr):
        return addr in self.sites

    def pool_label(self, addr):
        """Place P_<addr> here if this address starts a referenced pool word.

        Returns True when the caller must not also emit bytes for the word.
        """
        if addr not in self.pool_set or addr in self.placed_pools:
            return False
        self.placed_pools.add(addr)
        self.out.write("P_%08X:\n" % addr)
        return True

    def publish(self, addr):
        for nm in self.text_names.get(addr, ()):
            if nm in self.published:
                continue
            self.published.add(nm)
            self.out.write(".globl %s\n%s:\n" % (nm, nm))

    def alias(self, addr):
        name = "target_text_%08X" % addr
        if addr in self.text_targets and name not in self.aliases:
            self.aliases.add(name)
            self.out.write(".globl %s\n%s:\n" % (name, name))

    def label(self, addr):
        self.out.write("L_%08X:\n" % addr)
        self.publish(addr)

    def site(self, addr, kind_hint=None):
        rec = self.sites[addr]
        self.alias(addr)
        if addr in self.sym["insn_starts"] or addr in self.extra_text:
            self.label(addr)
        self.pool_label(addr)
        self.publish(addr)
        value = rec["value"]
        if addr in self.abs_sites:
            sym = rec["name"]
            kind = rec["kind"]
        else:
            sym = target_symbol(value)
            if sym is None:
                die("symbolic site 0x%08X has no target symbol" % addr)
            kind = rec.get("kind", kind_hint or "data")
        note = "# %s: value 0x%08X" % (kind, value)
        if rec.get("refs"):
            note += ", lrw refs " + ", ".join("0x%08X" % a for a in rec["refs"][:4])
            if len(rec["refs"]) > 4:
                note += " (+%d)" % (len(rec["refs"]) - 4)
        self.out.write("    .word %s    %s\n" % (sym, note))
        self.emitted_sites.add(addr)

    def instruction(self, addr, size, text, mnemonic):
        if addr in self.sites:
            self.site(addr)
            return 0
        splits = sorted(x for x in self.extra_text if addr < x < addr + size)
        if addr in self.extra_text:
            self.alias(addr)
            self.label(addr)
        if splits:
            self.alias(addr)
            self.label(addr)
            pos = addr
            for x in splits:
                if x > pos:
                    emit_bytes(self.out, self.image, pos, x, "split instruction", self)
                self.alias(x)
                self.label(x)
                pos = x
            if pos < addr + size:
                emit_bytes(self.out, self.image, pos, addr + size,
                           "split instruction", self)
            return 0
        self.alias(addr)
        self.label(addr)
        self.pool_label(addr)
        if mnemonic is None:
            emit_raw(self.out, self.image, addr, size, text)
        else:
            self.out.write("    %s    # %08X\n" % (mnemonic, addr))
        return 0

    def gap(self, start, end):
        self.out.write("\n/* ---- data gap %08X-%08X (%d bytes) ---- */\n" %
                       (start, end, end - start))
        self.out.write(".globl data_%08X\ndata_%08X:\n" % (start, start))
        events = [a for a in self.sites if start <= a < end]
        events += [a for a in self.extra_text if start <= a < end]
        events += [a for a in self.text_names if start <= a < end]
        events += [a for a in self.pool_labels if start <= a < end]
        if start in self.text_targets:
            self.alias(start)
        pos = start
        for a in sorted(set(events)):
            if a < pos:
                continue
            if a > pos:
                emit_bytes(self.out, self.image, pos, a, "", self)
            if a in self.sites:
                self.site(a)
                pos = a + 4
            elif a in self.pool_set:
                self.pool_label(a)
                pos = a
            else:
                self.alias(a)
                self.label(a)
                pos = a
        if pos < end:
            emit_bytes(self.out, self.image, pos, end, "", self)


def prepare_instructions(dis, raw, raw_ins, sym, text_data=None,
                         convert_raw_branches=False, redirects=None,
                         applied_redirects=None):
    site_addrs = sorted(set(sym["text_sites"]) | set(sym["absolute_sites"]))
    extra = set(sym["extra_text"])
    externals = set()
    converted = {}
    split_starts = set()
    redirects = redirects or {}
    for f in dis:
        for addr, size, text, lit in f["insns"]:
            for x in extra:
                if addr < x < addr + size:
                    split_starts.add(addr)
    for f in dis:
        start = f["start"]
        raw_fn = start in raw
        ins = []
        for addr, size, text, lit in f["insns"]:
            i = bisect.bisect_right(site_addrs, addr) - 1
            covered = i >= 0 and addr < site_addrs[i] + 4
            mnemonic = None
            in_data = (text_data is not None and
                       text_data.overlaps(addr, addr + size))
            if addr in redirects:
                toks = text.split()
                if raw_fn or covered or in_data or addr in split_starts:
                    die("redirect site 0x%08X is not a plain instruction" % addr)
                if size != 4 or not toks or toks[0] != "bsr":
                    die("redirect site 0x%08X is not a 4-byte bsr: %s" %
                        (addr, text))
                mnemonic = "bsr %s" % redirects[addr]
                if applied_redirects is not None:
                    applied_redirects.add(addr)
            elif (not raw_fn and not covered and not in_data and
                    addr not in raw_ins and addr not in split_starts):
                toks = text.split()
                if toks and toks[0] == "lrw":
                    mnemonic = lrw_bracket(text, lit, sym["pool_set"])
                else:
                    mnemonic = convert_instruction(
                        text, sym["insn_starts"] | extra, externals)
            elif (convert_raw_branches and not raw_fn and not covered and
                  not in_data and addr not in split_starts):
                toks = text.split()
                if toks and toks[0] in BRANCH_MNEMONICS:
                    mnemonic = convert_instruction(
                        text, sym["insn_starts"] | extra, externals)
            ins.append((addr, size, text, mnemonic))
        converted[start] = ins
    return converted, externals, split_starts


def emit_function(out, em, f, converted, sym, names):
    start, end = f["start"], f["end"]
    nm = names[start]
    out.write("\n/* ==== FUNCTION %08X %s ==== */\n" % (start, nm))
    if start in sym["text_targets"]:
        em.alias(start)
    out.write(".type fn_%08X, @function\n" % start)
    out.write(".globl fn_%08X\nfn_%08X:\n" % (start, start))
    out.write(".type %s, @function\n" % nm)
    out.write(".globl %s\n%s:\n" % (nm, nm))
    em.publish(start)
    ins = converted[start]
    i = 0
    while i < len(ins):
        addr, size, text, mnemonic = ins[i]
        if em.is_site(addr):
            em.site(addr)
            cover = addr + 4
            j = i
            max_end = cover
            while j < len(ins) and ins[j][0] < cover:
                max_end = max(max_end, ins[j][0] + ins[j][1])
                j += 1
            if max_end > cover:
                out.write("    # bytes after symbolic word\n")
                emit_bytes(out, em.image, cover, max_end, "pool continuation", em)
            i = j
            continue
        em.instruction(addr, size, text, mnemonic)
        i += 1
    out.write(".size fn_%08X, %d\n" % (start, end - start))
    out.write(".size %s, %d\n" % (nm, end - start))


def generate(image, funcs, dis, names, raw, raw_ins, sym, out_path,
             text_data=None, convert_raw_branches=False, blocks=None,
             block_new_addr=None, redirects=None):
    body = image.read_bytes()
    applied_redirects = set()
    converted, externals, split_starts = prepare_instructions(
        dis, raw, raw_ins, sym, text_data, convert_raw_branches, redirects,
        applied_redirects)
    missing_redirects = sorted(set(redirects or {}) - applied_redirects)
    if missing_redirects:
        die("redirect sites not found: %s" %
            ", ".join("0x%08X" % a for a in missing_redirects))
    unknown_externals = sorted(externals)
    for t in unknown_externals:
        if PAYLOAD_START <= t < TEXT_END:
            die("branch target 0x%08X was not given a label" % t)
    for f in dis:
        for addr, size, text, mnemonic in converted[f["start"]]:
            if mnemonic is not None and text.split()[0] in BRANCH_MNEMONICS:
                for t in branch_targets(text):
                    if sym["inside_text_site"](t) and t not in sym["text_sites"]:
                        die("emitted branch at 0x%08X targets inside pool word 0x%08X" % (addr, t))

    with open(out_path, "w") as out:
        out.write("/* Generated by gen/generate_vendor_source.py via gen/gen_app.py.\n")
        out.write(" * Do not edit: `make source` regenerates this file.\n")
        out.write(" * Position-independent sections with symbolic payload references.\n")
        out.write(" * Undecoded/ambiguous instruction encodings are emitted as exact bytes.\n")
        out.write(" */\n")
        out.write('    .section .vectors,"ax",@progbits\n')
        for t in unknown_externals:
            out.write("    .set L_%08X, 0x%08X\n" % (t, t))
        out.write("\n/* ---- vector table %08X-%08X ---- */\n" % (PAYLOAD_START, VECTOR_END))
        if PAYLOAD_START in sym["text_targets"]:
            out.write(".globl target_text_%08X\ntarget_text_%08X:\n" % (PAYLOAD_START, PAYLOAD_START))
        if PAYLOAD_START in sym["extra_text"]:
            out.write("L_%08X:\n" % PAYLOAD_START)
        out.write(".globl __Vectors\n__Vectors:\n")
        for i in range(64):
            addr = PAYLOAD_START + i * 4
            val = word_at(body, addr)
            note = ""
            if addr in sym["vector_sites"]:
                sym_name = target_symbol(val)
                if sym_name:
                    out.write("    .word %s    # [%02d] 0x%08X\n" % (sym_name, i, val))
                    continue
            for f in dis:
                if f["start"] == val:
                    note = names.get(val, "")
                    break
            out.write("    .word 0x%08X    # [%02d] %s\n" % (val, i, note))

        out.write('\n    .section .text,"ax",@progbits\n')
        em = Emitter(out, body, sym)
        funcs_by_start = {f["start"]: f for f in dis}
        for b in blocks:
            out.write("\n/* ---- BLOCK %08X -> %08X (%d bytes, %d functions) ---- */\n" %
                      (b["start"], block_new_addr[b["start"]], b["size"],
                       len(b["functions"])))
            for i, fs in enumerate(b["functions"]):
                f = funcs_by_start[fs]
                emit_function(out, em, f, converted, sym, names)
                nxt = (b["functions"][i + 1] if i + 1 < len(b["functions"])
                       else b["end"])
                if f["end"] < nxt:
                    em.gap(f["end"], nxt)

        missing_sites = set(em.sites) - em.emitted_sites
        if missing_sites:
            die("unemitted symbolic text sites: %s" %
                ", ".join("0x%08X" % a for a in sorted(missing_sites)))
        missing_pools = em.pool_set - em.placed_pools
        if missing_pools:
            die("pool words with no label point (lrw sites keep numeric "
                "directives there): %s" %
                ", ".join("0x%08X" % a for a in sorted(missing_pools)))
        missing_names = sorted(set(n for names in sym["text_names"].values()
                                   for n in names) - em.published)
        if missing_names:
            die("text names with no label point (each must sit on an emitted "
                "instruction or pool word): %s" % ", ".join(missing_names))
    return converted, unknown_externals, split_starts


def generate_rodata(image, out_dir, sym, incbin_prefix="src"):
    data = bytes_at(image.read_bytes(), RODATA_START, RODATA_END - RODATA_START)
    (out_dir / "rodata.bin").write_bytes(data)
    sites = sym["rodata_sites"]
    labels = sorted(sym["rodata_targets"])
    names = sym["rodata_names"]
    src = out_dir / "rodata.s"
    bin_ref = "%s/rodata.bin" % incbin_prefix
    published = set()
    with open(src, "w") as out:
        out.write("/* Generated by gen/generate_vendor_source.py via gen/gen_app.py.\n")
        out.write(" * Do not edit: `make source` regenerates this file.\n")
        out.write(" * Vendor rodata with symbolic internal pointers and labels at\n")
        out.write(" * every referenced byte offset.  Words inside packed byte[]\n")
        out.write(" * blobs stay numeric: they are packed data, not pointers. */\n")
        out.write('    .section .rodata,"a",@progbits\n')
        out.write(".globl rodata_start\nrodata_start:\n")
        events = sorted(set(list(sites) + labels + list(names)))
        pos = RODATA_START
        for a in events:
            if a < pos:
                if a in sites:
                    die("rodata pointer word 0x%08X overlaps previous event" % a)
                if a in names:
                    die("rodata name %s at 0x%08X falls inside a pointer word" %
                        (",".join(names[a]), a))
                continue
            if a > pos:
                out.write('    .incbin "%s", %d, %d    # %08X-%08X\n' %
                          (bin_ref, pos - RODATA_START, a - pos, pos, a))
            if a in labels:
                out.write(".globl rodata_%08X\nrodata_%08X:\n" % (a, a))
            for nm in names.get(a, ()):
                published.add(nm)
                out.write(".globl %s\n.type %s, @object\n%s:\n" % (nm, nm, nm))
            if a in sites:
                rec = sites[a]
                target = target_symbol(rec["value"])
                out.write("    .word %s    # rodata_word: value 0x%08X\n" %
                          (target, rec["value"]))
                pos = a + 4
            else:
                pos = a
        if pos < RODATA_END:
            out.write('    .incbin "%s", %d, %d    # %08X-%08X\n' %
                      (bin_ref, pos - RODATA_START, RODATA_END - pos, pos, RODATA_END))
        out.write(".globl rodata_end\nrodata_end:\n")
        missing = sorted(set(n for v in names.values() for n in v) - published)
        if missing:
            die("rodata names with no label point: %s" % ", ".join(missing))


def read_name_list(path):
    names = set()
    if not path.exists():
        return names
    for line in open(path):
        line = line.strip()
        if line and not line.startswith("#"):
            names.add(line.split()[0])
    return names


def read_named_rows(csv_path):
    rows = []
    with open(csv_path, newline="") as f:
        for row in csv.DictReader(f):
            try:
                addr = int(row["address"], 16)
            except (ValueError, KeyError):
                continue
            rows.append((addr, row["name"], row.get("type", "")))
    rows.sort()
    return rows


def assign_names(rows, reserved, aliases):
    used = set(reserved)
    for addr, name in list(BLOB_ANCHORS) + list(aliases):
        used.add(name)
    text_names = {}
    rodata_names = {}
    absolute = []
    for addr, name, typ in rows:
        sym = make_unique(name, addr, used)
        r = region(addr)
        if r == "text":
            text_names.setdefault(addr, []).append(sym)
        elif r == "rodata":
            rodata_names.setdefault(addr, []).append(sym)
        elif name in LINKER_SCRIPT_OWNED:
            continue
        elif r == "free":
            die("name 0x%08X %s falls in the SDK text window; only %s may live "
                "there and ld/W806/app_sdk.ld provides it" %
                (addr, name, "/".join(sorted(LINKER_SCRIPT_OWNED))))
        else:
            absolute.append((addr, sym, name, typ))
    for addr, name in BLOB_ANCHORS:
        if region(addr) != "rodata":
            die("blob anchor %s is not inside .rodata" % name)
        rodata_names.setdefault(addr, []).append(name)
    for addr, name in aliases:
        r = region(addr)
        if r == "text":
            text_names.setdefault(addr, []).append(name)
        elif r == "rodata":
            rodata_names.setdefault(addr, []).append(name)
        else:
            die("alias 0x%08X %s is not in a generated section" % (addr, name))
    return ({a: tuple(v) for a, v in text_names.items()},
            {a: tuple(v) for a, v in rodata_names.items()}, absolute)


def generate_symbols(rows, out_path):
    out = ["/* Generated by gen/generate_vendor_source.py via gen/gen_app.py",
           " * from gen/named_data_symbols.csv.",
           " * Names describing movable .text and .rodata bytes are labels inside",
           " * those sections (see zw_app.s / zw_rodata.s); only genuinely",
           " * absolute addresses are .set here, so this file contributes no bytes. */",
           ""]
    for addr, sym, name, typ in rows:
        out.append(".globl %s" % sym)
        out.append(".set %s, 0x%08X    /* %s %s */" % (sym, addr, name, typ))
    extra = [
        ("__app_data_start", 0x20000100),
        ("__app_bss_start", 0x2000038C),
        ("__app_bss_end", 0x20030C78),
        ("__app_heap_start", 0x20030C78),
        ("__app_heap_end", 0x20048000),
    ]
    for sym, addr in extra:
        out.append(".globl %s" % sym)
        out.append(".set %s, 0x%08X" % (sym, addr))
    out_path.write_text("\n".join(out) + "\n")
    return len(rows) + len(extra)


def deferred_candidates(body, dis, sym, text_data=None, excluded_rodata=None):
    text_sites = sorted(sym["text_sites"])
    ro_sites = sorted(sym["rodata_sites"])
    excluded = set(excluded_rodata or ())
    insn_starts = sym["insn_starts"]
    ins_by_start = {}
    for f in dis:
        for addr, size, text, lit in f["insns"]:
            ins_by_start[addr] = (size, text)

    def covered(sorted_sites, addr):
        i = bisect.bisect_right(sorted_sites, addr) - 1
        return i >= 0 and addr < sorted_sites[i] + 4

    out = []
    for a in range(PAYLOAD_START, RODATA_END - 3, 4):
        if a % 4:
            continue
        v = word_at(body, a)
        if region(v) not in PAYLOAD_REGIONS:
            continue
        if a < VECTOR_END:
            continue
        if a in excluded or covered(text_sites, a) or covered(ro_sites, a):
            continue
        rec = {
            "address": "0x%08X" % a,
            "value": "0x%08X" % v,
            "site_region": "text" if a < TEXT_END else "rodata",
            "target_region": region(v),
            "at_instruction_start": a in insn_starts,
        }
        if text_data is not None:
            rec["in_ghidra_text_data"] = text_data.overlaps(a, a + 4)
        if a in ins_by_start:
            rec["instruction"] = ins_by_start[a][1]
        else:
            for s in sorted(ins_by_start):
                size, text = ins_by_start[s]
                if s < a < s + size:
                    rec["instruction"] = text
                    rec["instruction_start"] = "0x%08X" % s
                    break
            else:
                rec["in_gap"] = True
        out.append(rec)
    return out

COND_BRANCHES = BRANCH_MNEMONICS - {"br", "bsr", "jmp", "jsr"}

class SiteSet:
    def __init__(self, addrs):
        self.addrs = sorted(addrs)

    def covers(self, addr):
        i = bisect.bisect_right(self.addrs, addr) - 1
        return i >= 0 and addr < self.addrs[i] + 4


def _branch_operands(text):
    out = []
    for tok in text.split():
        if tok.startswith("0x"):
            try:
                out.append(int(tok.rstrip(","), 16))
            except ValueError:
                pass
    return out


def build_layout(funcs, text_data_ranges, site_addrs, text_start, text_end):
    funcs = sorted(funcs, key=lambda f: f["start"])
    order = [f["start"] for f in funcs]
    atom_end = {}
    for i, f in enumerate(funcs):
        atom_end[f["start"]] = order[i + 1] if i + 1 < len(order) else text_end
    text_data = RangeSet(text_data_ranges, "Ghidra .text data")
    sites = SiteSet(site_addrs)

    def atom_of(addr):
        i = bisect.bisect_right(order, addr) - 1
        if i < 0 or addr >= atom_end[order[i]]:
            return None
        return i

    parent = list(range(len(funcs)))

    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    def union(x, y):
        x, y = find(x), find(y)
        if x != y:
            parent[y] = x
            return True
        return False

    pool_edges = 0
    branch_edges = 0
    lrw_count = 0
    limited_branches = 0
    skipped_data = 0
    for f in funcs:
        for addr, size, text, lit in f["insns"]:
            toks = text.split()
            if not toks:
                continue
            if text_data.overlaps(addr, addr + size) or sites.covers(addr):
                skipped_data += 1
                continue
            mn = toks[0]
            a = atom_of(addr)
            if a is None:
                continue
            if mn == "lrw" and lit is not None:
                lrw_count += 1
                b = atom_of(lit)
                if b is None:
                    raise SystemExit("lrw pool 0x%08X outside text" % lit)
                if union(a, b):
                    pool_edges += 1
                continue
            limited = (mn in COND_BRANCHES or mn == "br")
            if not limited:
                continue
            limited_branches += 1
            for target in _branch_operands(text):
                b = atom_of(target)
                if b is None:
                    continue
                if union(a, b):
                    branch_edges += 1

    closure_merges = 0
    while True:
        groups = {}
        for i in range(len(funcs)):
            groups.setdefault(find(i), []).append(i)
        changed = False
        for members in groups.values():
            lo, hi = min(members), max(members)
            if hi - lo + 1 == len(members):
                continue
            root = find(lo)
            for i in range(lo + 1, hi + 1):
                if union(root, i):
                    closure_merges += 1
                    changed = True
        if not changed:
            break

    groups = {}
    for i in range(len(funcs)):
        groups.setdefault(find(i), []).append(i)
    blocks = []
    for members in groups.values():
        members.sort()
        if members != list(range(members[0], members[-1] + 1)):
            raise SystemExit("internal error: non-contiguous dependency group")
        start = order[members[0]]
        end = atom_end[order[members[-1]]]
        blocks.append({
            "start": start,
            "end": end,
            "size": end - start,
            "functions": [order[i] for i in members],
        })
    blocks.sort(key=lambda b: b["start"])

    cursor = text_start
    for b in blocks:
        if b["start"] != cursor:
            raise SystemExit("block partition does not cover text at 0x%08X" % cursor)
        if b["start"] % 4 or b["size"] % 4:
            raise SystemExit("block 0x%08X is not word-aligned (size %d)" %
                             (b["start"], b["size"]))
        cursor = b["end"]
    if cursor != text_end:
        raise SystemExit("last block ends at 0x%08X, expected 0x%08X" %
                         (cursor, text_end))

    block_index = {}
    for i, b in enumerate(blocks):
        i0 = order.index(b["functions"][0])
        for j in range(i0, i0 + len(b["functions"])):
            block_index[j] = i
    for f in funcs:
        for addr, size, text, lit in f["insns"]:
            toks = text.split()
            if not toks or text_data.overlaps(addr, addr + size) or sites.covers(addr):
                continue
            mn = toks[0]
            a = atom_of(addr)
            if a is None:
                continue
            if mn == "lrw" and lit is not None:
                if block_index[a] != block_index[atom_of(lit)]:
                    raise SystemExit("lrw pool crosses blocks at 0x%08X" % addr)
            elif mn in COND_BRANCHES or mn == "br":
                for target in _branch_operands(text):
                    b = atom_of(target)
                    if b is not None and block_index[a] != block_index[b]:
                        raise SystemExit("limited branch crosses blocks at 0x%08X" % addr)

    return {
        "blocks": blocks,
        "counts": {
            "atoms": len(funcs),
            "blocks": len(blocks),
            "lrw_checked": lrw_count,
            "limited_branches_checked": limited_branches,
            "skipped_data_instructions": skipped_data,
            "pool_edges_merged": pool_edges,
            "branch_edges_merged": branch_edges,
            "interval_closure_merges": closure_merges,
        },
    }


def order_blocks(blocks, mode, pinned_addrs=(), text_start=0x08010500):
    if mode == "stock":
        ordered = list(blocks)
    else:
        pin_index = set()
        for addr in pinned_addrs:
            for i, b in enumerate(blocks):
                if b["start"] <= addr < b["end"]:
                    pin_index.add(i)
                    break
        segments = []
        prev = -1
        for p in sorted(pin_index):
            if p - prev > 1:
                segments.append(list(range(prev + 1, p)))
            prev = p
        if prev + 1 < len(blocks):
            segments.append(list(range(prev + 1, len(blocks))))
        result = list(blocks)
        for seg in segments:
            chosen = [blocks[i] for i in seg]
            if mode == "reverse":
                chosen.reverse()
            elif mode.startswith("rotate:"):
                n = int(mode.split(":", 1)[1], 0) % len(chosen)
                chosen = chosen[n:] + chosen[:n]
            elif mode.startswith("seed:"):
                rng = random.Random(int(mode.split(":", 1)[1], 0))
                rng.shuffle(chosen)
            else:
                raise SystemExit("unknown block order: %s" % mode)
            for slot, b in zip(seg, chosen):
                result[slot] = b
        ordered = result

    cursor = text_start
    new_addr = {}
    for b in ordered:
        if b["size"] % 4:
            raise SystemExit("cannot place unaligned block 0x%08X" % b["start"])
        new_addr[b["start"]] = cursor
        cursor += b["size"]
    return ordered, new_addr


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--image",
                    default="firmware/build/generated/image/image1.img")
    ap.add_argument("--inventory", default="gen/inventory.csv")
    ap.add_argument("--symbols", default="gen/named_data_symbols.csv")
    ap.add_argument("--objdump", default="csky-abiv2-elf-objdump")
    ap.add_argument("--out", default="firmware/build/generated/base")
    ap.add_argument("--cache", default="firmware/build/generated/disasm_cache.json")
    ap.add_argument("--raw-list", default="gen/config/raw_functions.txt")
    ap.add_argument("--raw-insns", default="gen/config/raw_instructions.txt")
    ap.add_argument("--text-data", default="gen/config/ghidra_text_data.txt")
    ap.add_argument("--packed-rodata",
                    default="gen/config/ghidra_rodata_packed.txt")
    ap.add_argument("--map-meta", default="gen/config/ghidra_map_meta.json")
    ap.add_argument("--convert-raw-branches", action="store_true",
                    help="emit pinned branch slots as labeled mnemonics "
                         "(required when function atoms are reordered)")
    ap.add_argument("--block-order", default="stock",
                    help="text block permutation: stock, reverse, rotate:N, seed:N")
    ap.add_argument("--pin-addr", action="append", default=[], metavar="ADDR",
                    help="keep the block containing ADDR at its stock address "
                         "(repeatable; deferred text targets are pinned "
                         "automatically)")
    ap.add_argument("--redirect-call", action="append", default=[],
                    metavar="ADDR=SYMBOL",
                    help="replace the 4-byte bsr at ADDR with a call to SYMBOL "
                         "(repeatable; used for the C startup hook)")
    ap.add_argument("--publish-alias", action="append", default=[],
                    metavar="ADDR=SYMBOL",
                    help="publish SYMBOL as a label at ADDR inside the blob "
                         "(repeatable; used to bind an SDK vector slot to vendor "
                         "code, which an absolute .set cannot follow if .text "
                         "moves)")
    ap.add_argument("--sdk-owned-names", default="gen/config/drop_names.txt",
                    help="names externalize.py deletes from symbols.s because the "
                         "SDK defines them; their value is the SDK's, so they "
                         "cannot be used as absolute anchors")
    args = ap.parse_args()

    base = Path(__file__).resolve().parent.parent
    image = (base / args.image).resolve()
    inventory = (base / args.inventory).resolve()
    symbols_csv = (base / args.symbols).resolve()
    out_dir = (base / args.out).resolve()
    cache = (base / args.cache).resolve()
    raw_path = (base / args.raw_list).resolve()
    raw_ins_path = (base / args.raw_insns).resolve()
    text_data_path = (base / args.text_data).resolve()
    packed_rodata_path = (base / args.packed_rodata).resolve()
    map_meta_path = (base / args.map_meta).resolve()
    out_dir.mkdir(parents=True, exist_ok=True)

    if not image.exists():
        die("missing image: %s" % image)
    text_data = load_ranges(text_data_path, TEXT_START, TEXT_END,
                            "Ghidra .text data")
    packed_rodata = load_ranges(packed_rodata_path, RODATA_START, RODATA_END,
                                "Ghidra packed rodata")
    check_map_meta(map_meta_path, {
        "text_data": (text_data_path, text_data),
        "rodata_packed": (packed_rodata_path, packed_rodata),
    })
    funcs = parse_functions(inventory)
    dis = load_disassembly(Path(args.objdump), image, funcs, cache)
    names, friendly_used = friendly_names(funcs)
    raw = load_raw(raw_path)
    raw_ins = load_raw(raw_ins_path)
    body = image.read_bytes()

    redirects = {}
    for spec in args.redirect_call:
        if "=" not in spec:
            die("malformed --redirect-call (expected ADDR=SYMBOL): %s" % spec)
        addr_s, symbol = spec.split("=", 1)
        try:
            addr = int(addr_s, 0)
        except ValueError:
            die("malformed --redirect-call address: %s" % addr_s)
        if not ident(symbol):
            die("malformed --redirect-call symbol: %s" % symbol)
        if addr in redirects:
            die("duplicate --redirect-call for 0x%08X" % addr)
        redirects[addr] = symbol

    aliases = []
    for spec in args.publish_alias:
        if "=" not in spec:
            die("malformed --publish-alias (expected ADDR=SYMBOL): %s" % spec)
        addr_s, symbol = spec.split("=", 1)
        try:
            addr = int(addr_s, 0)
        except ValueError:
            die("malformed --publish-alias address: %s" % addr_s)
        if not ident(symbol):
            die("malformed --publish-alias symbol: %s" % symbol)
        if any(sym_name == symbol for _, sym_name in aliases):
            die("duplicate --publish-alias symbol: %s" % symbol)
        aliases.append((addr, symbol))

    text_names, rodata_names, absolute_names = assign_names(
        read_named_rows(symbols_csv),
        friendly_used | set(names.values()) |
        {"__Vectors", "rodata_start", "rodata_end"}, aliases)
    anchors = {}
    for addr, sym_name, _, _ in absolute_names:
        if region(addr) in NAMED_DATA_REGIONS:
            anchors.setdefault(addr, sym_name)
    sdk_owned = read_name_list((base / args.sdk_owned_names).resolve())

    sym = build_site_map(body, dis, funcs, text_data, packed_rodata, anchors,
                         sdk_owned)
    sym["text_names"] = text_names
    sym["rodata_names"] = rodata_names

    if args.block_order != "stock" and not args.convert_raw_branches:
        die("--block-order requires --convert-raw-branches")
    deferred = deferred_candidates(body, dis, sym, text_data,
                                   sym["excluded_rodata"])
    pins = set()
    for a in args.pin_addr:
        try:
            pins.add(int(a, 0))
        except ValueError:
            die("malformed --pin-addr: %s" % a)
    for rec in deferred:
        if rec.get("target_region") == "text":
            pins.add(int(rec["value"], 16))
    layout = build_layout(dis, text_data.ranges,
                          sorted(sym["text_sites"]),
                          TEXT_START, TEXT_END)
    ordered, block_new_addr = order_blocks(
        layout["blocks"], args.block_order, sorted(pins), TEXT_START)

    try:
        incbin_prefix = out_dir.relative_to(base).as_posix()
    except ValueError:
        incbin_prefix = str(out_dir)

    app_s = out_dir / "app.s"
    converted, unknown_externals, _ = generate(
        image, funcs, dis, names, raw, raw_ins, sym, app_s, text_data,
        args.convert_raw_branches, ordered, block_new_addr, redirects)
    if args.block_order != "stock":
        for f in dis:
            for addr, size, text, mnemonic in converted[f["start"]]:
                if mnemonic is not None:
                    continue
                toks = text.split()
                if (toks and toks[0] in BRANCH_MNEMONICS and
                        not sym["inside_text_site"](addr) and
                        not text_data.overlaps(addr, addr + size)):
                    die("unconverted branch 0x%08X cannot be reordered" % addr)
    generate_rodata(image, out_dir, sym, incbin_prefix)
    abs_count = generate_symbols(absolute_names, out_dir / "symbols.s")

    redirect_records = []
    for addr in sorted(redirects):
        rec = None
        for f in dis:
            for a, size, text, _ in f["insns"]:
                if a == addr:
                    rec = {"size": size, "text": text}
                    break
            if rec is not None:
                break
        redirect_records.append({
            "site": "0x%08X" % addr,
            "symbol": redirects[addr],
            "original": rec["text"] if rec else None,
            "size": rec["size"] if rec else None,
        })
    block_layout = {
        "block_order": args.block_order,
        "convert_raw_branches": bool(args.convert_raw_branches),
        "pinned_targets": ["0x%08X" % a for a in sorted(pins)],
        "redirect_calls": redirect_records,
        "counts": layout["counts"],
        "blocks": [{
            "stock_start": "0x%08X" % b["start"],
            "stock_end": "0x%08X" % b["end"],
            "new_start": "0x%08X" % block_new_addr[b["start"]],
            "size": b["size"],
            "functions": ["0x%08X" % a for a in b["functions"]],
        } for b in ordered],
        "moved_blocks": sum(
            1 for b in ordered if block_new_addr[b["start"]] != b["start"]),
    }
    raw_funcs = [f["start"] for f in dis if f["start"] in raw]
    asm_insns = sum(1 for f in dis for _, _, _, m in converted[f["start"]] if m is not None)
    raw_insns = sum(1 for f in dis for _, _, _, m in converted[f["start"]] if m is None)
    site_count = (len(sym["text_sites"]) + len(sym["vector_sites"]) +
                  len(sym["rodata_sites"]))
    print("functions %d  raw functions %d  mnemonic insns %d  raw insns %d" % (
        len(dis), len(raw_funcs), asm_insns, raw_insns))
    print("symbolic sites %d (text %d, vectors %d, rodata %d)" % (
        site_count, len(sym["text_sites"]), len(sym["vector_sites"]),
        len(sym["rodata_sites"])))
    print("targets: text %d, rodata %d; extra labels %d; deferred words %d" % (
        len(sym["text_targets"]), len(sym["rodata_targets"]),
        len(sym["extra_text"]), len(deferred)))
    print("excluded packed rodata words %d; data-sourced lrw %d, branches %d" % (
        len(sym["excluded_rodata"]), sym["data_lrw"], sym["data_branches"]))
    print("Ghidra maps: text data %d ranges/%d bytes; packed rodata %d ranges/%d bytes" % (
        len(text_data.ranges), text_data.bytes(),
        len(packed_rodata.ranges), packed_rodata.bytes()))
    print("names: %d .text labels, %d .rodata labels, %d absolute, %d from the "
          "linker script" % (
              sum(len(v) for v in text_names.values()),
              sum(len(v) for v in rodata_names.values()),
              abs_count, len(LINKER_SCRIPT_OWNED)))
    print("blocks %d (%s): moved %d, pinned %s; lrw %d, branches %d, closure %d" % (
        block_layout["counts"]["blocks"], args.block_order,
        block_layout["moved_blocks"],
        ",".join(block_layout["pinned_targets"]) or "none",
        block_layout["counts"]["lrw_checked"],
        block_layout["counts"]["limited_branches_checked"],
        block_layout["counts"]["interval_closure_merges"]))
    if redirect_records:
        for r in redirect_records:
            print("redirect %s -> %s (was %s)" %
                  (r["site"], r["symbol"], r["original"]))
    if unknown_externals:
        print("absolute branch targets outside payload: %s" %
              ", ".join("0x%08X" % a for a in unknown_externals))


if __name__ == "__main__":
    main()
