/*
 * FTAQ5.c
 *
 * Created: 30/11/2021 上午9:26:00
 * Author : Fei
 */ 
//Yip Lung Fei
//19052736d


#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdbool.h>
#define X ((16000000/16/9600) - 1)

bool start=true;
char prologue[]="FTAxx";
char rec[]="Received!";
char res[]="Resume!";
char w[]="Wrong!";
int i=0;//for counting prologue
int j=0;//count for r
char a=0;//save the first character
char b=0;//save the second character
int output_enable=0;//indicate whether output "Bye!"
int count=0;
int state=0;
int on=1;
int wrong=0;
int flag=1;
int state1s=0;
int stop=0;

void set_timer1(){
	OCR1A=0xF424;
	TCCR1B=0x0C;//timer 1 CTC mode with prescaler 256, trigger interrupt every 1s
	TIMSK1=(1<<OCIE1A);
}

ISR(TIMER1_COMPA_vect){
	if (flag!=0)
	{
		flag--;
	}
	else if(flag==0){
		flag=1;
	}
	stop=0;
}
void delay(){
	while(flag==1);
}
ISR(USART_UDRE_vect){
		if ((on==1)&(stop==0)){
			UDR0=prologue[i++];
			if (i==strlen(prologue))
			{
				start=false;
				i=0;
				state1s=1;
				stop=1;
			}
		}
		if (wrong==1)
		{
			UDR0=w[j++];
			if (j==strlen(w))
			{
				j=0;
				output_enable=0;
				state=0;
				wrong=0;
			}
		}
		if (output_enable==1)
		{
			if (state==1)
			{
				on=0;
				UDR0=rec[j++];
				if (j==strlen(rec))
				{
					j=0;
					output_enable=0;
					state=0;
				}
			}else if (state==2)
			{
				UDR0=res[j++];
				if (j==strlen(res))
				{
					j=0;
					output_enable=0;
					state=0;
					on=1;
				}
			}
		}
}
ISR(USART_RX_vect){
	count+=1;
	if (count==1)
	{
		a=UDR0;
	}
	else if ((count==2)&(a=='A'))
	{
		b=UDR0;
		if ((a=='A')&(b=='B'))
		{
			output_enable=1;
			state=1;
		}
		else{
			count=1;
			a=b;
		}
	}
	else if ((count==2)&(a=='C'))
	{
		b=UDR0;
		if ((a=='C')&(b=='D'))
		{
			output_enable=1;
			state=2;
		}
		else{
			count=1;
			a=b;
		}
	}
	else{
		count=0;
		wrong=1;
	}
}

int main(void)
{
	UBRR0 = X;
	//transmit and receive enable
	UCSR0B = (1 << TXEN0)| (1 << RXEN0) | (1 << RXCIE0) | (1<<UDRIE0);//(1 << TXCIE0) debugde了快两个小时，愣是不知道哪里出了问题，最后试着把这个删掉，就成了
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  //8 bit data format
	set_timer1();
	sei();
	while (1);
}

