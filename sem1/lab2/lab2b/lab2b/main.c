/*
 * lab2b.c
 *
 * Created: 29/9/2021 上午11:08:06
 * Author : Fei
 */
 
 
 
 
//For Section B part 2, just replace the Normal Mode function to CTC Mode function



#include <avr/io.h>

void NormalModeDelay(int x){
	TCNT0=0;//start counter from 0
	TCCR0A=0;
	TCCR0B=0x01;
	for(int z=0;z!=x;++z){
		for(int a=0;a!=10;++a){
			for(int y=0;y!=6250;++y){
				while((TIFR0&(1<<0))==0);//255mc+1mc=256mc
				TIFR0=(1<<TOV0);
				}
		}
	}
	TCCR0B=0;//stop timer
}

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

void NormalModeDelay100ms(){
	TCNT0=0;
	TCCR0B=0x01;
	for(int y=0;y!=6250;++y){
		while((TIFR0&(1<<0))==0);//255mc+1mc=256mc
		TIFR0=(1<<TOV0);
	}
	TCCR0B=0;
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
		NormalModeDelay100ms();
		//CTCModeDelay100ms();
		PORTC^=(1<<0);
	}	
}

int main(void)
{
    DDRB=0x3F;
	DDRC=0x03;
    while (1) 
    {
		//1
		PORTC=0x02;//light1(red)
		PORTB=0x0C;//light2(green) light3(red)0c
		NormalModeDelay(5);
		//CTCModeDelay(5);
		
		//2
		PORTC=0x02;
		PORTB=0x14;
		NormalModeDelay(1);
		//CTCModeDelay(1);
		
		//3
		PORTC=0x02;
		PORTB=0x24;
		NormalModeDelay(1);
		//CTCModeDelay(1);
		
		//4
		PORTC=0x02;
		PORTB=0x26;
		NormalModeDelay(1);
		//CTCModeDelay(1);
		
		//5
		PORTB=0x21;
		PORTC=0x01;
		NormalModeDelay(5);
		//CTCModeDelay(5);
		
		//6
		PORTB=0x22;
		PORTC_blinking();
		//1 second delay has already done in function 'PORTC_blinking()'
		
		//7
		PORTB=0x24;
		PORTC=0x02;
		NormalModeDelay(1);
		//CTCModeDelay(1);
		
		//8
		PORTB=0x34;
		PORTC=0x02;
		NormalModeDelay(1);
		//CTCModeDelay(1);
		
		//PORTB=0xFF;
		//delay(5);
		//PORTB=0;
		//delay(5);
    }
}

