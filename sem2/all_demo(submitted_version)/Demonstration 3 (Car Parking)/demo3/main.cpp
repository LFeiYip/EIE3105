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

//remote
//   G   x
//  D@C H@P
//   F   `


int main(void) {
	wheel(STOP, 0);
	while(1){
		wait(0);
		if(getDistance()<60){
			wheel(STOP, 0);
		}
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

void led(void), button(void), update_pwm(char);
void poll(unsigned tick) { //tick increments every 2.5 ms
  static unsigned t;
  /* do something here */
  if (t == tick) return;
  t = tick;
  update_pwm(getPath());
  led(); button();
  display(t);
}

void on_button(bool b) {
	wheel(b ? FORWARD : STOP, 10);		// speed value is ignored in STOP
}

