/*main.c */

#include <avr/io.h>

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
unsigned char keypad[4][2]={
							{'SW20','SW30'},
							{'SW21','SW31'},
							{'SW22','SW32'},
							{'SW2','SW3'},
};
void delay_ms(int x){
	TCCR1A = 0x00; // CTC TOP = OCR1A
	TCCR1B = 0x01; // no prescaler
	//65536-16000=C180
	TCNT1H = 0xC1;
	TCNT1L = 0x80;
	//1 cycle 1ms
	unsigned char count = 0;
	while (count < x)
	{
		while(!(TIFR1 & (1<<TOV1))) ;
		TIFR1 = (1<<TOV1);
		count++;
	}
	TCCR1B=0;
}
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
	int col;
	unsigned int row;
	
	//DDRB|=0b00000111; //set pb0-pb2 as output pins
	//DDRD&=0b11110011; //set pd2 and pd3 as input pins
	//PORTB&=0b11111000; //pb0-pb2 output 0;
	//PORTD&=0b11110011;  //pull-up pd2 and pd3 
	
	DDRD= 0x00 ; //input PORTD2-3
	PORTD=0xFF;
	DDRB=0xFF; //output PORTB0-2
	PORTB=0x00;
	
	usart_init();
	//usart_send('a');
	while(1){
		do 
		{
			PORTB&=0b11111000; //ground all rows at once
			//delay_ms(50);
			column= (PIND & 0x0C); //read the column
			//usart_send('z'); //for debugging
		} while (column!=0x0C); //check if all keys are released
		
		do 
		{
			do
			{	
				//usart_send('y'); //for debugging
				delay_ms(15);
				column=(PIND & 0x0C);
			} while (column==0x0C);
			
			//usart_send('x'); //for debugging
			delay_ms(15);
			column=(PIND & 0x0C);
		} while (column==0x0C);
		
		while(1){
			int count=0; //for distinguish SW2
			
			PORTB=0xFE; //ground pb0
			delay_ms(10);
			column=(PIND&0x0C);
			if (column!=0x0C)
			{
				row=0;
				count++;
				if (column==0x08)
				{
					col=0;
				}
				else
				{
					col=1;
				}
				//usart_send('0');
			}
			
			PORTB=0xFD; //ground pb1
			delay_ms(10);
			column=(PIND&0x0C);
			if (column!=0x0C)
			{
				row=1;
				if (column==0x08)
				{
					col=0;
				}
				else
				{
					col=1;
				}
				count++;
				//usart_send('1');
			}
			
			PORTB=0xFB; //ground pb2
			delay_ms(10);
			column=(PIND&0x0C);
			if (column!=0x0C)
			{
				row=2;
				if (column==0x08)
				{
					col=0;
				}
				else
				{
					col=1;
				}
				count++;
				//usart_send('2');
			}
			

			if(count==3){
				row=3;
				//usart_send('3');
				break;
			}else {break;}
		}
		//usart_send('b')	;
		//save result to portD
		
		if (col==0)
		{
			if(row==0){
				usart_send('d');
			}
			else if(row==1){
				usart_send('s');
			}
			else if(row==2){
				usart_send('a');
			}
			else if(row==3){
				usart_send('w');
			}
			//PORTD=keypad[row][0];
		}
		else if(col==1){
			//PORTD=keypad[row][1];
			if(row==0){
				usart_send('j');
			}
			else if(row==1){
				usart_send('l');
			}
			else if(row==2){
				usart_send('k');
			}
			else if(row==3){
				usart_send('i');
			}
		}
		
	}

	return 0;
}

