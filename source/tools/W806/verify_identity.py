#!/usr/bin/env python3
"""Check the built payload against the stock payload, byte for byte.

The vendor application is position-fixed: it is linked to absolute addresses and
its literal pools name those addresses, so there is no such thing as "close
enough" for the bytes the vendor wrote.  Those bytes are copied verbatim out of
the stock image, which is what makes them checkable: the built image must equal
the stock image everywhere except where this tree deliberately rewrites it.

Exactly two mechanisms rewrite vendor bytes, and nothing else may:

  * the vector table -- the SDK startup supplies __Vectors, so all 64 slots are
    SDK content.  A slot may differ only when it now names an address inside the
    SDK region the link appends after the stock payload;
  * a call retarget -- SDK functions override the stock ones of the same name,
    so a `bsr` whose callee the SDK supplies is re-pointed at the SDK copy.  A
    changed word may differ only if it decodes as `bsr` and its new target lies
    inside that same SDK region.

Everything else in the stock prefix must be identical.  The check is
one-directional on purpose: every difference must be explained by one of the two
mechanisms, but a rewrite the link happened not to perform is not an error -- a
call left pointing at a stock function still lands on working code.  So the gate
reports corruption (a generator regression, a lost block, a stray edit) and never
invents a failure out of a legitimate layout change.

Usage: verify_identity.py --stock <stock payload> --built <built payload>
"""

import argparse
import hashlib
import struct
import sys
from pathlib import Path

PAYLOAD_VMA = 0x08010400
VECTOR_SIZE = 0x100
BSR_OPCODE = 0xE000
BSR_OPCODE_MASK = 0xF000


class VerifyError(Exception):
    pass


def read_file(path, what):
    try:
        return Path(path).read_bytes()
    except OSError as exc:
        raise VerifyError("cannot read %s %s: %s" % (what, path, exc))


def bsr_target(blob, off, addr):
    """Decode a 4-byte `bsr` at `off`, or None if it is not one.

    C-SKY stores the 32-bit form as two little-endian halfwords: the opcode plus
    the low 10 displacement bits, then the high 16.  So the displacement is 26
    bits and counts halfwords.  Both halves are needed: masking only the low 4
    bits decodes forward calls correctly and backward calls as garbage, which
    silently invents call sites that were never retargeted.
    """
    if off < 0 or off + 4 > len(blob):
        return None
    low, high = struct.unpack_from("<HH", blob, off)
    if low & BSR_OPCODE_MASK != BSR_OPCODE:
        return None
    disp = (((low & 0x3FF) << 16) | high) << 1
    if disp & 0x4000000:
        disp -= 0x8000000
    return addr + disp


def check(stock, built, sdk_base):
    if len(built) < len(stock):
        raise VerifyError(
            "built payload is %d bytes, shorter than the %d-byte stock payload "
            "the vendor bytes are copied from"
            % (len(built), len(stock)))
    if PAYLOAD_VMA + len(stock) != sdk_base:
        raise VerifyError(
            "stock payload ends at 0x%08X, not at the SDK text base 0x%08X; "
            "the stock image and the link describe different layouts "
            "(pass --sdk-base to match, or supply the firmware this tree "
            "expects)" % (PAYLOAD_VMA + len(stock), sdk_base))

    sdk_end = PAYLOAD_VMA + len(built)

    def in_sdk(value):
        return sdk_base <= value < sdk_end

    differing = [i for i in range(len(stock)) if stock[i] != built[i]]

    changed_vectors = []
    for off in range(0, VECTOR_SIZE, 4):
        if stock[off:off + 4] == built[off:off + 4]:
            continue
        value = struct.unpack_from("<I", built, off)[0]
        if not in_sdk(value):
            raise VerifyError(
                "vector slot %d at 0x%08X names 0x%08X, outside the SDK region "
                "0x%08X..0x%08X"
                % (off // 4, PAYLOAD_VMA + off, value, sdk_base, sdk_end))
        changed_vectors.append(off)

    claimed = set()
    for off in changed_vectors:
        claimed.update(range(off, off + 4))

    payload_end = PAYLOAD_VMA + len(stock)
    retargets = []
    for off in range(VECTOR_SIZE, len(stock) - 3, 2):
        addr = PAYLOAD_VMA + off
        if stock[off:off + 4] == built[off:off + 4]:
            continue
        was = bsr_target(stock, off, addr)
        now = bsr_target(built, off, addr)
        if was is None or now is None:
            continue
        if not (PAYLOAD_VMA <= was < payload_end) or not in_sdk(now):
            continue
        retargets.append((off, was, now))
        claimed.update(range(off, off + 4))

    stray = [off for off in differing if off not in claimed]
    if stray:
        first = stray[0]
        lines = ["%d differing byte(s) match no mechanism" % len(stray)]
        for off in stray[:5]:
            lines.append("  %#010x  built %02x  stock %02x"
                         % (PAYLOAD_VMA + off, built[off], stock[off]))
        if len(stray) > 5:
            lines.append("  ...")
        raise VerifyError("\n".join(lines))

    return changed_vectors, retargets, len(differing), sdk_end


def main(argv=None):
    ap = argparse.ArgumentParser(
        description="Verify the built payload against the stock payload")
    ap.add_argument("--stock", required=True,
                    help="stock payload unpacked from the .fls (image1.img)")
    ap.add_argument("--built", required=True, help="built app payload (.bin)")
    ap.add_argument("--sdk-base", default="0x0807E3D8",
                    help="text base of the SDK region appended after the stock "
                         "payload (conf.mk SDK_TEXT_BASE)")
    args = ap.parse_args(argv)

    try:
        sdk_base = int(args.sdk_base, 16)
    except ValueError:
        ap.error("--sdk-base is not a hex number: %s" % args.sdk_base)

    try:
        changed_vectors, retargets, total, sdk_end = check(
            read_file(args.stock, "stock payload"),
            read_file(args.built, "built payload"),
            sdk_base)
    except VerifyError as exc:
        sys.stderr.write("verify_identity: %s\n" % exc)
        return 1

    print("verify  stock   %d B @ 0x%08X, %d vendor bytes"
          % (Path(args.stock).stat().st_size, PAYLOAD_VMA,
             Path(args.stock).stat().st_size))
    print("verify  built   %d B, ends 0x%08X (SDK from 0x%08X)"
          % (Path(args.built).stat().st_size, sdk_end, sdk_base))
    print("verify  %d vector slot(s) -> SDK handlers, %d call(s) -> SDK "
          "functions" % (len(changed_vectors), len(retargets)))
    print("verify  %d differing byte(s), every one explained; all other stock "
          "bytes identical" % total)
    print("verify  sha256 %s" % hashlib.sha256(
        Path(args.built).read_bytes()).hexdigest())
    return 0


if __name__ == "__main__":
    sys.exit(main())
