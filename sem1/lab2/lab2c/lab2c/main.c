/*
 * lab2c.c
 *
 * Created: 2/10/2021 下午9:05:24
 * Author : Fei
 */ 

#include <avr/io.h>

void setup(){
	DDRC=0xFF;
	TCCR1A=0;
	TCCR1B=0x0F;//CTC mode,clock on rising edge //0x0F work
	OCR1A=0x02;//count 3, form 0 to 2
}

int main(void)
{
	setup();
	
	while(1)
	{
		if(TIFR1&(1<<OCF1A))
		{
			PORTC^=(1<<0);
			TIFR1=1<<OCF1A;
		}
		

	}
}

