#include <avr/io.h>
#include <string.h>
#define  X ((16000000/16/9600) - 1)

void init();
void send(char data);
int receive(void);


int main(void)
{
	
	unsigned char b[] = " The pulse width: ";
	unsigned char t1;
	char newline='\n';
	init();
	while (1) 
    {
		DDRB &= ~(1<<0); 
		PORTB=1;
		TCCR1A=0; 
		TCCR1B=(1<<ICES1)|(1<<CS12)| (0<<CS11) | (0<<CS10); //Rising edge, prescaler=256, no noise canceller
		TIFR1=(1<<ICF1);//Clear input capture flag 
		while((TIFR1&(1<<ICF1))==0); //wait until ICF1 is set 
		t1=ICR1L;
		
		TIFR1=(1<<ICF1);//Clear
		TCCR1B=(0<<ICES1) | (1<<CS12) | (0<<CS11) | (0<<CS10) ;//Falling edge, prescaler 256, no noise canceller
		while((TIFR1&(1<<ICF1))==0); //Wait
		t1=ICR1L-t1; 
		TIFR1=(1<<ICF1); //Clear 
		t1 *= 0.79;

		for(int i=0; i<17;i++){
			send(b[i]);
		}
			
		send(t1 / 10 + '0');
		send(t1 % 10 +'0');
		send(newline);

		
		
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



void send(char data) {
	while( !( UCSR0A & (1<<UDRE0)) );
	UDR0 = data;
}
