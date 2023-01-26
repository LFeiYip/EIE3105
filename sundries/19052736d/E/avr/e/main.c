#include <avr/io.h>
#include <string.h>
#define  X ((16000000/16/9600) - 1)

void init();
void send(char data);
unsigned char receive(void);

int main(void)
{
	init();
	unsigned char a[] = " Input value: ";
	unsigned int p = 0;
	unsigned char temp;
	
	while (1)
	{
		
		
		while(p < 10) {
			temp = receive();
			if(temp>= '0' && temp <= '9') {
				p = p * 10 + temp - '0';
			}
		}

		for(int i=0;i<16;i++)
		{
			send(a[i]);
		}

		send(p / 10 + '0');
		send(p % 10 + '0');
		OCR0B=p-1;
		p= 0;

	}
}


void init(){
	
	UCSR0B=(1<<TXEN0)|(1<<RXEN0);
	UCSR0C=(1<<UCSZ01)|(1<<UCSZ00);
	UBRR0L = X;
	
	TCCR0A = (1<<WGM00) | (1<<WGM01) | (0<<COM0A0) | (0<<COM0B0) | (1<<COM0B1);
	TCCR0B = (1<<WGM02) | (0<<CS00) | (0<<CS01) | (1<<CS02);   //pre-scalar 256
	
	OCR0A = 125;  // frePWM=16000000/125*256=500
	OCR0B = 62;
	DDRD=0xff;
	
}

unsigned char receive(void){
	while( !( UCSR0A & (1<<RXC0)) );
	return UDR0;
}


void send(char data) {
	while( !( UCSR0A & (1<<UDRE0)) );
	UDR0 = data;
}
