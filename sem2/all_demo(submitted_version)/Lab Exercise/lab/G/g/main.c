#include <avr/io.h>
#include <avr/interrupt.h>
#define  X ((16000000/16/9600) - 1)
unsigned char h,l;
int ADCnum=0;

void init();

int main(void)
{
	/* Replace with your application code */
	init();
	while (1)
	{
	}
}

void init(){
	
	UBRR0L = X;
	
	TCCR0A = (1<<WGM00) | (1<<WGM01) | (0<<COM0A0) | (0<<COM0B0) | (1<<COM0B1);
	TCCR0B = (1<<WGM02) | (0<<CS00) | (0<<CS01) | (1<<CS02);   //pre-scalar 256
	OCR0A = 125;

	TCCR1A = (1<<COM1A1)|(1<<COM1B1)|(1<<WGM11)|(1<<WGM10);
	TCCR1B = (1<<WGM13)|(1<<WGM12)|(1<CS12);
	OCR1A = 125L;

	TCCR2A = (1<<COM2A1)|(1<<COM2B1)|(1<<WGM21)|(1<<WGM20);
	TCCR2B = (1<<WGM22)|(1<<CS22)|(1<<CS21);
	OCR2A = 125;

	DDRB |= (1<<2);
	DDRD |= (1<<5)|(1<<3);
	DDRC = (~(1<<0))&(~(1<<1))&(~(1<<2));

	ADCSRA= (1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	ADMUX = (1<<REFS1)|(1<<REFS0)|(1<<ADLAR);
	sei();
	ADCSRA |= (1<<ADSC);
}

ISR(ADC_vect){
	
	l = ADCL;
	h = ADCH;
	if (ADCnum==0){
		if (h < 0xB1){
			OCR0B = 0;
		}
		else{
			OCR0B =125;
		}
		ADMUX |= (1<<MUX0);
		ADCnum = 1;
	}
	else if (ADCnum==1){
		if (h < 0xB1){
			OCR1B = 0;
		}
		else{
			OCR1B = 125;
		}
		ADMUX &= ~(1<<MUX0);
		ADMUX |= (1<<MUX1);
		ADCnum=2;
	}
	else if(ADCnum==2){
		if (h < 0xC0){
			OCR2B = 0;
		}
		else{
			OCR2B=125;
		}
		ADMUX &= ~(1<<MUX1);
		
		ADCnum=0;
	}
	ADCSRA |= (1<<ADSC);
}
