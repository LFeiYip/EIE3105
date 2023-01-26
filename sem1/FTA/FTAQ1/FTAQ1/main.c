/*
 * FTAQ1.c
 *
 * Created: 30/11/2021 上午9:00:23
 * Author : Fei
 */ 
//Yip Lung Fei, 19052736d
/*pC1 led1
pc2 led2
pc2 led3*/
#include <avr/io.h>
#include <avr/interrupt.h>

int state=1;

void set_timer1(){
	OCR1A=0xF424;
	TCCR1B=0x0C;//timer 1 CTC mode with prescaler 256, trigger interrupt every 1s
	TIMSK1=(1<<OCIE1A);
}

void setup(){
	DDRC|=0xFF;//0x04
}

ISR(TIMER1_COMPA_vect){
	state++;
}


int main(void)
{
	setup();
	set_timer1();
	sei();
	while (1)
	{
		if(state==1)
		{
			PORTC=(0<<1)|(1<<2)|(1<<3);
		}else if (state==2)
		{
			PORTC=(1<<1)|(0<<2)|(1<<3);
		}else if (state==3)
		{
			PORTC=(1<<1)|(1<<2)|(0<<3);
		}else if (state==4)
		{
			PORTC=(1<<1)|(1<<2)|(1<<3);
		}
		if (state==5)
		{
			state=1;
		}
	}
}

