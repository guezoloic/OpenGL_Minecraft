#!/usr/bin/env python3
import sys
from pathlib import Path

if len(sys.argv) != 3 or not sys.argv[1].endswith((".glsl", ".vert", ".frag")):
    sys.exit(1)

src = Path(sys.argv[1])
dst = Path(sys.argv[2])

# variable name
varname = src.replace("/", "_").replace(".", "_")

# read to binary mode
content = src.read_bytes()

line = 12

with open(dst, "wb") as f:
    # content array
    f.write(f"unsigned char {varname}[] = {{\n")
    
    for i, byte in enumerate(content):
        # tab
        if i % line == 0:
            f.write("\t")
        # hexa
        f.write(f"0x{byte:02x}, ")
        
        # LF/CRLF
        if (i + 1) % line == 0:
            f.write("\n")
    
    # content size
    f.write(f"unsigned int {varname}_len = {len(content)};")