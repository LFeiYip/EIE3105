/*
 * GccApplication2.c
 *
 * Created: 9/14/2022 3:47:30 PM
 * Author : 19052736d
 */ 

#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
	TCCR0A = (1<<COM0A1)|(0<<COM0A0)|(1<<COM0B1)|(0<<COM0B0)|(1<<WGM01)|(1<<WGM00);
	TCCR0B = (1<<WGM02)|(0<<CS02)|(1<<CS01)|(1<<CS00);//PRESCALING 64
	OCR0A = 124;//500Hz
	OCR0B = 62;//50% DUTY CYCLE
	DDRD = 0B00100000;
    while (1);
}

 