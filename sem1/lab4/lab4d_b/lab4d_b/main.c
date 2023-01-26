/*
 * lab4d_b.c
 *
 * Created: 10/11/2021 下午12:59:34
 * Author : Fei
 */ 

#include <avr/io.h>
#include <string.h>
#include <avr/interrupt.h>

#define X ((16000000/16/4800) - 1)

char prologue[]="We Are Ready!";
char r[]= "Bye!";
char a=0;
char b=0;
char T=0;
char R=0;
int start=1;
int count=0;

//data register empty interrupt
//if empty, write to UDR
ISR(USART_UDRE_vect){
	UDR0=T;
	//UCSR0B &= ~(1 << UDRIE0);
}

//receive complete interrupt
ISR(USART_RX_vect){
	count++;
	R=UDR0;
}

int main(void){
	UBRR0 = X;
	//transmit and receive enable
	UCSR0B = (1 << TXEN0)| (1 << TXCIE0) | (1 << RXEN0) | (1 << RXCIE0) | (1<<UDRIE0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  //8 bit data format
	sei();

	while (1){

		//while (( UCSR0A & (1<<RXC0))  == 0){};
		//count++;
		if (count==1)
		{
			a=R;
		}
		else if ((count==2)&(a=='H'))
		{
			b=R;
			if ((a=='H')&(b=='i'))
			{
				for (int i = 0; i < strlen(r); i++){
					//while (( UCSR0A & (1<<UDRE0))  == 0){};
					T = r[i];
				}
			}
		}
		else{
			count=0;
		}
	}
}

