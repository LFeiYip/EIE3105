/*main.c */

#include <avr/io.h>
#include <avr/interrupt.h>

//enum led_state{ON, OFF, NORMAL, FAST, SLOW};
//void init(void);
//void wait_ms(unsigned int);
//void led(enum led_state);
//int battery_low(void);
//int battery_full(void);
//void shutdown(void);
//
//int main(){
	//init();
	//led(ON);
	//wait_ms(1000);
	//while(!battery_low()) led(battery_full()?ON:FAST);
	//led(OFF);
	//shutdown();
	//while(1);
//}
void delay_200ms();
unsigned char keypad[4][2]={
							{'SW20','SW30'},
							{'SW21','SW31'},
							{'SW22','SW32'},
							{'SW2','SW3'},
};

//ISR(USART_UDRE_vect){
	//UDR0='G';
//}

void usart_init (void){
	UCSR0B=(1<<TXEN0) | (1<<RXEN0);
	UCSR0C=(1<<UCSZ01) | (1<<UCSZ00);
	UBRR0L=0X67;//baud rate 9600
}
void usart_send (unsigned char ch){
	while (! (UCSR0A & (1<<UDRE0)));
	UDR0=ch;
}

int main(void){
	unsigned char column;
	unsigned char row;
	DDRB|=0b00000111; //set pb0-pb2 as output pins
	DDRD&=0b11110011; //set pd2 and pd3 as input pins
	PORTB&=0b11111000; //pb0-pb2 output 0;
	PORTD&=0b11110011;  //pull-up pd2 and pd3 
	
	usart_init ();
	usart_send('a');
	while(1){
		usart_send('a');
		do 
		{
			PORTB&=0b11111000; //ground all rows at once
			column= (PIND & 0x0C); //read the column
		} while (column!=0x0C); //if pd2 and pd3 not equal to '11', break
		
		do 
		{
			do 
			{
				delay_200ms();
				column=(PIND&0x0C);
			} while (column==0x0C);
			
			delay_200ms();
			column=(PIND&0x0C);
		} while (column==0x0C);
		
		while(1){
			int count=0; //for distinguish SW2
			PORTB=0xFE; //ground pb0
			column=(PIND&0x0C);
			if (column!=0x0C)
			{
				count=1;
			}
			
			PORTB=0xFD; //ground pb1
			column=(PIND&0x0C);
			if (column!=0x0C)
			{
				count=2;
			}
			
			PORTB=0xFB; //ground pb2
			column=(PIND&0x0C);
			if (column!=0x0C)
			{
				count=3;
			}
			
			PORTB=0xFF;
			column=(PIND&0x0C);
			if (column!=0x0C)
			{
				count=4;
			}
			
			if (count==1)
			{
				row=1;
				break;
			}
			else if(count==2){
				row=2;
				break;
			}
			else if(count==3){
				row=3;
				break;
			}else{
				row=4;
				break;
			}
		}
			
		//save result to portD
		if (column==0x08)
		{
			PORTD=keypad[row][0];
		}
		else if(column==0x04){
			PORTD=keypad[row][1]
		}
		
		//if (PORTD=='SW20')
		//{
			//UDR0='a';
		//}
		
	}
	usart_send('a')	;	
	return 0;
}

void delay_200ms(){
	TCCR1A=0b00000000;
	TCCR1B=0b00001011;
	OCR1A=12500;
	
	unsigned char count=0;
	while(count<4){
		while(!(TIFR1&(1<<OCF1A)));
		TIFR1=(1<<OCF1A);
		count++;
	}
}