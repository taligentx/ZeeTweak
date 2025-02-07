'''
zrle2bmp.py 1.0 - Convert Zeeweii compressed images to bitmap

Zeeweii DSO3D12 firmware contains both uncompressed and compressed image data. This script
converts Zeeweii's custom RLE compression to a standard RGB565 bitmap, keeping the original
color palette (offset 0x73F6C, 448 bytes).

Requirements: pip install pillow

Compressed image data format:
  - Header
    - Bytes 0-1: width
    - Bytes 2-3: height
  - Image data
    - Bytes 0-1: pixel run length
    - Bytes 2-3: color index from Zeeweii color palette

Compressed images:
  - Boot logo (offset 0x24D1C, 1792 bytes)

Offsets and sizes are based on firmware 3.0.6-III.
'''

import struct
import sys
from PIL import Image


# Zeeweii firmware color palette, RGB565
DSO3D12_PALETTE = [0x0000, 0xFFFF, 0xF800, 0x07E0, 0x001F, 0xFFE0, 0xF81F, 0x07FF, 0xCE59, 0xFE41,
                   0x2945, 0x630C, 0xA514, 0xD69A, 0x0969, 0x228E, 0x0250, 0x1D3A, 0xF81F, 0xFA80]


def convert_zrle(input_file, output_file=None):
    with open(input_file, "rb") as f:
        data = f.read()
    
    # Read width (2 bytes) and height (2 bytes), little-endian
    width = struct.unpack_from("<H", data, 0)[0]
    height = struct.unpack_from("<H", data, 2)[0]
    print(f"Decoding {width}x{height} image...")
    
    pixels = []
    idx = 4  # Start after width/height
    
    while idx < len(data):
        run_length = data[idx]
        color_index = data[idx + 1]
        idx += 2
        
        if color_index >= len(DSO3D12_PALETTE):
            print(f"Warning: Color index {color_index} out of bounds, using black.")
            color = 0x0000
        else:
            color = DSO3D12_PALETTE[color_index]
        
        pixels.extend([color] * run_length)
    
    # Verify pixel count
    if len(pixels) != width * height:
        print(f"Warning: Pixel count mismatch! Expected {width * height}, got {len(pixels)}.")
        pixels = pixels[:width * height]
    
    # Convert to raw RGB565 bytes
    bmp_data = b"".join(struct.pack("<H", p) for p in pixels)
    
    if output_file is None:
        output_file = input_file.rsplit('.', 1)[0] + ".bmp"
    
    # BMP header
    file_size = 72 + len(bmp_data)
    bmp_header = struct.pack(
        "<2sIHHIIiiHHIIIIIIIIII",
        b"BM", file_size, 0, 0, 70, 56, width, -height, 1, 16, 3, len(bmp_data),
        2835, 2835, 0, 0, 0xF800, 0x07E0, 0x001F, 0x0000)

    with open(output_file, "wb") as f:
        f.write(bmp_header)
        f.write(bmp_data)
    
    print(f"Image saved as {output_file}")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 zrle2bmp.py <input_file> [output_file]")
        sys.exit(1)
    
    input_filename = sys.argv[1]
    output_filename = sys.argv[2] if len(sys.argv) > 2 else None
    
    convert_zrle(input_filename, output_filename)

