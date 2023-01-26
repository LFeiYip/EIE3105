/*
 * lab2a.c
 *
 * Created: 29/9/2021 上午10:20:54
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
	for(int i=0;i!=100;i++){
		for(int j=0;j!=625;j++){
			while((TIFR0&=(1<<TOV0))==0);//256mc
			TIFR0=(1<<TOV0);
			}
	}
	TCCR0B=0;	
}

void T0ctcDelay(){
	
}
int main(void){
	DDRB=0x01;
	
    while (1) {
		T0Delay();
		//T0ctcDelay();
		PORTB=(1<<0);
		char a=PORTB;
		a!=a;
		PORTB=0;
		T0Delay();
		//T0ctcDelay();
		PORTB=a;
}
}

