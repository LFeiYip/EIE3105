/*
 * GccApplication1.c
 *
 * Created: 9/14/2022 5:47:03 PM
 * Author : 19052736d
 */ 

#include <avr/io.h>

void send(char data) {
	while( !( UCSR0A & (1<<UDRE0)) );
	UDR0 = data;
}

char re() {
	while( !( UCSR0A & (1<<UDRE0)) );
	return UDR0;
}

void tim0_init(){
	//timer0 generate PWM
	TCCR0A = (1<<COM0A1)|(0<<COM0A0)|(1<<COM0B1)|(0<<COM0B0)|(1<<WGM01)|(1<<WGM00);
	TCCR0B = (1<<WGM02)|(0<<CS02)|(1<<CS01)|(1<<CS00);//PRESCALING 64
	OCR0A = 250;//500Hz
	OCR0B = 125;//50% DUTY CYCLE
}

void tim1_init(){
	//timer 1 capture PWM
	TCCR1A =0;
	TCCR1B=(1<<ICES1)|(0<<CS12)|(1<<CS11)|(1<<CS10);
	TIFR1 = (1<<ICF1);
}

void usart_init(){
	UCSR0B=(1<<TXEN0)|(1<<RXEN0);
	UCSR0C=(1<<UCSZ01)|(1<<UCSZ00);	
	UBRR0L =(16000000/16/9600) - 1;
}

char check_pulse_width(){
	while((TIFR1&(1<<ICF1))==0);
	unsigned char t1= ICR1L;
	TIFR1=(1<<ICF1);
	TCCR1B=(0<<ICES1)|(1<<CS12)|(0<<CS11)|(0<<CS10);
	while((TIFR1&(1<<ICF1))==0);
	unsigned char c=ICR1L-t1;
	TIFR1=(1<<ICF1);
	return c;
}

int main(void)
{
    /* Replace with your application code */
	tim0_init();
	tim1_init();
	usart_init();
	DDRB=0x00; //pb0 input
	DDRD = 0b00100000;

	while(1){
		unsigned char c=check_pulse_width();
		send(c/10+ '0');
		send(c%10+ '0');
		send(' ');
	}
	

}

