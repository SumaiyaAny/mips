/*
 * InstructionMemory.cpp
 *
 * Created: 8/25/2022 2:09:29 PM
 * Author : Sumaiya Sultana
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

uint16_t INSTRUCTIONS[1<<5] = {
	0xc023, 0x903e, 0xd231, 0xe234, 0x0135, 0xb323, 0x6331, 0x4341, 0xf120, 0x7441, 0x2334, 0xf110, 0x8131, 0x1531, 0x5225, 0x3352, 0xf120, 0xa13a
};

int main(void)
{
	// Some pins of PORTC can not be used for I/O directly.
	// turn of JTAG to use them
	// o write a 1 to the JTD bit twice consecutively to turn it off
	MCUCSR = (1<<JTD);  MCUCSR = (1<<JTD);
	
	DDRB = 0x00;	// input pc
	
	// Instruction : C[7:0]A[7:0]
	DDRA = 0xFF;	// lower 8-bits of instruction
	DDRC = 0xFF;	// upper 8-bits of instruction
	
	uint8_t pc = -1;
	uint16_t instruction;
	/* Replace with your application code */
	while (1)
	{
		if (PINB != pc) {
			pc = PINB;
			instruction = INSTRUCTIONS[pc];
			PORTA = (uint8_t) instruction;
			PORTC = (uint8_t) (instruction >> 8);
			_delay_ms(50);
		}
	}
}


