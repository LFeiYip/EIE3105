
#include <avr/io.h>

void usart_init (void){
	UCSR0B=(1<<TXEN0) | (1<<RXEN0);
	UCSR0C=(1<<UCSZ01) | (1<<UCSZ00);
	UBRR0L=0X67;//baud rate 9600
}
void usart_send (unsigned char ch){
	while (! (UCSR0A & (1<<UDRE0)));
	UDR0=ch;
}
void delay_10ms()
{
	TCCR1A = 0x00; // CTC TOP = OCR1A
	TCCR1B = 0x0B; // Prescaler = 64
	OCR1A = 2500; //2500*(1/(16MHz/64))=10ms
	
	unsigned char count = 0;
	while (count < 1) 
	{
		while(!(TIFR1 & (1<<OCF1A))) ;
		TIFR1 = (1<<OCF1A);
		count++;
	}
}


int main(void)
{
	unsigned char colloc, rowloc=5, column=5;
	unsigned char state=0;
	unsigned int  flag;
	unsigned int count = 0;//to count the do while loop
	usart_init();
	
	DDRD= 0x00;
	PORTD=0xFF;
	DDRB=0xFF;
	PORTB=0x00;

	while (1) 
	{	
		do
		{
			PORTB = 0xF8; //ground all rows at once
			colloc=(PIND & 0x0C); //read the columns
		} while (colloc != 0x0C); //check until all keys released
		PORTB = 0xF8; //ground all rows at once
		state=1;
		do
		{
			state = 0;
			do
			{	
				if(count>=1)
				{
					if(state==0){
						usart_send('1');
						}	
				}
				count++;
				delay_10ms();  //call delay
				colloc=(PIND & 0x0C); //see if any key is pressed
			} while (colloc == 0x0C); //keep checking for key press
			colloc=(PIND & 0x0C); //read columns
			
		} while (colloc == 0x0C);
		
		count = 0;
		while(1)
		{
			flag=0;
			PORTB = 0xFE; //ground row 0
			delay_10ms();  //call delay
			colloc=(PIND & 0x0C); //read columns
			
			if(colloc != 0x0C) //column detected
			{
				rowloc=0;  //save row location
				if(colloc==0x08)	column=0;
				else				column=1;
				flag++;
			}
			
			PORTB=0xFD; //ground row 1
			delay_10ms();  //call delay
			colloc=(PIND & 0x0C); //read columns
			
			if(colloc != 0x0C) //column detected
			{
				rowloc=1;  //save row location
				if(colloc==0x08){column=0;}
				else{column=1;}
				flag++;
			}
			
			PORTB=0xFB; //ground row 2
			delay_10ms();  //call delay
			colloc=(PIND & 0x0C); //read columns
			
			if(colloc != 0x0C) //column detected
			{
				rowloc=2;  
				if(colloc==0x08)	column=0;
				else				column=1;
				flag++;
			}
			
			if(flag==3){
				if(colloc == 0x04){
					state = 1;
					usart_send('i');
					rowloc=3;
					break;
				}
				else if(colloc == 0x08){
					state = 1;
					usart_send('w');
					colloc=0x0C;
					rowloc=3;
					break;
				}
			}
			else  {break;}
			
		}

		if(column==0){
			state = 1;
			if(rowloc==0){
				usart_send('d');
			}
			if(rowloc==1){
				usart_send('s');
			}
			if (rowloc==2){
				usart_send('a');
			}
			
			
		}
		//column 1
		else if(column==1){
			state = 1;
			if(rowloc==0){
				usart_send('j');
			}
			if(rowloc==1){
				usart_send('l');
			}
			if(rowloc==2){
				usart_send('k');
			}
		}
		
	}
	return 0;
}

