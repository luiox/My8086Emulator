#define DEBUG 1

#include <stdio.h>

#define GetLow8BitsIn16Bits(x) ((x) & 0x00FF)
#define GetHigh8BitsIn16Bits(x) ((x) >> 8)
#define CombineTwo8BitsTo16Bits(high,low) (((high) << 8) | (low))

typedef unsigned int Register; /* Every register in 8086 is 16 bits. */

typedef struct tagEmulator {
	/* General-Purpose Registers. */
	Register rax;
	Register rbx;
	Register rcx;
	Register rdx;
	/* Segment Registers. */
	Register rcs;
	Register rip;
	Register rss;
	Register res;
	/* Address Register. */
	Register rds;
	/* Stack Registers. */
	Register rsp;
	Register rsi;
	Register rdi;
	char* memory;
}Emulator;

char memory[1 << 16]; // 64K memory

void emulator_init(Emulator* e)
{
	e->memory = memory;
	e->rax = 0;
	e->rbx = 0;
	e->rcx = 0;
	e->rdx = 0;

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
	macro_test();
#endif

	/* Determine whether to execute files or simple code based on the number of args. */
	if (argc == 1) { /* execute simple code. */
		while (1) {

		}
	}
	else { /* execute asm file. */
		while (1) {

		}
	}


	return 0;
}