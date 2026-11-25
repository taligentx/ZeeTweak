#!/usr/bin/env python3

import argparse
import binascii
import hashlib
import struct
import sys
from pathlib import Path

MAGIC = 0xA0FFFF9F
HEADER_SIZE = 0x40
APP_PAYLOAD_VMA = 0x08010400
APP_WINDOW_END = 0x08096000
SECBOOT_PAYLOAD_VMA = 0x08002400
SECBOOT_PAYLOAD_SIZE = 31580
SECBOOT_PAYLOAD_SHA256 = \
    "e86e4fcd7d48e5b1b6c6859824cbbe2ea4956da8b31a0054ee26abfb01fa0342"


class VerifyError(Exception):
    pass


def jamcrc(data):
    return (~binascii.crc32(data)) & 0xFFFFFFFF


def read_file(path, what):
    try:
        return Path(path).read_bytes()
    except OSError as exc:
        raise VerifyError("cannot read %s %s: %s" % (what, path, exc))


def parse_image(data, off, what):
    if off + HEADER_SIZE > len(data):
        raise VerifyError("%s: truncated header at 0x%X" % (what, off))
    hdr = struct.unpack_from("<8I16s4I", data, off)
    if hdr[0] != MAGIC:
        raise VerifyError("%s: bad magic at 0x%X: 0x%08X"
                          % (what, off, hdr[0]))
    length = hdr[3]
    body_off = off + HEADER_SIZE
    body = data[body_off:body_off + length]
    if len(body) != length:
        raise VerifyError("%s: truncated payload at 0x%X" % (what, off))
    if jamcrc(body) != hdr[6]:
        raise VerifyError("%s: bad payload JAMCRC at 0x%X" % (what, off))
    if jamcrc(data[off:off + 0x3C]) != hdr[12]:
        raise VerifyError("%s: bad header JAMCRC at 0x%X" % (what, off))
    return hdr, body_off, body


def check_secboot(secboot_bin_path, secboot_img_path):
    payload = read_file(secboot_bin_path, "secboot payload")
    if len(payload) != SECBOOT_PAYLOAD_SIZE:
        raise VerifyError(
            "secboot payload size %d, want %d (stock)"
            % (len(payload), SECBOOT_PAYLOAD_SIZE))
    digest = hashlib.sha256(payload).hexdigest()
    if digest != SECBOOT_PAYLOAD_SHA256:
        raise VerifyError(
            "secboot payload was modified\n"
            "  %s\n  expected %s\n  actual   %s\n"
            "The bootloader must stay stock; restore tools/W806/"
            "W806_secboot.bin." % (secboot_bin_path,
                                   SECBOOT_PAYLOAD_SHA256, digest))

    img = read_file(secboot_img_path, "secboot image")
    hdr, body_off, body = parse_image(img, 0, "secboot image")
    if hdr[2] != SECBOOT_PAYLOAD_VMA:
        raise VerifyError("secboot image loads at 0x%08X, want 0x%08X"
                          % (hdr[2], SECBOOT_PAYLOAD_VMA))
    if body != payload:
        raise VerifyError("secboot image payload does not match %s"
                          % secboot_bin_path)
    if body_off + len(body) != len(img):
        raise VerifyError("secboot image has %d trailing bytes"
                          % (len(img) - body_off - len(body)))
    return payload, img


def check_fls(fls_path, secboot_payload, secboot_img, app_bin_path,
              run_address, version_string=None):
    fls = read_file(fls_path, "firmware image")
    h0, off0, body0 = parse_image(fls, 0, "secboot image in .fls")
    if h0[2] != SECBOOT_PAYLOAD_VMA:
        raise VerifyError(".fls secboot loads at 0x%08X, want 0x%08X"
                          % (h0[2], SECBOOT_PAYLOAD_VMA))
    if len(body0) != SECBOOT_PAYLOAD_SIZE or body0 != secboot_payload:
        raise VerifyError(".fls does not carry the pinned stock secboot "
                          "payload")
    sec_end = off0 + len(body0)
    if fls[:sec_end] != secboot_img:
        raise VerifyError(".fls secboot region differs from the generated "
                          "secboot image")

    app_bin = read_file(app_bin_path, "app payload")
    if not app_bin:
        raise VerifyError("app payload is empty")

    h1, off1, body1 = parse_image(fls, sec_end, "app image in .fls")
    vma = h1[2]
    if vma != APP_PAYLOAD_VMA:
        raise VerifyError("app image loads at 0x%08X, want 0x%08X"
                          % (vma, APP_PAYLOAD_VMA))
    if run_address is not None and run_address != vma:
        raise VerifyError(
            "configured run address 0x%08X does not match the app image "
            "load address 0x%08X" % (run_address, vma))
    if version_string is not None:
        raw = h1[8].split(b"\0", 1)[0]
        if raw != version_string.encode():
            raise VerifyError(
                "app image version string %r, want %r"
                % (raw.decode("latin-1"), version_string))
    end = vma + len(body1)
    if end > APP_WINDOW_END:
        raise VerifyError(
            "app payload ends at 0x%08X, crossing the persistent/calibration "
            "region at 0x%08X" % (end, APP_WINDOW_END))
    if body1 != app_bin:
        raise VerifyError(".fls app payload differs from %s" % app_bin_path)
    if off1 + len(body1) != len(fls):
        raise VerifyError(".fls has %d trailing bytes"
                          % (len(fls) - off1 - len(body1)))
    return vma, end, len(fls)


def main():
    ap = argparse.ArgumentParser(description="Verify the secboot image and the packed .fls firmware")
    ap.add_argument("--secboot-bin", required=True,
                    help="stock secboot payload (W806_secboot.bin)")
    ap.add_argument("--secboot-img", required=True,
                    help="generated secboot image (W806_secboot.img)")
    ap.add_argument("--fls", help="packed .fls firmware to verify")
    ap.add_argument("--app-bin", help="raw app payload (.bin)")
    ap.add_argument("--run-address",
                    help="configured app load address, e.g. 0x08010400")
    ap.add_argument("--version-string",
                    help="expected app image version string")
    args = ap.parse_args()

    if bool(args.fls) != bool(args.app_bin):
        ap.error("--fls and --app-bin must be given together")
    run_address = None
    if args.run_address is not None:
        text = args.run_address.strip()
        try:
            run_address = int(text, 16)
        except ValueError:
            ap.error("--run-address is not a hex number: %s" % text)

    try:
        payload, secboot_img = check_secboot(args.secboot_bin,
                                             args.secboot_img)
        print("CHECK    secboot payload  %d B, sha256 %s (stock)"
              % (len(payload), SECBOOT_PAYLOAD_SHA256[:16] + "..."))
        print("CHECK    secboot image    %d B @ 0x%08X, CRCs ok"
              % (len(secboot_img), SECBOOT_PAYLOAD_VMA))
        if args.fls:
            vma, end, total = check_fls(args.fls, payload, secboot_img,
                                        args.app_bin, run_address,
                                        args.version_string)
            print("CHECK    app payload      %d B @ 0x%08X, ends 0x%08X "
                  "< 0x%08X"
                  % (end - vma, vma, end, APP_WINDOW_END))
            if args.version_string:
                print("CHECK    version string   %s" % args.version_string)
            print("CHECK    firmware image   %d B, layout and CRCs ok"
                  % total)
    except VerifyError as exc:
        sys.stderr.write("verify_image: %s\n" % exc)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
