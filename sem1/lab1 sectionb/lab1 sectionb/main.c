/*
 * lab1 sectionb.c
 *
 * Created: 18/9/2021 上午12:22:49
 * Author : Fei
 */ 

#include <avr/io.h>

void T0Delay(){ 
	TCNT0=0;
	TCCR0A=0;
	TCCR0B=0x01;
	//1 machine cycle=1/16MHz=0.025us
	//from 0 to FF, there are 255+1=256 machine cycle
	//a whole preiod of timer0 last 0.0625*256=16us
	//1/16us=62500 machine cycle
	for(int i=0;i!=40;i++){
		for(int j=0;j!=625;j++){
			while((TIFR0&=(1<<TOV0))==0);//256mc
			TIFR0=(1<<TOV0);
			}
	}
	TCCR0B=0;
	
}
int main(void){
	DDRB=0x01;
	DDRD=0xFF;
	int count=0;
	
    while (1) {
		if(PINB&(1<<0)){
			T0Delay();
			++count;
			if((count%2)!=0){
				PORTD=0xFF;
			}
			else{
				PORTD=0;
			}
		}
	}
}


