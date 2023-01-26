/*
 * GccApplication1.c
 *
 * Created: 16/09/2022 18:38:43
 * Author : Administrator
 */ 

//#include <avr/io.h>
//#include <avr/interrupt.h>
//#include <stdio.h>
//
//void send(char);
//char a;
//int adc=0;
//
//ISR(ADC_vect){
	//a = ADCH;
	//ADCSRA |= (1<<ADSC); //start conversion
//}
//
//void send(char data) {
	//while( !( UCSR0A & (1<<UDRE0)) );
	//UDR0 = data;
//}
//
//char re() {
	//while( !( UCSR0A & (1<<UDRE0)) );
	//return UDR0;
//}
//
//void usart_init(){
	//UCSR0B=(1<<TXEN0)|(1<<RXEN0);
	//UCSR0C=(1<<UCSZ01)|(1<<UCSZ00);
	//UBRR0L =(16000000/16/9600) - 1;
//}
//
//int main(void)
//{
	//usart_init();
	//
	//TCCR0A = (1<<COM0A1)|(0<<COM0A0)|(1<<COM0B1)|(0<<COM0B0)|(1<<WGM01)|(1<<WGM00);
	//TCCR0B = (1<<WGM02)|(0<<CS02)|(1<<CS01)|(1<<CS00);//PRESCALING 64
	//OCR0A = 124;//500Hz
	//
	//TCCR1A = (1<<COM1A1)|(1<<COM1B1)|(1<<WGM11)|(1<<WGM10);
	//TCCR1B = (1<<WGM13)|(1<<WGM12)|(1<CS12);
	//OCR1A = 125L;
//
	//TCCR2A = (1<<COM2A1)|(1<<COM2B1)|(1<<WGM21)|(1<<WGM20);
	//TCCR2B = (1<<WGM22)|(1<<CS22)|(1<<CS21);
	//OCR2A = 125;
	//
	//DDRD |= (1<<5) | (1<<3);//pd5-oc0b, pb3-oc2b
	//DDRB |=(1<<2);//pb2-oc1b
	//
	//DDRB = 0xFF;
	//DDRD = 0xFF;
	//DDRC = 0;
	//sei();
	//ADCSRA = 0x8F;
	//ADMUX = (1<<MUX0)|(1<<REFS1)|(1<<REFS0)|(1<<ADLAR); //left adjusted,2.65V
	////
	//
	//ADCSRA |=(1<<ADSC);
    ///* Replace with your application code */
	//char previous=0;
    //while (1) 
    //{
		////if(a!=previous){
			//send((a&0b00000001)+'0');
			//send((a&0b00000010)+'0');
			//send((a&0b00000100)+'0');
			//send((a&0b00001000)+'0');
			//send((a&0b00010000)+'0');
			//send((a&0b00100000)+'0');
			//send((a&0b01000000)+'0');
			//send((a&0b10000000)+'0');
			//send(' ');
		////}
		////previous=a;
		////have light 024xxxxx
		////dark 1208xxxx
		//
		//if(adc==0){
			//if (a < 0xB1){
				//OCR0B = 0;
			//}
			//else{
				//OCR0B =125;
			//}
			//ADMUX &=(1<<MUX1);
		//}
		//
		//if(adc==1){
			//if (a < 0xB1){
				//OCR1B = 0;
			//}
			//else{
				//OCR1B =125;
			//}
			//ADMUX &=(1<<MUX2);
		//}
		//
		//if(adc==2){
			//if (a < 0xB1){
				//OCR2B = 0;
			//}
			//else{
				//OCR2B =125;
			//}
			//ADMUX &=(1<<MUX0);
		//}
		//adc++;
		//if(adc>=3)adc=0;
    //}
//}










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
			if (ADCnum==0){
				if (h < 0xB1){
					OCR0B = 0;
				}
				else{
					OCR0B =125;
				}
				ADMUX &= ~(1<<MUX2);
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
				ADMUX |= (1<<MUX2);
				ADCnum=0;
			}
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
	ADCSRA |= (1<<ADSC);
}
