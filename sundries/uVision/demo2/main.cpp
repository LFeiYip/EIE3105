#include <stdio.h>

char SPI_data = 0;

void wait(unsigned int);   //background jobs are being serviced through this function
unsigned int getADC(void);
char getPath(void);
unsigned int getLeft(void);
unsigned int getRight(void);
void pwmLeft(unsigned int);
void pwmRight(unsigned int);
void setLeft(bool);
void setRight(bool);
int getDistance(void);

void line_track(char path);
void set_speed(unsigned v);

enum led_state { ON, OFF, NORMAL, FAST, SLOW };
enum led_color { BLUE, GREEN, YELLOW };
void led(led_color, led_state);

bool uart2_print(const char*);
bool uart3_print(const char*);
int uart2_read(void);          //return -1 for none
int uart3_read(void);

char c;
extern int count;
void classic_linetrack(void);
void follow_outer_edge(void);
void follow_inner_edge(void);
bool check_count(unsigned);
extern int error;
extern int flag;
extern int state;

int main(void) {
	wait(0);
  while(state==0){
		classic_linetrack();
		wait(0);
	}

	while(state==1){
		follow_inner_edge();
		wait(0);
	}
	
	while(state==2){
		follow_outer_edge();
		wait(0);
	}
//	while(check_count(3*120)){
//		classic_linetrack();
//		wait(0);
//	}
	while(state==3){
		follow_inner_edge();
		wait(0);
	}
	while(state==4){
		classic_linetrack();
		wait(0);
	}
	if(state==5){
		pwmLeft(0);
		pwmRight(0);
	}


//	while (1) {
////		follow_outer_edge();
//		classic_linetrack();
//		wait(1);//1=2.5ms
//  }
}

void on_button(bool b) {
  //static int state;
  if (b) {
    //if (++state > 2) state = 0;
    //unsigned int pwm = state == 2 ? 0 : 10000;
    pwmLeft(10000); pwmRight(10000);
    setLeft(1); // 1:forward    0://backward
    setRight(1);
  }
}

//void line_track(char path){
//	if(((path&8)&(path&16))|((path&4)&(path&8))|((path&16)&(path&32))){ //4 5 if one, go straight
//		//
//	}
//	else if ((path&64)|(path&128)){ //7,8 is one, turn left
//		turn_left();
//	}
//	else if ((path&1)|(path&2)){ //1,2 is one, turn right
//		turn_right();
//	}
//	 
//}
 
 