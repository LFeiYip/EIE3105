/*
 * lab4a.c
 *
 * Created: 3/11/2021 下午2:25:03
 * Author : Fei
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
//
//char a=0;
//
//ISR(USART_RX_vect){
	//a=UDR0;
//}
//
//ISR(USART_UDRE_vect){
	//UDR0=a;
//}
//
//int main(void)
//{	
	//UCSR0B=(1<<TXEN0)|(1<<RXEN0)|(1<<RXCIE0)|(1<<UDRIE0);//enable receiver, transmitter and enable their interrupt
	//UCSR0C=(1<<UCSZ01)|(1<<UCSZ00);
	//UBRR0L=0xCF;//(1000000/16/4800)-1=207=0xCF
    //sei();
    //while (1) 
    //{
    //}
//}


char a=0;

void usart_init(void){
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);   // Turn on the transmission and reception circuitry
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01); // Use 8-bit character sizes
	UBRR0L=0xCF;//(1000000/16/4800)-1=207=0xCF
}

char usart_get(){
	while ((UCSR0A&(1<<RXC0))==0);
	a=UDR0;
	return a;
}

void usart_send(unsigned char ch){
	while((UCSR0A&(1<<UDRE0))==0);
	UDR0=ch;
}

int main(void){
	usart_init();
	while (1)
	{
		usart_send(usart_get());
	}
}



//#include <avr/io.h>
//#include <util/delay.h>
//
//
//#define USART_BAUDRATE 2400
//#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
//
//
//#define bit_get(p,m) ((p) & (m))
//#define bit_set(p,m) ((p) |= (m))
//#define bit_clr(p,m) ((p) &= ~(m))
//#define bit_flip(p,m) ((p) ^= (m))
//#define bit_write(c,p,m) (c ? bit_set(p,m) : bit_clear(p,m))
//#define BIT(x) (0x01 << (x))
//
//
//int main(void)
//{
	//char ReceivedByte;
//
	//UCSR0B |= (1 << RXEN0) | (1 << TXEN0);   // Turn on the transmission and reception circuitry
	//UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01); // Use 8-bit character sizes
//
	//UBRR0H = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register
	//UBRR0L = BAUD_PRESCALE; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register
//
	//for (;;) // Loop forever
	//{
		//while ((UCSR0A & (1 << RXC0)) == 0) {}; // Do nothing until data have been received and is ready to be read from UDR
		//ReceivedByte = UDR0; // Fetch the received byte value into the variable "ByteReceived"
//
		//while ((UCSR0A & (1 << UDRE0)) == 0) {}; // Do nothing until UDR is ready for more data to be written to it
		//UDR0 = ReceivedByte; // Echo back the received byte back to the computer
	//}
//}

