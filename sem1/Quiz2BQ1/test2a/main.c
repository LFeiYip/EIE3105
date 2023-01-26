/*
 * test2a.c
 *
 * Created: 3/11/2021 上午9:59:40
 * Author : Fei
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

int state=0;
int count=0;

void set_timer1(){
	OCR1A=0xF424;
	TCCR1B=0x0C;//timer 1 CTC mode with prescaler 256, trigger interrupt every 1s
	TIMSK1=(1<<OCIE1A);
}

void setup(){
	DDRC|=0xFF;//0x04
	EIMSK=(1<<1);//enable INT1;
	EICRA=0x08;
}


ISR(INT1_vect){
	state+=1;
}

ISR(TIMER1_COMPA_vect){
	count++;
}


int main(void)
{
	setup();
	sei();
	set_timer1();
	while (1)
	{
		if(state==0)
		{
			if (count==0)
			{
				PORTC=0x01;
			}
			if (count==1)
			{
				PORTC=0;
			}
			if (count==2)
			{
				count=0;
			}
		}
		if(state==1){
			PORTC=0;
		}
		if (state==2)
		{
			state=0;
		}
	}
}


