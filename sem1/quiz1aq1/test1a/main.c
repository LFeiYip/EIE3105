/*
 * test1a.c
 *
 * Created: 20/10/2021 上午10:02:51
 * Author : Fei
 */ 

#include <avr/io.h>

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


int main(void)
{
    /* Replace with your application code */
	DDRB=0;
	DDRC=0xFF;
    while (1) 
    {
		PORTC=0x03;
		if(PINB&(1<<0)){
			while(1){
				PORTC=0x01;
				CTCModeDelay(1);
				PORTC=0;
				CTCModeDelay(1);
				PORTC=0x02;
				CTCModeDelay(1);
				PORTC=0x03;
				CTCModeDelay(1);
			}
		}
    }
}

