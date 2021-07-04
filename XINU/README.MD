XINU with Galileo

Xinu Is Not Unix (Xinu, a recursive acronym), is an operating system for embedded systems,[2] originally developed by Douglas Comer for educational use at Purdue University in the 1980s. The name is both recursive, and is Unix spelled backwards. It has been ported to many hardware platforms, including the DEC PDP-11 and VAX systems, Sun-2 and Sun-3 workstations, Intel x86, PowerPC G3, MIPS and AVR (atmega328p/Arduino). Xinu was also used for some models of Lexmark printers.[2]

Despite its name suggesting some similarity to Unix, Xinu is a different type of operating system, written with no knowledge of the Unix source code, or compatibility goals. It uses different abstractions, and system calls, some with names matching those of Unix, but different semantics.

For the Galileo, the quickest way to get started involves using an SD memory card and a serial cable. Connect the serial cable from the board to a PC (inexpensive cables are all that one needs). Run a terminal emulator, such as minicom to display the serial output in a window on the PC. Plug the SD card into the PC, compile Xinu and load the image onto the SD card. Unplug the SD card from the PC and plug it into the experimenter board. Boot the board, and use the console serial connection to boot the image from the SD card. Output from Xinu will be displayed over the serial line.


Resources: 

https://xinu.cs.purdue.edu/

https://github.com/jarrocha/XinuBBB/tree/main

https://xinu.cs.mu.edu/index.php/Main_Page

http://mathcs.pugetsound.edu/~dchiu/teaching/archive/CS475sp17/proj1/
