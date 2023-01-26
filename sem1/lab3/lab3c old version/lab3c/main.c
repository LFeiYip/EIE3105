/*
 * lab3c.c
 *
 * Created: 16/10/2021 下午9:04:46
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
	PORTC|=(1<<4);
	for(int i=0;i!=10;++i){
		CTCModeDelay100ms();
		PORTC^=(1<<4);
	}
}

void set_interrupt_INT0(){
	EIMSK|=0;//INT0,signal from PD2
	EICRA|=0x01;//setup ISC0, logical change will trigger interrupt
}

void set_interrupt_INT1(){
	EIMSK|=0x02;
	EICRA|=0x04;
}

//void set_interrupt_timer0compare(){
	//TIMSK0=(1<<OCIE0A);//enable timer0 compare match
//}

ISR(INT0_vect){
	++count;
	if(count==3){
		PORTC^=(1<<0);
		count=0;
	}
	//PORTB^=0xFF;
	//PORTC=PORTC^((1<<4)&(1<<5));
}

ISR(INT1_vect){
	PORTB^=0xFF;
	PORTC=PORTC^((1<<4)&(1<<5));
	//++count;
	//if(count==3){
		//PORTC^=(1<<0);
		//count=0;
	//}
}

int main(void)
{
	/* Replace with your application code */
	DDRB=0x3F;
	DDRC=0xFF;//0x04
	//set_interrupt_timer0compare();
	set_interrupt_INT0();
	set_interrupt_INT1();
	sei();
	
	while (1) {
		//1
		PORTC|=(1<<4)&(1<<5);//light1(red)(1<<4)&(1<<5)  0x20
		PORTB=0x0C;//light2(green) light3(red)0c
		CTCModeDelay(5);
		
		//2
		PORTC|=(1<<4)&(1<<5);//0x20
		PORTB=0x14;
		CTCModeDelay(1);
		
		//3
		PORTC|=(1<<4)&(1<<5);
		PORTB=0x24;
		CTCModeDelay(1);
		
		//4
		PORTC|=(1<<4)&(1<<5);
		PORTB=0x26;
		CTCModeDelay(1);
		
		//5
		PORTB=0x21;
		PORTC|=(1<<4);//0x10
		CTCModeDelay(5);
		
		//6
		PORTB=0x22;
		PORTC_blinking();
		//1 second delay has already done in function 'PORTC_blinking()'
		
		//7
		PORTB=0x24;
		PORTC|=(1<<4)&(1<<5);
		CTCModeDelay(1);
		
		//8
		PORTB=0x34;
		PORTC|=(1<<4)&(1<<5);
		CTCModeDelay(1);

	}
}
