#include <stdio.h>

void wait(unsigned);   //call poll while wait
bool uart3_print(const char*);
unsigned getADC(void), get_count(void), getDistance(void);
char getPath(void);
int uart2_read(void), uart3_read(void);

enum led_state { ON, OFF, NORMAL, FAST, SLOW };
enum led_color { BLUE, GREEN, YELLOW };
void led(led_color, led_state);

enum wheel_action { STOP, FORWARD, BACKWARD, LEFT, RIGHT };
void wheel(wheel_action, unsigned speed);		// speed<100: speed control; speed>100:direct pwm
bool check_count(unsigned);


void wheel_track(int);	//1:left, -1:right
void classic_linetrack(void);
void follow_inner_edge(void);
void pwmLeft(unsigned), pwmRight(unsigned);

int state=0;
int flag=0;
int mode=0;
int error=0;
char c;
int count=0;

int main(void){
	
	wheel(STOP,0);
	while(state==0)wait(0);
	
	wheel(LEFT,3);
	while(state==1)wait(0);
	
	wheel_track(1);
	while(state==2)wait(0);
	
	mode=1;
	
	while(state==3){
		wait(0);
		classic_linetrack();
	}
	
	while(state==4){
		wait(0);
		error=0;
	}
	
	while(state==5){
		wait(0);
		error=0;
	}
	
	while(state==6){
		wait(0);
		error=-1;
	}
	
	while(state==7){
		wait(0);
		classic_linetrack();
	}
	
	while(state==8){
		wait(0);
		//follow_inner_edge();
		classic_linetrack();
	}
	
	while(state==9){
		wait(0);
		error=0;
	}
	
	while(state==10){
		wait(0);
		error=0;
	}
	
	while(state==11){
		wait(0);
		error=1;
	}
	
	while(state==12){
		wait(0);
		classic_linetrack();
	}
	
	wheel(STOP,0);
	while(state==13)wait(0);
	
	
	wheel(FORWARD,1);
	while(state==14){
		wait(0);
		classic_linetrack();
	}
	
	wheel(STOP,0);
	while(state==15)wait(0);
	
	while(1){
		wait(0);
	}
}


static void display(unsigned t) {
  static char buffer[99];
  if (t & 31) return;
  sprintf(buffer, "\rpath=[xxxx xxxx] dist=%d count=%d batt=%d    ", getDistance(), get_count(), (getADC()*89)>>12);
  char c = getPath();
  buffer[7] = c & 1 ? '0' : '.';
  buffer[8] = c & 2 ? '1' : '.';
  buffer[9] = c & 4 ? '2' : '.';
  buffer[10] = c & 8 ? '3' : '.';
  buffer[12] = c & 16 ? '4' : '.';
  buffer[13] = c & 32 ? '5' : '.';
  buffer[14] = c & 64 ? '6' : '.';
  buffer[15] = c & 128 ? '7' : '.';
  uart3_print(buffer);
}

void led(void), button(void), update_pwm(char), check_state(void);
void poll(unsigned tick) { //tick increments every 2.5 ms
  static unsigned t;
  /* do something here */
  if (t == tick) return;
  t = tick;
	check_state();
  update_pwm(getPath());
  led(); button();
  display(t);
}

void check_state(){
	c=getPath();
	if(state==0){
		if(getDistance()>50){
			if(getDistance()<60)state=1;
		}
	}
	
	if(state==1){
		if((c&0x18)==0)flag=1;
		if(flag==1){
			if((c&0x18)==0x18){
				state=2;
				flag=0;
			}
		}
	}
	
//	if(state==2){
//		if(((c&0xFF)==0xFE)|((c&0xFF)==0xFF))state=3;
//	}
	if(state==2){
		if(check_count(120))state=3;
	}
	
//	if(state==3){
//		if((c&0xFF)==0x00)flag=1;
//		if(flag==1){
//			if((c&0xFF)!=0x00){
//				state=4;
//				flag=0;
//			}
//		}
//	}
	if(state==3){
		if(c&128)flag=1;
		if(flag==1){
			if(!(c&128)){
				state=4;
				flag=0;
			}
		}
	}
	
	if(state==4){
		if((c&0xFF)==0x00)flag=1;
		if(flag==1){
			if((c&0xFF)!=0x00){
				flag=0;
				state=5;
			}
		}
	}
	
	if(state==5){
		if((c&0xFF)==0x00)flag=1;
		if(flag==1){
			if(((c&0xFF)==0xFF) | ((c&0xFF)==0xF0)){
				flag=0;
				state=6;
			}
		}
	}
	
	if(state==6){
		//this state make sure the car go to the correct path
		if(((c&0xFF)==0x80) | ((c&0xFF)==0xC0))state=7;
	}
	
	if(state==7){
		if( (c&0xFF)==0x3F)flag=1;
		if(flag==1){
			if(!(c&1)){
				count++;
				flag=0;
			}
		}
		if(count==2){
			state=8;
			count=0;
			flag=0;
		}
	}
	
	if(state==8){
//		if(c&128)flag=1;
//		if(flag==1){
//			if(!(c&128)){
//				flag=2;
//			}
//		}

//		if(flag==2){
//			if(((c&0xFF)==0x3E) | ((c&0xFF)==0x1F))flag=3;
//		}
//		if(flag==3){
//			if(((c&0xFF)==0x0E) | ((c&0xFF)==0x0F)){
//				state=9;
//				flag=0;
//			}
//		}	
		if(((c&0xFF)==0x7C) | ((c&0xFF)==0xF8))flag=1;
		if(flag==1){
			if(!(c&128)){
				state=9;
				flag=0;
			}
		}
	}
	
	if(state==9){
		if((c&0xFF)==0x00)flag=1;
		if(flag==1){
			if(!((c&0xFF)==0x00)){
				state=10;
				flag=0;
			}
		}
	}
	
	if(state==10){
		if((c&0xFF)==0x00)flag=1;
		if(flag==1){
			if(!((c&0xFF)==0x00)){
				state=11;
				flag=0;
			}
		}
	}
	
	if(state==11){
		if((c&0xFF)==0x01)state=12;
	}
	
	if(state==12){
		if((getDistance()<60) & (getDistance()!=0))state=13;
	}
	
	if(state==13){
		if(getDistance()> 70)state=14;
	}
	
	if(state==14){
		if(check_count(250))state=15;
	}
}

void on_button(bool b) {
//	wheel(b ? FORWARD : STOP, 25000);		// speed value is ignored in STOP
}

