#!/usr/bin/env python3

import argparse
import hashlib
import json
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
GEN = ROOT / "gen"

OUTPUTS = {
    "app.s": "zw_app.s",
    "rodata.s": "zw_rodata.s",
    "rodata.bin": "zw_rodata.bin",
    "symbols.s": "zw_symbols.s",
}

HOOKS = (
    ("0x08014F32", "app_mainloop", "bsr L_08016CB4"),
    ("0x08021098", "dmm_remote_flush", "bsr 0x080270A8"),
)

VECTOR_ALIASES = (
    ("0x08015678", "UART2_5_IRQHandler"),
)
INCBIN_RE = re.compile(r'\.incbin "[^"]*rodata\.bin"')
STOCK_FIRMWARE_SHA256 = "8a8b0b03b5fea86038d3c6c51ce1d8adefa76cb300fd45d279572fee00adb21b"


def die(msg):
    sys.stderr.write("generate_vendor_source: %s\n" % msg)
    sys.exit(1)


def sha256_file(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def input_files():
    files = sorted(GEN.glob("*.py")) + sorted(GEN.glob("*.csv"))
    files += sorted((GEN / "config").glob("*"))
    return [p for p in files if p.is_file()]


def signature(firmware):
    inputs = {"firmware": sha256_file(firmware)}
    for p in input_files():
        inputs[p.relative_to(ROOT).as_posix()] = sha256_file(p)
    blob = json.dumps(inputs, sort_keys=True).encode()
    return hashlib.sha256(blob).hexdigest(), inputs


def find_firmware(arg):
    if arg:
        p = Path(arg).expanduser().resolve()
        if not p.is_file():
            die("firmware not found: %s" % p)
        return p
    candidates = sorted(p for p in (ROOT / "firmware").glob("*.fls")
                        if not p.name.startswith("._"))
    stock = [p for p in candidates if sha256_file(p) == STOCK_FIRMWARE_SHA256]
    if len(stock) == 1:
        return stock[0]
    if len(stock) > 1:
        die("multiple stock .fls files in firmware/: %s\n"
            "select one with FIRMWARE=<path>"
            % ", ".join(p.name for p in stock))
    if candidates:
        die("no stock image in firmware/: %s\n"
            "expected container SHA-256 %s\n"
            "build output lands here too; pass FIRMWARE=<path> to override"
            % (", ".join(p.name for p in candidates), STOCK_FIRMWARE_SHA256))
    die("no firmware image found: place dso3d12_v3.0.7_III.fls in %s "
        "or pass FIRMWARE=<path>" % (ROOT / "firmware"))


def find_objdump(arg):
    if arg:
        if os.path.isfile(arg) or shutil.which(arg):
            return arg
        die("objdump not found: %s\n"
            "set CONFIG_W800_TOOLCHAIN_PATH or put the C-SKY toolchain on PATH"
            % arg)
    found = shutil.which("csky-abiv2-elf-objdump")
    if found:
        return found
    die("csky objdump not found; set CONFIG_W800_TOOLCHAIN_PATH or put the "
        "C-SKY toolchain on PATH")


def run(cmd, what):
    print("GEN      %s" % what)
    result = subprocess.run([str(x) for x in cmd])
    if result.returncode:
        die("%s failed with exit code %d" % (what, result.returncode))


def write_atomic(path, data):
    tmp = path.with_name(path.name + ".tmp")
    tmp.write_bytes(data)
    os.replace(tmp, path)


def render_app(text):
    for site, symbol, source_line in HOOKS:
        comment = "bsr %s    # %s  hook: replaces %s" % (
            symbol, site[2:], source_line)
        pattern = re.compile(
            r"^([ \t]*)bsr[ \t]+%s[ \t]*#[ \t]*%s[^\n]*$"
            % (re.escape(symbol), site[2:]), re.M)
        hits = pattern.findall(text)
        if len(hits) != 1:
            die("expected exactly one redirected bsr at %s, found %d"
                % (site, len(hits)))
        text = pattern.sub(
            lambda m, c=comment: "%s%s" % (m.group(1), c), text)
    return text


def render_rodata(text):
    text, count = INCBIN_RE.subn('.incbin "zw_rodata.bin"', text)
    if count == 0:
        die("no rodata .incbin found in generated rodata.s")
    if text.count(".incbin") != count:
        die("unexpected .incbin directive in generated rodata.s")
    return text


def install(sdk_dir, out_dir):
    out_dir.mkdir(parents=True, exist_ok=True)
    app = render_app((sdk_dir / "app.s").read_text())
    rodata = render_rodata((sdk_dir / "rodata.s").read_text())
    write_atomic(out_dir / "zw_app.s", app.encode())
    write_atomic(out_dir / "zw_rodata.s", rodata.encode())
    write_atomic(out_dir / "zw_rodata.bin", (sdk_dir / "rodata.bin").read_bytes())
    write_atomic(out_dir / "zw_symbols.s", (sdk_dir / "symbols.s").read_bytes())


def outputs_current(stamp, sig, out_dir):
    if not stamp or stamp.get("signature") != sig:
        return False
    recorded = stamp.get("outputs", {})
    for dst in OUTPUTS.values():
        path = out_dir / dst
        if not path.is_file() or recorded.get(dst) != sha256_file(path):
            return False
    return True


def main():
    ap = argparse.ArgumentParser(description="Generate the vendor sources from a DSO3D12 .fls")
    ap.add_argument("--firmware", default=None, help="DSO3D12 v3.0.7 III .fls (default: firmware/*.fls)")
    ap.add_argument("--out-dir", default=str(ROOT / "src_zw"), help="destination for the generated vendor files")
    ap.add_argument("--work-dir", default=str(ROOT / "firmware" / "build" / "generated"), help="scratch directory")
    ap.add_argument("--objdump", default=None, help="csky-abiv2-elf-objdump path")
    ap.add_argument("--force", action="store_true", help="regenerate even when the stamp is current")
    args = ap.parse_args()

    firmware = find_firmware(args.firmware)
    out_dir = Path(args.out_dir).resolve()
    work_dir = Path(args.work_dir).resolve()
    objdump = find_objdump(args.objdump)

    sig, inputs = signature(firmware)
    stamp_path = work_dir / "stamp.json"
    stamp = None
    if stamp_path.is_file():
        try:
            stamp = json.loads(stamp_path.read_text())
        except ValueError:
            stamp = None
    if not args.force and outputs_current(stamp, sig, out_dir):
        print("source   : up to date (%s)" % out_dir)
        return 0

    image_dir = work_dir / "image"
    base_dir = work_dir / "base"
    sdk_dir = work_dir / "sdk"
    for d in (image_dir, base_dir, sdk_dir):
        if d.exists():
            shutil.rmtree(d)
    work_dir.mkdir(parents=True, exist_ok=True)

    run([sys.executable, GEN / "unpack_firmware.py",
         "--firmware", firmware, "--out-dir", image_dir], "unpack")

    gen_cmd = [sys.executable, GEN / "gen_app.py",
               "--image", image_dir / "image1.img",
               "--inventory", GEN / "inventory.csv",
               "--symbols", GEN / "named_data_symbols.csv",
               "--objdump", objdump,
               "--out", base_dir,
               "--cache", work_dir / "disasm_cache.json",
               "--raw-list", GEN / "config" / "raw_functions.txt",
               "--raw-insns", GEN / "config" / "raw_instructions.txt",
               "--text-data", GEN / "config" / "ghidra_text_data.txt",
               "--packed-rodata", GEN / "config" / "ghidra_rodata_packed.txt",
               "--map-meta", GEN / "config" / "ghidra_map_meta.json",
               "--sdk-owned-names", GEN / "config" / "drop_names.txt",
               "--convert-raw-branches", "--block-order", "stock"]
    for site, symbol, _ in HOOKS:
        gen_cmd += ["--redirect-call", "%s=%s" % (site, symbol)]
    for addr, symbol in VECTOR_ALIASES:
        gen_cmd += ["--publish-alias", "%s=%s" % (addr, symbol)]
    run(gen_cmd, "vendor assembly")

    run([sys.executable, GEN / "externalize.py",
         "--in-dir", base_dir, "--out-dir", sdk_dir,
         "--drop-set", GEN / "config" / "drop_set.txt",
         "--drop-names", GEN / "config" / "drop_names.txt",
         "--report", work_dir / "externalize_report.txt"],
        "SDK externalization")

    install(sdk_dir, out_dir)
    outputs = {dst: sha256_file(out_dir / dst) for dst in OUTPUTS.values()}
    stamp = {
        "signature": sig,
        "inputs": inputs,
        "firmware": {"path": str(firmware),
                     "sha256": inputs["firmware"]},
        "outputs": outputs,
    }
    write_atomic(stamp_path, (json.dumps(stamp, indent=2, sort_keys=True)
                              + "\n").encode())
    for dst in OUTPUTS.values():
        print("SOURCE   %s (%d bytes)" % (out_dir / dst,
                                          (out_dir / dst).stat().st_size))
    print("source   : generated from %s" % firmware)
    return 0


if __name__ == "__main__":
    sys.exit(main())
