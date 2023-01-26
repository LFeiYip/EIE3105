/*
 * Quiz3AQ1.c
 *
 * Created: 17/11/2021 上午10:07:52
 * Author : Fei
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define X ((16000000/16/9600) - 1)

int state=0;
char a=0;
ISR(USART_UDRE_vect){
	if (state==1)
	{
		UDR0='A';
		state++;
	}
	if (state==2)
	{
		UDR0=a;
		state++;
	}
	
	if (state==3)
	{
		while(!(UCSR0A&(1<<UDRE0)));
		UDR0='a';
		state=0;
	}
}
ISR(USART_RX_vect){
	if (state==0)
	{
		a=UDR0;
		state=1;
	}

}

int main(void){
	UBRR0 = X;
	//transmit and receive enable
	UCSR0B = (1 << TXEN0)| (1 << UDRIE0) | (1 << RXEN0) | (1 << RXCIE0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  //8 bit data format
	sei();

	while (1);
}





