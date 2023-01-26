/*
 * interrupt test.c
 *
 * Created: 27/10/2021 上午10:12:53
 * Author : Fei
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>



void set_counter1CTC(){
	TCCR1B=0x0F;//rising edge
	OCR1A=2;
}

ISR(TIMER1_COMPA_vect){
	PORTD^=0x01;
}

int main(void)
{
	DDRD|=0xFF;//0x04
	set_counter1CTC();
	TIMSK1=(1<<OCIE1A);
	sei();
	while (1);
	
}

