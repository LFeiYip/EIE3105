/*
 * quiz1aq2.c
 *
 * Created: 20/10/2021 上午10:18:17
 * Author : Fei
 */ 

#include <avr/io.h>

void CTCModeDelay(int x){
	OCR0A=199;
	TCCR0A=0x02;
	TCCR0B=0x01;
	//for every second, 16M/200=80000=800x100
	for(int c=0;c!=x;++c){
		for(int a=0;a!=100;++a){
			for(int b=0;b!=800;++b){
				while((TIFR0&(1<<1))==0);
				TIFR0=(1<<OCF0A);
			}
		}
	}
	TCCR0B = 0;
}

void setup(){
	DDRC=0xFF;
	TCCR1A=0;
	TCCR1B=0x0F;//CTC mode,clock on rising edge //0x0F work
	OCR1A=0x02;//count 3, form 0 to 2
}


void stage1(){
	CTCModeDelay(1);
	PORTC=0x03;
	CTCModeDelay(1);
	PORTC=0x01;
	CTCModeDelay(1);
	PORTC=0;  
	CTCModeDelay(1);
	PORTC=0x02;
	
}
	
void stage2(){
	CTCModeDelay(1);
	PORTC=0;
	CTCModeDelay(1);
	PORTC=0x03;
	CTCModeDelay(1);
	PORTC=0x01;
	CTCModeDelay(1);
	PORTC=0x02;
	
}
int main(void)
{
	setup();
	int count=0;
	while(1)
	{
		do 
		{
			if(count==0){
				stage1();
				++count;
			}
			if(count!=0){
				stage2();
				count=0;
			}
		} while ((TIFR1&(1<<OCF1A))==0);
		

	}
}
