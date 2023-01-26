char getPath(void);
void setLeft(bool);
void setRight(bool);
bool uart3_print(const char*);
void pwmLeft(unsigned int);
void pwmRight(unsigned int);

extern char c;
char sensor[8]={0};
int error=0;
int count=0;
int flag=0;

bool uart3_print(const char*);

void read_sensor(void){
	//sensor give 1 if read line
	//		positive o				o negetive
	//0			1			2			3			4			5			6			7
	//1			2			4			8			16		32		64		128
	c = getPath();
//	sensor[0] = c & 1? '1' : '0';
//	sensor[1] = c & 2? '1' : '0';
//	sensor[2] = c & 4? '1' : '0';
//	sensor[3] = c & 8? '1' : '0';
//	sensor[4] = c & 16? '1' : '0';
//	sensor[5] = c & 32? '1' : '0';
//	sensor[6] = c & 64? '1' : '0';
//	sensor[7] = c & 128? '1' : '0';
	//uart3_print(sensor);
	char d=c & 0x18;


//**********************line follow logic******************************	
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
			if(/*sensor[5]==1 | sensor[6]==1 | sensor[7]==1*/(c&32==1)|(c&64==1)|(c&128==1)){
				//need to turn left
				error=2;
			}else if(/*sensor[0]==1 | sensor[1]==1 | sensor[2]==1*/(c&1==1)|(c&2==1)|(c&4==1)){
				error=-2;
			}
		}

//***************************************************************************	
	


//************************choose loop logic************************
		if(/*sensor[0]=1*/d==0x01){
			count++;
	}
}