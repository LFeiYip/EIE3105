/*
 * lab4d_b_revised.c
 *
 * Created: 10/11/2021 下午10:31:08
 * Author : Fei
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdbool.h>
#define X ((16000000/16/4800) - 1)

bool start=true;
char prologue[]="We Are Ready!";
char r[]="Bye!";
int i=0;//for counting prologue
int j=0;//count for r
char a=0;//save the first character
char b=0;//save the second character
int output_enable=0;//indicate whether output "Bye!"
int count=0;

ISR(USART_UDRE_vect){
	if (start==true){
		UDR0=prologue[i++];//udr0=prologue[a],then a+1
		if (i==strlen(prologue))
		{
			start=false;
			i=0;
		}
	}
	if (output_enable==1)
	{
		UDR0=r[j++];
		if (j==strlen(r))
		{
			j=0;
			output_enable=0;
		}
	}
}
ISR(USART_RX_vect){
	count+=1;
	if (count==1)
	{
		a=UDR0;
	}
	else if ((count==2)&(a=='H'))
	{
		b=UDR0;
		if ((a=='H')&(b=='i'))
		{
			output_enable=1;
			//UDR0='T';
		}
		else{
			count=1;
			a=b;
		}
	}
	else{
		count=0;
	}
}

int main(void)
{
    UBRR0 = X;
    //transmit and receive enable
    UCSR0B = (1 << TXEN0)| (1 << RXEN0) | (1 << RXCIE0) | (1<<UDRIE0);//(1 << TXCIE0) debugde了快两个小时，愣是不知道哪里出了问题，最后试着把这个删掉，就成了 
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  //8 bit data format
    sei();
    while (1);
}

