/*
 * lab4c.c
 *
 * Created: 10/11/2021 上午12:35:14
 * Author : Fei
 */ 

#include <avr/io.h>
#include <string.h>

#define X ((16000000/16/9600) - 1)


int main(void){

	int count=0;
	UBRR0 = X;
	//transmit and receive enable
	UCSR0B = (1 << TXEN0)| (1 << TXCIE0) | (1 << RXEN0) | (1 << RXCIE0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  //8 bit data format
	char a=0;
	char b=0;

	while (1){

		//while (count==0){
			//while (( UCSR0A & (1<<UDRE0))  == 0){};
			//UDR0='a';
			//if ((UCSR0A&(1<<RXC0))!=0){
				//a=UDR0;
				//count=1;
			//}
		//}
		do 
		{
			while (( UCSR0A & (1<<UDRE0))  == 0){};
			UDR0='a';
			if ((UCSR0A&(1<<RXC0))!=0){
				a=UDR0;
				count=1;
			}
		} while (count==0);
		
		//print a 10 times
		for (int i=0;i!=10;i++){
			while (( UCSR0A & (1<<UDRE0))==0){};
			UDR0=a;
		}
		
		//等待输入，持续将输入放入b
		while (1){
			while (( UCSR0A & (1<<RXC0))  == 0);
			b=UDR0;
			if (b==a){
				count=0;
				a=b=0;
				break;}
		}
	}
}


