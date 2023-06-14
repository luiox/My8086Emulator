#define _CRT_SECURE_NO_WARNINGS
#define DEBUG 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#pragma warning(disable:6031)

/* This macro function extracts the low 8 bits from a 16-bit value. */
#define GetLow8BitsIn16Bits(x) ((x) & 0x00FF)
/* This macro function extracts the high 8 bits from a 16-bit value. */
#define GetHigh8BitsIn16Bits(x) ((x) >> 8)
/* This macro function combines two 8-bit values into a single 16-bit value. */
#define CombineTwo8BitsTo16Bits(high,low) (((high) << 8) | (low))

typedef unsigned int Register; /* Every register in 8086 is 16 bits. */

typedef struct tagEmulator {
	/* General-Purpose Registers. */
	Register rax; /* Accumulator register */
	Register rbx; /* Base register */
	Register rcx; /* Counter register */
	Register rdx; /* Data register */
	Register rsp; /* Stack pointer register */
	Register rbp; /* Base pointer register */
	Register rsi; /* Source index register */
	Register rdi; /* Destination index register */
	/* Segment Registers. */
	Register rds; /* Data segment register */
	Register res; /* Extra segment register */
	Register rss; /* Stack segment register */
	Register rcs; /* Code segment register */
	Register rip; /* Instruction pointer register */

	char* memory; /* Memory */
} Emulator;
char memory[1 << 16]; // 64K memory

void emulator_init(Emulator* e)
{
	assert(e);
	memset(e, 0, sizeof(Emulator));
	e->memory = memory;

}

void r_proc(Emulator* e, char* cmd)
{
	assert(e);
	assert(cmd);
	size_t size = strlen(cmd);
	if (2 == size) { /* show infomation of all registers. */
		printf("AX=%04X  BX=%04X  CX=%04X  DX=%04X  SP=%04X  BP=%04X  SI=%04X\n",
			e->rax, e->rbx, e->rcx, e->rdx, e->rsp, e->rbp, e->rsi);
		printf("DI=%04X  DS=%04X  ES=%04X  SS=%04X  CS=%04X  IP=%04X\n",
			e->rdi, e->rds, e->res, e->rss, e->rcs, e->rip);
	}
	else {
		static char* regs[] = { "AX","BX","CX","DX","SP","BP","SI","DI","DS","ES","SS","CS","IP" };
		char targetReg[3] = { cmd[2],cmd[3],'\0' };
		for (int i = 0; i < 13; i++)
			if (strcmp(targetReg, regs[i]) == 0) {
				Register* reg = (Register*)e + i;
				printf("%s=%04X\n", targetReg, *reg);
				printf(":");
				unsigned short value;
				scanf("%hu", &value);
				*reg = value;
				break;
			}
	}
}

void d_proc(Emulator* e, char* cmd)
{
	
}

#ifdef DEBUG

void macro_test()
{
	Register a = 0x12, b = 0x34, c = 0x1234;
	printf("%X\n", GetHigh8BitsIn16Bits(c));
	printf("%X\n", GetLow8BitsIn16Bits(c));
	printf("%X\n", CombineTwo8BitsTo16Bits(a, b));
}

#endif // DEBUG

int main(int argc, char* argv)
{
	Emulator e;
	emulator_init(&e);

#ifdef DEBUG
	//macro_test();
#endif

	/* Determine whether to execute files or simple code based on the number of args. */
	if (argc == 1) { /* execute simple code. */
		while (1) {
			printf("-");
			char cmd[128] = { '\0' };
			fgets(cmd, 127, stdin);
			fflush(stdin);
			switch (cmd[0]) {
			case 'R':
				r_proc(&e, cmd);
				break;
			case 'D':
				d_proc(&e, cmd);
				break;
			case 'E':

			default:
				break;
			}
		}
	}
	else { /* execute asm file. */
		while (1) {

		}
	}


	return 0;
}