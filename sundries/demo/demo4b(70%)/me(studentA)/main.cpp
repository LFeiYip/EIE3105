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
  while(state==0){
		follow_inner_edge();
		wait(0);
	}

	while(state==1){
		error=0;
		wait(0);
	}
	
	while(state==2){
		error=0;
		wait(0);
	}
	
	while(state==3){
		wait(0);
		error=1;
	}
	
	while(state==4){
		wait(0);
		classic_linetrack();
	}
	while(state==5){
		pwmLeft(0);
		pwmRight(0);
	}
	while(state==6){
		wait(0);
		classic_linetrack();
	}
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

 