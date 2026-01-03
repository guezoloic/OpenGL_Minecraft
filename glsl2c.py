#!/usr/bin/env python3

import sys
from pathlib import Path

line: int = 12

def write_binary(content: bytes) -> str:
    text = ""
    for i, byte in enumerate(content):
        if i % line == 0:
            text += "\t"
        text += f"0x{byte:02x}, "
        if (i + 1) % line == 0:
            text += "\n"
    text += "0x00\n"
    return text

def main() -> int:
    # check arguments
    if len(sys.argv) < 2 or len(sys.argv) > 3:
        print("glsl2c.py <shader_file> [output_c_file]")
        return 1

    src = Path(sys.argv[1])

    if not src.suffix.endswith((".glsl", ".frag", ".vert")):
        print(f"file error: cannot convert {src.suffix} to .c file")
        return 1

    dst = Path(sys.argv[2]) if len(sys.argv) == 3 else src.with_suffix(".c")

    # variable name
    varname = f"{src.stem}_{src.suffix[1:]}".upper()

    # read binary
    content = src.read_bytes()

    with open(dst, "w") as f:
        f.write(f"const unsigned char {varname}[] = {{\n{write_binary(content)}}};\n")
        f.write(f"const unsigned int {varname}_LEN = {len(content)};\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())
