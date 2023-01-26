/* isr.c */
#include <avr/interrupt.h>

enum led_state{ON, OFF, NORMAL, FAST, SLOW};
void wait_ms(unsigned int t){}
void led(enum led_state s){}
int battery_low(void){return 0;}
int battery_full(void){return 1;}
void shutdown(void){TCCR0B=UCSR0B=DDRB=ADCSRA=0;}
	
void init(void){
	DDRB=0x28;
	DDRD=0x02;
	PORTD=0x0c;
	TCCR0A=2;
	0CR0A=249;	//1ms
	UBRR0=103;
	TIMSK0=2;
	ADMUX=14;
	ADCSRA=0X87;
	TCCR0B=3;
	UCSR0B=_BV(TXEN0);
	sei();
}

ISR(TIMER0_COMPA_vect){
	static int count;
	if (++count>999)
	{
		count=0;
		PINB=_BV(3);
	}
}