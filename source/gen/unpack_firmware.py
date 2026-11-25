#!/usr/bin/env python3

import argparse
import binascii
import hashlib
import json
import struct
import sys
from pathlib import Path

MAGIC = 0xA0FFFF9F
HEADER_SIZE = 0x40
APP_PAYLOAD_VMA = 0x08010400
APP_WINDOW_END = 0x08096000

PINNED_IMAGE1_SHA256 = "cd27caafdd477c25ec970352541b33b762f381576a7e29639dddf18c60cb826a"
PINNED_IMAGE1_SIZE = 450520

SECBOOT_PAYLOAD_VMA = 0x08002400
PINNED_IMAGE0_SIZE = 31580
PINNED_IMAGE0_SHA256 = "e86e4fcd7d48e5b1b6c6859824cbbe2ea4956da8b31a0054ee26abfb01fa0342"


def jamcrc(data):
    return (~binascii.crc32(data)) & 0xFFFFFFFF


def parse_image(data, off):
    if off + HEADER_SIZE > len(data):
        raise ValueError("truncated header at 0x%X" % off)
    hdr = struct.unpack_from("<8I16s4I", data, off)
    if hdr[0] != MAGIC:
        raise ValueError("bad magic at 0x%X: 0x%08X" % (off, hdr[0]))
    length = hdr[3]
    body_off = off + HEADER_SIZE
    body = data[body_off:body_off + length]
    if len(body) != length:
        raise ValueError("truncated payload at 0x%X" % off)
    if jamcrc(body) != hdr[6]:
        raise ValueError("bad payload JAMCRC at 0x%X" % off)
    if jamcrc(data[off:off + 0x3C]) != hdr[12]:
        raise ValueError("bad header JAMCRC at 0x%X" % off)
    return {
        "offset": off,
        "vma": hdr[2],
        "length": length,
        "payload_jamcrc": hdr[6],
        "header_jamcrc": hdr[12],
        "body": body,
    }


def unpack(firmware_path, out_dir):
    data = Path(firmware_path).read_bytes()
    image0 = parse_image(data, 0)
    image1_off = HEADER_SIZE + image0["length"]
    image1 = parse_image(data, image1_off)

    if image0["vma"] != SECBOOT_PAYLOAD_VMA:
        raise ValueError("unexpected secboot load address 0x%08X (want 0x%08X)" % (image0["vma"], SECBOOT_PAYLOAD_VMA))
    if image0["length"] != PINNED_IMAGE0_SIZE:
        raise ValueError("unexpected secboot payload size %d (want %d)" % (image0["length"], PINNED_IMAGE0_SIZE))
    digest0 = hashlib.sha256(image0["body"]).hexdigest()
    if digest0 != PINNED_IMAGE0_SHA256:
        raise ValueError(
            "secboot payload SHA-256 %s does not match the stock bootloader\n"
            "  expected %s\n"
            "The bootloader must not be changed."
            % (digest0, PINNED_IMAGE0_SHA256))

    if image1["vma"] != APP_PAYLOAD_VMA:
        raise ValueError("unexpected app load address 0x%08X (want 0x%08X)" % (image1["vma"], APP_PAYLOAD_VMA))
    if image1["length"] != PINNED_IMAGE1_SIZE:
        raise ValueError("unexpected app payload size %d (want %d)" % (image1["length"], PINNED_IMAGE1_SIZE))
    if image1["vma"] + image1["length"] > APP_WINDOW_END:
        raise ValueError("app payload crosses into persistent data")
    end = image1_off + HEADER_SIZE + image1["length"]
    if end != len(data):
        raise ValueError("%d trailing bytes after app payload" % (len(data) - end))

    digest = hashlib.sha256(image1["body"]).hexdigest()
    if digest != PINNED_IMAGE1_SHA256:
        raise ValueError(
            "app payload SHA-256 %s does not match the pinned build\n"
            "  expected %s\n"
            "The generator metadata describes DSO3D12 v3.0.7 III only."
            % (digest, PINNED_IMAGE1_SHA256))

    out_dir = Path(out_dir)
    out_dir.mkdir(parents=True, exist_ok=True)
    (out_dir / "image0.img").write_bytes(image0["body"])
    (out_dir / "image1.img").write_bytes(image1["body"])

    meta = {
        "firmware_sha256": hashlib.sha256(data).hexdigest(),
        "firmware_size": len(data),
        "image0": {
            "file": "image0.img",
            "vma": "0x%08X" % image0["vma"],
            "size": image0["length"],
            "jamcrc": "0x%08X" % image0["payload_jamcrc"],
            "sha256": digest0,
        },
        "image1": {
            "file": "image1.img",
            "vma": "0x%08X" % image1["vma"],
            "size": image1["length"],
            "jamcrc": "0x%08X" % image1["payload_jamcrc"],
            "sha256": digest,
        },
    }
    (out_dir / "firmware_meta.json").write_text(
        json.dumps(meta, indent=2, sort_keys=True) + "\n")
    return meta


def main():
    ap = argparse.ArgumentParser(description="Unpack and validate a DSO3D12 .fls firmware container")
    ap.add_argument("--firmware", required=True, help="DSO3D12 .fls file")
    ap.add_argument("--out-dir", required=True,
                    help="directory for image0.img, image1.img and metadata")
    args = ap.parse_args()
    try:
        meta = unpack(args.firmware, args.out_dir)
    except (OSError, ValueError) as exc:
        sys.stderr.write("unpack_firmware: %s\n" % exc)
        return 1
    print("firmware   : %s (%d bytes, sha256 %s)" % (args.firmware, meta["firmware_size"], meta["firmware_sha256"][:16] + "..."))
    for name in ("image0", "image1"):
        im = meta[name]
        print("%-10s : %s, %d bytes at %s, sha256 %s" % (name, im["file"], im["size"], im["vma"], im["sha256"]))
    return 0


if __name__ == "__main__":
    sys.exit(main())
