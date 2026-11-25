#!/usr/bin/env python3

import re
import sys

A8 = r"0[0-9A-Fa-f]{7}"

VECTOR_BASE_ADDR = "08010400"


def remap_vector_base(text):
    n = 0
    def sub(m):
        nonlocal n
        n += 1
        return "__Vectors"
    pat = r"\b(?:target_text|L)_(%s)\b" % VECTOR_BASE_ADDR
    return re.sub(pat, sub, text), n


def load_drop(path):
    drop = {}
    for line in open(path):
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        addr, name = line.split()
        drop[addr.upper()] = name
    return drop


def split_app_sections(text):
    m = re.search(r"^[ \t]*\.section[ \t]+\.text\b.*$", text, re.M)
    if not m:
        die("no .section .text found in app.s")
    return text[:m.start()], text[m.start():]


def strip_vector_table_and_keep_sets(pre):
    keep = []
    for ln in pre.splitlines(keepends=True):
        s = ln.strip()
        if s.startswith(".set L_"):
            keep.append(ln)
        elif re.match(r"\.section\b", s) and ".vectors" in s:
            keep.append(ln)
        elif s.startswith("/*") or s.startswith("*") or s == "":
            keep.append(ln)
    return "".join(keep)


def transform_app_body(body, drop, counts):
    def retarget_word(m):
        addr = m.group(1).upper()
        if addr in drop:
            counts["word"] += 1
            return ".word %s" % drop[addr]
        return m.group(0)

    def retarget_branch(m):
        prefix, label, addr = m.group(1), m.group(2), m.group(3).upper()
        if addr in drop:
            counts["branch"] += 1
            return "%s %s" % (prefix, drop[addr])
        return m.group(0)

    body = re.sub(r"\.word[ \t]+target_text_(%s)" % A8, retarget_word, body)
    body = re.sub(
        r"\b(bsr|jbr|jmp|jsr)[ \t]+(L|fn|target_text)_(%s)" % A8,
        retarget_branch, body)

    lines = body.splitlines(keepends=True)
    out = []
    cur_drop_name = None
    for ln in lines:
        fh = re.match(r"/\* ==== FUNCTION (%s) (\S+) ==== \*/" % A8, ln)
        if fh:
            addr = fh.group(1).upper()
            name = fh.group(2)
            cur_drop_name = name if addr in drop else None
            out.append(ln)
            continue
        if re.match(r"/\* ---- (BLOCK|data gap)", ln) or \
           re.match(r"[ \t]*\.section\b", ln.strip()):
            cur_drop_name = None
        if cur_drop_name is not None:
            s = ln.strip()
            if s == ".globl %s" % cur_drop_name:
                counts["name"] += 1
                continue
            if s == "%s:" % cur_drop_name:
                continue
            if (s.startswith(".type %s," % cur_drop_name) or
                    s.startswith(".size %s," % cur_drop_name)):
                continue
        out.append(ln)
    return "".join(out)


def transform_rodata(text, drop, counts):
    def retarget_word(m):
        addr = m.group(1).upper()
        if addr in drop:
            counts["rodata_word"] += 1
            return ".word %s" % drop[addr]
        return m.group(0)

    return re.sub(r"\.word[ \t]+target_text_(%s)" % A8, retarget_word, text)


def transform_symbols(text, drop, drop_names, counts):
    names = {v for v in drop.values()} | set(drop_names)
    out = []
    pending = None
    for ln in text.splitlines(keepends=True):
        s = ln.strip()
        g = re.match(r"\.globl (\S+)$", s)
        st = re.match(r"\.set (\S+), .*", s)
        if g and g.group(1) in names:
            pending = g.group(1)
            counts["symbols_dropped"] += 1
            continue
        if st and st.group(1) in names:
            pending = None
            continue
        out.append(ln)
    return "".join(out)


def die(msg):
    sys.stderr.write("externalize: %s\n" % msg)
    sys.exit(1)


def load_names(path):
    names = set()
    if not path:
        return names
    for line in open(path):
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        names.add(line.split()[0])
    return names


def main():
    import argparse
    ap = argparse.ArgumentParser()
    ap.add_argument("--in-dir", required=True)
    ap.add_argument("--out-dir", required=True)
    ap.add_argument("--drop-set", required=True)
    ap.add_argument("--drop-names", default=None,
                    help="file of bare symbol names (no entry addr) to strip "
                         "from symbols.s, e.g. ABS .set collisions like g_trap_sp")
    ap.add_argument("--report", default=None)
    a = ap.parse_args()

    drop = load_drop(a.drop_set)
    drop_names = load_names(a.drop_names)
    counts = {"branch": 0, "word": 0, "rodata_word": 0, "name": 0, "symbols_dropped": 0}

    import os
    os.makedirs(a.out_dir, exist_ok=True)

    app = open(os.path.join(a.in_dir, "app.s")).read()
    pre, body = split_app_sections(app)
    pre_kept = strip_vector_table_and_keep_sets(pre)
    body_t = transform_app_body(body, drop, counts)
    body_t, nvec = remap_vector_base(body_t)
    counts["vector_base_remap"] = nvec
    open(os.path.join(a.out_dir, "app.s"), "w").write(pre_kept + body_t)

    rodata = open(os.path.join(a.in_dir, "rodata.s")).read()
    rodata_t = transform_rodata(rodata, drop, counts)
    rodata_t, nvec_r = remap_vector_base(rodata_t)
    counts["vector_base_remap"] += nvec_r
    open(os.path.join(a.out_dir, "rodata.s"), "w").write(rodata_t)

    import shutil
    for f in ("rodata.bin",):
        src = os.path.join(a.in_dir, f)
        if os.path.exists(src):
            shutil.copy2(src, os.path.join(a.out_dir, f))

    symbols = open(os.path.join(a.in_dir, "symbols.s")).read()
    open(os.path.join(a.out_dir, "symbols.s"), "w").write(
        transform_symbols(symbols, drop, drop_names, counts))

    summary = ("dropped=%d branch_retargeted=%d word_retargeted=%d "
               "rodata_word_retargeted=%d stripped_names=%d "
               "symbols_dropped=%d" %
               (len(drop), counts["branch"], counts["word"],
                counts["rodata_word"], counts["name"],
                counts["symbols_dropped"]))
    print(summary)
    if a.report:
        open(a.report, "w").write(summary + "\n")


if __name__ == "__main__":
    main()
