# AssemblerN2T
A program that translates Hack assembly language files (.asm files) into the equivalent binary machine code (.hack file).

The Assembler class drives the program, centered on the Run function. The Parser object parses the assembly file, after which the Code object writes the corresponding binary representation of the command to the output file.
A Makefile is included for a simpler build step, while example Hack .asm files can be found on the Nand2Tetris course website (https://www.nand2tetris.org/).
When running the program, include the file extension in the terminal command (e.g., Assembler Pong.asm).
