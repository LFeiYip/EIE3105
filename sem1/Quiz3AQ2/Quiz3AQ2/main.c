/*
 * Quiz3AQ2.c
 *
 * Created: 17/11/2021 上午10:35:57
 * Author : Fei
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
 
#define X ((16000000/16/9600) - 1)
char var='A';
int flag=0;
 
void set_timer1(){
	OCR1A=0xF424;
	TCCR1B=0x0C;//timer 1 CTC mode with prescaler 256, trigger interrupt every 1s
	TIMSK1=(1<<OCIE1A);
}

ISR(TIMER1_COMPA_vect){
	flag=1;
}

ISR(USART_RX_vect){
	var=UDR0;
	if(var>='a'&&var<='z')
	{
		var+=('A'-'a');
	}
}
ISR(USART_UDRE_vect){
	if (flag==1)
	{
		UDR0=var;
		flag=0;
	}
}

int main(void)
{
	set_timer1();
	UBRR0 = X;
	//transmit and receive enable
	UCSR0B = (1 << TXEN0)| (1 << UDRIE0) | (1 << RXEN0) | (1 << RXCIE0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  //8 bit data format
	sei();

    /* Replace with your application code */
    while (1) 
    {
    }
}

