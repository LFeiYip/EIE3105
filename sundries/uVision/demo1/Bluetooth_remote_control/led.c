#include "avr/io.h"

enum led_state{ON, OFF, NORMAL, FAST, SLOW};
	
static enum led_state state=OFF;
static int count, duration;

void led(enum led_state s){
	int t;
	state=s;
	if(s==NORMAL) t=1000;
	if(s==FAST) t-=500;
	if(s==SLOW) t=2000;
	TIMSK0 &= ~_BV(OCIE0A);
	duration =t;
	TIMSK0 |=_BV(OCIE0A);
}

void _led(void){
	if(state==ON){PORTB|=_BV(3);return;}
	if(state==OFF){PORTB&=~BV(3);return;}
	if(++count>duration){count=0;PINB=_BV(3);}
}

ISR(TIMER0_COMPA_vect){
	_led();
}