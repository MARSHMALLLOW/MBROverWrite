@echo off
"C:\Users\anasb\AppData\Local\bin\NASM\nasm" -f bin MBRSource.asm -o binary.bin
REM with bin extension.
"C:\Users\anasb\AppData\Local\bin\NASM\nasm" -f bin MBRSource.asm -o binary.iso
REM with iso extension.
"C:\Users\anasb\AppData\Local\bin\NASM\nasm" -f bin MBRSource.asm -o binary.img
REM with img extension.
echo successful!
pause