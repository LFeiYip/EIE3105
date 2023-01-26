/*
 * lab4d_c.c
 *
 * Created: 11/11/2021 下午2:15:06
 * Author : Fei
 */ 

#include <avr/io.h>
#include <string.h>
#include <avr/interrupt.h>

#define X ((16000000/16/9600) - 1)

int state=0;
char a=0;
int count=0;
char b=0;
ISR(USART_UDRE_vect){
	//state0: keep output "a"
	if (state==0)
	{
		UDR0='a';
	}
	
	//state1:output the input 10 times
	if ((state==1)&(count!=10))
	{
		++count;
		UDR0=a;
		if (count==10)
		{
			state=2;
			count=-1;
		}
	}
	if (state==2)
	{
		if (b==a){
			state=0;
			a=b=0;
			}
	}
}
ISR(USART_RX_vect){
	if (state==0)
	{
		a=UDR0;
		state=1;
	}
	if (state==2)
	{
		b=UDR0;
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



