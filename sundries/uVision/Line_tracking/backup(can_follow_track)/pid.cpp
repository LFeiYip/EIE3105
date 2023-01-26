#include <stm32f10x.h>

unsigned int getLeft(void);
unsigned int getRight(void);
void pwmLeft(unsigned int);
void pwmRight(unsigned int);
int set_error(int, int, int);

extern int error;
extern char c;
extern int count;

class Speed{
	public:
		Speed(void){last = speed8 = 0; }
		unsigned speed(unsigned cnt){
			unsigned u = cnt - last;
			last = cnt;
			unsigned s, s8 = speed8;
			for (s = u; s8; s8 >>= 4) s +=s8 & 15;
			speed8 <<=4;
			speed8 |=u;
			return s;
		}
	private:
		unsigned speed8, last;
} left, right;

class Pid{
	public:
		Pid(unsigned p, unsigned i, unsigned d):p(p), i(i),d(d){
			reset();
		}
		int control(int error){
			int delta = error - last;
			last = error;
			acc +=error;
			if (acc > MAX) acc= MAX;
			if (acc < MIN) acc= MIN;
			return error*p + acc / i + delta *d;
		}
		void reset(void){ acc = last = 0; }
	private:
		enum {MAX = 2123456789, MIN = -2123456789};
		unsigned p, i, d;
		int acc, last;
	} speed(10000,2,100), steer(10000,10,100);

	//speed(12345,1,0), steer(1234,1,0);

static unsigned speed_set;
static int track;	
	



void uppdate_pwm(void){
	int lt = left.speed(getLeft());
	int rt = right.speed(getRight());
	int sp = speed.control(5 - (lt + rt));
	int st = steer.control(set_error(lt,rt,error));
	lt = sp - st; rt = sp + st;
	if (lt < 0) lt = 0;
	if (rt < 0) rt = 0;
	if (lt > 44999) lt = 44999;
	if (rt > 44999) rt = 44999;
	pwmLeft(lt); pwmRight(rt);
}

//void uppdate_pwm(void){
//	int lt = left.speed(getLeft());
//	int rt = right.speed(getRight());
//	int sp = speed.control(3 - (lt + rt));
//	int st = steer.control(lt-rt);
//	lt = sp - st; rt = sp + st;
//	if (lt < 0) lt = 0;
//	if (rt < 0) rt = 0;
//	if (lt > 44999) lt = 44999;
//	if (rt > 44999) rt = 44999;
//	pwmLeft(lt); pwmRight(rt);
//}

//void set_speed(unsigned v){
//	speed_set=v;
//}

int set_error(int left, int right, int err){
	if(err==0) return (left-right);
	else return err;
}