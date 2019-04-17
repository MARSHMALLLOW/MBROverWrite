# MBROverWrite [![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
Overwrite the Master Boot Record with C++

You need to:

- Dev-Cpp to compile this code.
- Python version 2 or later to convert the binary file.
- An assembler like NASM.

## How to compile it:
First thing, assemble the MBR source code by clicking "make.bat".
If you see binary.bin, binary.img and binary.iso in your path, that means the code is compiled.
Now convert it to C format, use bin2cpp.py binary.bin exported.c.
Finally, compile the C++ code, and test it in a virtual machine.

## WARNING: Don't test it in your physical machine! For educational purposes only!
