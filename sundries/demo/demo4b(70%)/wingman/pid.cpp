extern int error;

enum wheel_action { STOP, FORWARD, BACKWARD, LEFT, RIGHT };

class Speed {
public:
  Speed(void) { last = speed8 = 0; }
  unsigned speed(unsigned cnt) {     //cnt = new counter value
    unsigned u = cnt - last;         //change in 2.5 ms
    last = cnt;
    unsigned s, s8 = speed8;
    for (s = u; s8; s8 >>= 4) s += s8 & 15;
    speed8 <<= 4;                    //shift out old data
    speed8 |= u;                     //save new data
    return s;
  }
private:
  unsigned speed8, last;
} left, right;

class Pid {
public:
  Pid(unsigned p, unsigned i, unsigned d):p(p),i(i),d(d) { reset(); }
  int control(int error) {
    int delta = error - last;
    last = error;
    acc += error;
    if (acc > MAX) acc = MAX;
    if (acc < MIN) acc = MIN;
    return error * p + acc * i + delta *d;
  }
  void reset(void) { acc = last = 0; }
private:
  enum { MAX=2123456789, MIN=-2123456789 };
  unsigned p, i, d;
  int acc, last;
} speed(22345,100,1000), steer(20000,2,1000);

static unsigned speed_set;
static int track;						// 0: no track, -1: right, 1: left
static wheel_action action = STOP;

extern int mode;
static int getError(int left, int right, char c, int err) {
	if(mode==0){
		static int last;
		if (!track) return left - right;
		else switch (c & 0x18) {
			case 0x00: return last << 1;
			case 0x08: return (last = -1);
			case 0x10: return (last = 1);
			default: return track;
		}
	}
	else return err;
}

unsigned getLeft(void), getRight(void);
void pwmLeft(unsigned), pwmRight(unsigned);
void update_pwm(char c) {          //call it at the end of poll(unsigned)
	int	lt = left.speed(getLeft());	 //when counter values are updated
	int	rt = right.speed(getRight());
	if (speed_set < 100) {
		if (speed_set) {
			int sp = speed.control(speed_set - (lt + rt));
			int st = steer.control(getError(lt, rt, c, error));
			lt = sp - st; rt = sp + st;
			if (lt < 0) lt = 0;
			if (rt < 0) rt = 0;
			if (lt > 44999) lt = 44999;
			if (rt > 44999) rt = 44999;
		} else lt = rt = 0; 
  } else lt = rt = speed_set;
	pwmLeft(lt); pwmRight(rt);
}

unsigned get_count(void) { return getLeft() + getRight(); }

static unsigned last_count;

void setLeft(bool), setRight(bool);
void wheel(wheel_action a, unsigned s) {
  speed_set = s; track = 0;
  switch (action = a) {
  case FORWARD: setLeft(true); setRight(true); break;
  case BACKWARD: setLeft(false); setRight(false); break;
  case LEFT: setLeft(false); setRight(true); break;
  case RIGHT: setLeft(true); setRight(false); break;
  default: speed_set = 0;
  }
  speed.reset(); steer.reset();
  last_count = get_count();
}

void wheel_track(int i) {		//-1: right, 1: left
	if (action != FORWARD) wheel(FORWARD, 3);
	track = i;
}

void wheel_speed(unsigned s) { if (action != STOP) speed_set = s; }

bool check_count(unsigned c) {
  unsigned count = get_count() - last_count;
  return count >= c;
}

extern char c;
void classic_linetrack(){
	char d=c & 0x18;
	if(/*(sensor[3]==1)&(sensor[4]==1)*/ d==0x18){
		error=0;
	}
	else if(/*sensor[3]==0 & sensor[4]==1*/ d==0x10){
		//turn left
		error=1;
	}
	else if(/*sensor[3]==1 & sensor[4]==0*/ d==0x08){
		//turn right
		error=-1;
	}
	else if(/*sensor[3]==0 & sensor[4]==0*/d==0x00){
		if(/*sensor[5]==1 | sensor[6]==1 | sensor[7]==1*/(c&32)|(c&64)|(c&128)){
			//need to turn left
			error=2;
		}else if(/*sensor[0]==1 | sensor[1]==1 | sensor[2]==1*/(c&1)|(c&2)|(c&4)){
			error=-2;
		}
	}
}