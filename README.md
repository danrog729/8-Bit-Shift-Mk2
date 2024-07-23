# 8-Bit-Shift-Mk2

An emulation of a CPU architecture I designed on Turing Complete (https://store.steampowered.com/app/1444480/Turing_Complete/). I designed it with the intention of having as few logic gates as possible, which obviously leads to the design decisions you can see in the code. It has no cache and so accesses its RAM array directly. Future versions will have both a RAM and a cache, as they will be higher bit.
To use the CPU, you need to input the machine code directly into the program array, as defined at the beginning of the code. In future I will write an assembler for this machine code so this won't have to happen. I have included a .asm file as an example of what the assembly would look like. This example would compile into the machine code that is in the program array in this repository. The CPU instructions work as follows:  

Each CPU instruction is 2 bytes long. The first byte is the opcode, the second byte is a specified register, unless the opcode is 0x10 where it just acts as a value. See below.  

OPCODES (byte 1):  
0x01 - add - adds the contents of the register specified to the accumulator  
0x02 - not - bitwise nots the contents of the register specified and stores it into the accumulator  
0x04 - sav (save) - copies the contents of the accumulator to the register specified  
0x08 - mov (move) - copies the contents of the register specifice to the accumulator  
0x10 - imm (immediate) - copies the data specified in the program to accumulator  
0x20 - jmp (jump) - jumps to the address stored in the specified register if the contents of the accumulator are negative (the MSB is on)  
0x40 - inp (input) - copies a value into the specified register from the RAM array, the address in RAM being the contents of the accumulator  
0x80 - out (output) - copies the contents of the specified register into the RAM array, the address in RAM being the contents of the accumulator  

SPECIFIED REGISTER (byte 2):  
0x01 - register 0  
0x02 - register 1  
0x04 - register 2  
0x08 - register 3  
0x10 - register 4  
0x20 - register 5  
0x40 - register 6  
0x80 - register 7  
If the opcode is 0x10 i.e. an "immediate" instruction, this byte will instead act as the value that will be stored in the accumulator.  
