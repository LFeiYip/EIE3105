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

extern int state;
int mode=1;
extern int error;
char c;

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
	
	wheel(STOP,0);
	while(state==5){
		wait(0);
	}
	
	wheel(FORWARD,2);
	while(state==20){
		wait(0);
		classic_linetrack();
	}
	
	mode=0;
	wheel(RIGHT,2);
	while(state==6){
		wait(0);
	}
	
	wheel(STOP,0);
	while(state==7){
		wait(0);
	}
	
	wheel(LEFT,2);
	while(state==8){
		wait(0);
	}
	
	wheel(FORWARD,5);
	wait(0);
	mode=1;
	while(state==9){
		wait(0);
		classic_linetrack();
	}
	
	wheel(STOP,0);
	while(state==10)wait(0);
	
	while(1){
		wait(0);
	}
}


void on_button(bool b) {
	//static int state;
	if (b) {
		//if (++state > 2) state = 0;
		//unsigned int pwm = state == 2 ? 0 : 10000;
	wheel(FORWARD,5);
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
void read_sensor(void);
void poll(unsigned tick) { //tick increments every 2.5 ms
  static unsigned t;
  /* do something here */
  if (t == tick) return;
  t = tick;
	read_sensor();
  update_pwm(getPath());
  led(); button();
  display(t);
}


