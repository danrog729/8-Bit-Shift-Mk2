#include <stdio.h>
#pragma warning(disable : 4996)

char acc;
char pc;
char reg0;
char reg1;
char reg2;
char reg3;
char reg4;
char reg5;
char reg6;
char reg7;
char program[256] = {
0x10, 0x01, 0x04, 0x40, 0x10, 0x7E, 0x04, 0x01, 0x10, 0x70, 0x04, 0x02, 0x02, 0x01, 0x01, 0x40,
0x04, 0x04, 0x02, 0x02, 0x01, 0x40, 0x04, 0x08, 0x10, 0x34, 0x04, 0x80, 0x08, 0x08, 0x01, 0x01,
0x20, 0x80, 0x10, 0x48, 0x04, 0x80, 0x08, 0x04, 0x01, 0x02, 0x20, 0x80, 0x10, 0x5C, 0x04, 0x80,
0x02, 0x40, 0x20, 0x80, 0x10, 0x18, 0x04, 0x80, 0x08, 0x02, 0x01, 0x04, 0x04, 0x02, 0x02, 0x02,
0x01, 0x40, 0x04, 0x08, 0x02, 0x40, 0x20, 0x80, 0x10, 0x18, 0x04, 0x80, 0x08, 0x01, 0x01, 0x08,
0x04, 0x01, 0x02, 0x01, 0x01, 0x40, 0x04, 0x04, 0x02, 0x40, 0x20, 0x80, 0x10, 0x00, 0x80, 0x01};
char ram[256];

void add_command(char* reg);
void not_command(char* reg);
void sav_command(char* reg);
void mov_command(char* reg);
void imm_command(char value);
void jmp_command(char* reg);
void inp_command(char* reg);
void out_command(char* reg);

void core_dump();

int main()
{
	while (pc < 256)
	{
		char* desiredRegister = 0x00;
		if (program[pc] != 0x10)
		{
			switch (program[pc + 1])
			{
			case (char)0x01:
				desiredRegister = &reg0; break;
			case (char)0x02:
				desiredRegister = &reg1; break;
			case (char)0x04:
				desiredRegister = &reg2; break;
			case (char)0x08:
				desiredRegister = &reg3; break;
			case (char)0x10:
				desiredRegister = &reg4; break;
			case (char)0x20:
				desiredRegister = &reg5; break;
			case (char)0x40:
				desiredRegister = &reg6; break;
			case (char)0x80:
				desiredRegister = &reg7; break;
			default:
				printf("UNRECOGNISED REGISTER %02x\n", program[pc + 1] & 0xff);
				core_dump();
				return -1;
			}
		}

		switch (program[pc])
		{
		case (char)0x01:
			add_command(desiredRegister); pc += 2; break;
		case (char)0x02:
			not_command(desiredRegister); pc += 2; break;
		case (char)0x04:
			sav_command(desiredRegister); pc += 2; break;
		case (char)0x08:
			mov_command(desiredRegister); pc += 2; break;
		case (char)0x10:
			imm_command(program[pc + 1]); pc += 2; break;
		case (char)0x20:
			jmp_command(desiredRegister); break;
		case (char)0x40:
			inp_command(desiredRegister); pc += 2; break;
		case (char)0x80:
			out_command(desiredRegister); pc += 2; break;
		default:
			printf("UNRECOGNISED OPCODE %02x\n", program[pc] & 0xff);
			core_dump();
			return -1;
		}
	}
}

void add_command(char* reg)
{
	acc += *reg;
}

void not_command(char* reg)
{
	acc = ~*reg;
}

void sav_command(char* reg)
{
	*reg = acc;
}

void mov_command(char* reg)
{
	acc = *reg;
}

void imm_command(char value)
{
	acc = value;
}

void jmp_command(char* reg)
{
	if ((acc & (char)0x80) == (char)0x80)
	{
		pc = *reg;
	}
	else
	{
		pc += 2;
	}
}

void inp_command(char* reg)
{
	*reg = ram[acc];
}

void out_command(char* reg)
{
	ram[acc] = *reg;
}

void core_dump()
{
	printf("CORE DUMP\n");
	printf("PROGRAM:\n");
	printf("   _0 _1 _2 _3 _4 _5 _6 _7 _8 _9 _a _b _c _d _e _f\n");
	for (int row = 0; row < 16; row++)
	{
		printf("%01x_ ", row & 0xf);
		for (int cell = 0; cell < 16; cell++)
		{
			printf("%02x ", program[row * 16 + cell] & 0xff);
		}
		printf("\n");
	}
	printf("  PC = %02x\n", pc & 0xff);
	printf(" ACC = %02x\n", acc & 0xff);
	printf("REG0 = %02x\n", reg0 & 0xff);
	printf("REG1 = %02x\n", reg1 & 0xff);
	printf("REG2 = %02x\n", reg2 & 0xff);
	printf("REG3 = %02x\n", reg3 & 0xff);
	printf("REG4 = %02x\n", reg4 & 0xff);
	printf("REG5 = %02x\n", reg5 & 0xff);
	printf("REG6 = %02x\n", reg6 & 0xff);
	printf("REG7 = %02x\n", reg7 & 0xff);
	printf("RAM:\n");
	printf("   _0 _1 _2 _3 _4 _5 _6 _7 _8 _9 _a _b _c _d _e _f\n");
	for (int row = 0; row < 16; row++)
	{
		printf("%01x_ ", row & 0xf);
		for (int cell = 0; cell < 16; cell++)
		{
			printf("%02x ", ram[row * 16 + cell] & 0xff);
		}
		printf("\n");
	}
}