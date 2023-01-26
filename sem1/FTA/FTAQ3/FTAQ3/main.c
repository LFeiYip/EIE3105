/*
 * FTAQ3.c
 *
 * Created: 30/11/2021 上午10:40:09
 * Author : Fei
 */ 
//Yip Lung Fei

#include <avr/io.h>
#include <avr/interrupt.h>

int state=0;
int count=0;

void set_timer1(){
	OCR1A=0xF424;
	TCCR1B=0x0C;//timer 1 CTC mode with prescaler 256, trigger interrupt every 1s
	TIMSK1=(1<<OCIE1A);
}

void set_timer1_half(){
	OCR1A=0x7A12;
	TCCR1B=0x0C;//timer 1 CTC mode with prescaler 256, trigger interrupt every 0.5s
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
	set_timer1();
	sei();
	while (1)
	{
		if(state==0){
			//set_timer1();
			if (count==0)
			{
				PORTC=0;
			}
			if (count==1)
			{
				PORTC=(1<<1)|(1<<2)|(1<<3);
			}
			if(count==2){
				count=0;
			}
		}
		if(state==1){
			//set_timer1_half();
			if (count==0)
			{	
				PORTC=(1<<1)|(0<<2)|(1<<3);
			}
			if (count==2)
			{
				PORTC=(0<<1)|(1<<2)|(0<<3);
			}
			if(count==4){
				count=0;
			}
		}
		if(state==2){
			state=0;
		}
		
		
	}
}


