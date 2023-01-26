/*
 * lab4b.c
 *
 * Created: 3/11/2021 下午7:52:43
 * Author : Fei
 */ 

#include <avr/io.h>
#include <string.h>

#define X ((16000000/16/4800) - 1)


int main(void){

	char prologue[]="We Are Ready!";
	char r[]= "Bye!";
	int count=0;
	UBRR0 = X;
	//transmit and receive enable
	UCSR0B = (1 << TXEN0)| (1 << TXCIE0) | (1 << RXEN0) | (1 << RXCIE0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  //8 bit data format
	char a=0;
	char b=0;
	
	for (int i = 0; i < strlen(prologue); i++){
		while (( UCSR0A & (1<<UDRE0))  == 0){};
		UDR0 = prologue[i];
	}

	while (1){

		while (( UCSR0A & (1<<RXC0))  == 0){};
		count++;
		if (count==1)
		{
			a=UDR0;
		}
		//else if (count==2)
		//{
			//b=UDR0;
			//if ((a=='H')&(b=='i'))
			//{
				 //for (int i = 0; i < strlen(r); i++){
					 //while (( UCSR0A & (1<<UDRE0))  == 0){};
					 //UDR0 = r[i];
				 //}
			//}
		//}
		//有问题，如果ab错位就会出错
		else if ((count==2)&(a=='H'))
		{
			b=UDR0;
			if ((a=='H')&(b=='i'))
			{
				for (int i = 0; i < strlen(r); i++){
					while (( UCSR0A & (1<<UDRE0))  == 0){};
					UDR0 = r[i];
				}
			}
		}
		else{
			count=0;
		}
	}
}


//void set_serial(){
	//UCSR0B=(1<<RXEN0)|(1<<TXEN0);
	//UCSR0C=(1<<UCSZ01)|(1<<UCSZ00);
	//UBRR0L=0xCF;//UBRR0 doesn't work but UBRR0L work, why?
//}
//
//void prologue(){
	//unsigned char a[]="We Are Ready!";
	//for (int i=0;i!=13;i++)
	//{
		//while ((UCSR0A&(1<<UDRE0))==0);
		//UDR0=a[i];
	//}
//}
//int main(void)
//{	
	//set_serial();
	//prologue();
	//char str[3];
	//char ch[1];
	//char response[]="Bye!";
    //
    //while (1) 
    //{
		//while (1){
			//while ((UCSR0A&(1<<RXC0))==0);
			//ch[0]=UDR0;
			//strcpy(str,ch);
			//for (int a=0;a<strlen(str);a++){
				//if ((str[a]=='H')&(str[a+1]=='i')){
					//break;
				//}
			//}
		//}
		//str=[0];	
		//for (int i=0; i<strlen(response);i++){
			//while ((UCSR0A&(1<<UDRE0))==0);
			//UDR0=response[i];
			//}
			//
	//}
//}

