/*
 * lab3b.c
 *
 * Created: 29/10/2021 下午3:51:25
 * Author : Fei
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

int count=0;
int count2=0;

void timer2_CTCModeDelay100ms(){
	OCR2A=199;
	TCCR2A=0x02;
	TCCR2B=0x01;
	//for every 1/10 second, 1.6M/200=8000=800x10
	for(int a=0;a!=10;++a){
		for(int b=0;b!=800;++b){
			while((TIFR2&(1<<1))==0);
			TIFR2=(1<<OCF2A);
		}
	}
	TCCR2B = 0;
}

void PORTC_blinking(){
	PORTC=(PORTC&(1<<0))|(1<<4);
	for(int i=0;i!=10;++i){
		timer2_CTCModeDelay100ms();
		//PORTC^=(1<<4);
		PORTC^=(1<<4);
	}
}

void set_timer1(){
	OCR1A=0xF424;
	TCCR1B=0x0C;//timer 1 CTC mode with prescaler 256, trigger interrupt every 1s
	TIMSK1=(1<<OCIE1A);
}


void setup(){
	DDRD=0xFF;
	DDRB|=0x3F;
	DDRC|=0xFF;//0x04
	set_timer1();
	EIMSK=(1<<0);
	EICRA=(1<<1);
}

void traffic_light(){
	//state1
	while(count<5){
		//time duration=5s
		PORTB=0x0C;//light2(green) light3(red)0c
		PORTC= (PORTC&(1<<0))|(1<<5);//light1(red)
	}
	
	//state2
	if(count==5){
		//from count=5 to count=6, time duration=1s
		PORTB=0x14;
		PORTC=(PORTC&(1<<0))|(1<<5);
	}
	
	//state3
	if(count==6){
		//from count= to count=7, time duration=1s
		PORTB=0x24;
		PORTC=(PORTC&(1<<0))|(1<<5);
	}
	
	//state4
	if(count==7){
		//from count=7 to count=8, time duration=1s
		PORTB=0x26;
		PORTC=(PORTC&(1<<0))|(1<<5);
	}
	
	//state5
	while((count==8)&(count<13)){
		//from count=8 to count=13, time duration=5s
		PORTB=0x21;
		PORTC=(PORTC&(1<<0))|(1<<4);
	}
	
	//state6
	if(count==13){
		//from count=13 to count=14, time duration=1s
		PORTB=0x22;
		PORTC_blinking();
		//1 second delay has already done in function 'PORTC_blinking()'
	}
	
	
	//state7
	if(count== 14){
		//from count=14 to count=15, time duration=1s
		PORTB=0x24;
		//PORTC=(1<<5)|a;
		PORTC=(PORTC&(1<<0))^(1<<5);
	}
	
	//state8
	while((count==15)&(count<16)){
		//from count=15 to count=16, time duration=1s
		PORTB=0x34;
		PORTC=(PORTC&(1<<0))^(1<<5);
	}
	
	if(count==16){
		//reset count to 0
		count=0;
	}
}

ISR(TIMER1_COMPA_vect){
	count++;
}

ISR(INT0_vect){
	count2++;
	if(count2==3){
		PORTC^=(1<<0);
		count2=0;
	}
}

int main(void)
{
	setup();
	sei();
	while (1)
	{
		traffic_light();
	}
}

