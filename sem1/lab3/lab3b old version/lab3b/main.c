/*
 * lab3b.c
 *
 * Created: 16/10/2021 下午7:42:06
 * Author : Fei
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

int count=0;

void CTCModeDelay(int x){
	OCR0A=199;
	TCCR0A=0x02;
	TCCR0B=0x01;
	//for every second, 16M/200=80000=800x100
	for(int c=0;c!=x;++c){
		for(int a=0;a!=100;++a){
			for(int b=0;b!=800;++b){
				while((TIFR0&(1<<1))==0);
				TIFR0=(1<<OCF0A);
			}
		}
	}
	TCCR0B = 0;
}

void CTCModeDelay100ms(){
	OCR0A=199;
	TCCR0A=0x02;
	TCCR0B=0x01;
	//for every 1/10 second, 1.6M/200=8000=800x10
	for(int a=0;a!=10;++a){
		for(int b=0;b!=800;++b){
			while((TIFR0&(1<<1))==0);
			TIFR0=(1<<OCF0A);
		}
	}
	TCCR0B = 0;
}

void PORTC_blinking(){
	PORTC=0x01;
	for(int i=0;i!=10;++i){
		CTCModeDelay100ms();
		PORTC^=(1<<0);
	}
}

void set_interrupt_INT0(){
	EIMSK=0;//INT0,signal from PD2
	EICRA=0x01;//setup ISC0, logical change will trigger interrupt
}

//void set_interrupt_timer0compare(){ 
	//TIMSK0=(1<<OCIE0A);//enable timer0 compare match
//}

//ISR(TIMER1_COMPA_vect){
	//PORTC^=(1<<2);
//}

ISR(INT0_vect){
	++count;
	if(count==3){
		PORTC^=(1<<5);
		count=0;
	}
}


int main(void)
{
    /* Replace with your application code */
	DDRB=0x3F;
	DDRC=0xFF;//0x04
	//set_interrupt_timer0compare();
	set_interrupt_INT0();
	sei();
	
    while (1) {
		//1
		PORTC=0x02;//light1(red)
		PORTB=0x0C;//light2(green) light3(red)0c
		CTCModeDelay(5);
		
		//2
		PORTC=0x02;
		PORTB=0x14;
		CTCModeDelay(1);
		
		//3
		PORTC=0x02;
		PORTB=0x24;
		CTCModeDelay(1);
		
		//4
		PORTC=0x02;
		PORTB=0x26;
		CTCModeDelay(1);
		
		//5
		PORTB=0x21;
		PORTC=0x01;
		CTCModeDelay(5);
		
		//6
		PORTB=0x22;
		PORTC_blinking();
		//1 second delay has already done in function 'PORTC_blinking()'
		
		//7
		PORTB=0x24;
		PORTC=0x02;
		CTCModeDelay(1);
		
		//8
		PORTB=0x34;
		PORTC=0x02;
		CTCModeDelay(1);

	}
}

