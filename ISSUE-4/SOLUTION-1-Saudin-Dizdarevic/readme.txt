Hi,

I have created a Tetris for AgonLight. The code is in C, actually written in Z88DK C compiler. I used the nightly version which has support for Agon.
The code, which is initially written for Windows (https://github.com/TheWaggle/Tetris/blob/main/forWin/tetris.c adapted from) has been adapted to work for Agon.

The code is compiled on Windows 10 by following:

zcc +agon -pragma-define:CRT_ENABLE_COMMANDLINE=1 -pragma-define:CLIB_DEFAULT_SCREEN_MODE=1 -DAMALLOC -lm -O2 -lndos main.c -o tetris.bin

Best regards,
Saudin Dizdarevic
