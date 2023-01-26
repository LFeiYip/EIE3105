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

enum led_state { ON, OFF, NORMAL, FAST, SLOW };
enum led_color { BLUE, GREEN, YELLOW };
void led(led_color, led_state);

bool uart2_print(const char*);
bool uart3_print(const char*);
int uart2_read(void);          //return -1 for none
int uart3_read(void);

char buffer[30];

int main(void) {
  while (1) {
    wait(40);
		char c = getPath();
    sprintf(buffer, "\r0123 4567   distance=%d   ", getDistance());
		buffer[1] = c & 1? '1' : '0';
		buffer[2] = c & 2? '1' : '0';
		buffer[3] = c & 4? '1' : '0';
		buffer[4] = c & 8? '1' : '0';
		buffer[6] = c & 16? '1' : '0';
		buffer[7] = c & 32? '1' : '0';
		buffer[8] = c & 64? '1' : '0';
		buffer[9] = c & 128? '1' : '0';
    uart3_print(buffer);
  }
}

void on_button(bool b) {
  static int state;
  if (b) {
    if (++state > 2) state = 0;
    unsigned int pwm = state == 2 ? 0 : 10000;
    pwmLeft(pwm); pwmRight(pwm);
    setLeft(state);
    setRight(state);
  }
}

//int main(void){
//	while(1){
//		wait(10);
//		int k=uart2_read();
//		if(k==-1)k=uart3_read();
//		if(k!=-1){
//			switch(k){
//				case'b':led(BLUE,OFF);break;
//				case'B':led(BLUE,ON);break;
//				default:led(BLUE,NORMAL);
//			}
//		}
//	}
//}

//void on_button(bool b){
//	if(b) uart2_print("uart2:hello\r\n");
//	else uart3_print("uart3:hello\r\n");
//}

//char buffer[20];

//void on_button(bool b){
//	if(b) uart3_print("uart2: hello\r\n");
//	else{
//		sprintf(buffer, "%d\r\n", getADC());
//		uart3_print(buffer);
//	}
//}
