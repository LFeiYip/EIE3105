char getPath(void);
void setLeft(bool);
void setRight(bool);
bool uart3_print(const char*);
void pwmLeft(unsigned int);
void pwmRight(unsigned int);
void classic_linetrack(void);

extern char c;
char sensor[8]={0};
int error=0;
int count=0;
int temp=0;
int inner_circle_count=0;
char last=0x00;

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
	int flag=0;
	classic_linetrack();


////**********************line follow logic******************************
//	if(inner_circle_count==0){
//		if(count<3){
//			classic_linetrack();
//			if(/*sensor[0]=1*/(c&1)){
//				temp=1;
//			}
//			if((temp==1) & !(c&1)){
//				count++;
//				temp=0;
//			}
//		}else{
//			if(flag==0) classic_linetrack();
//			//when count>2, the car still moving in the big circle, detect the small circle first
//			if((c&128)|(c&64)){
//				flag=1; //the LHS sensor have detect the small circle, move to left a liitle bit for the ease of checking the next state
//			}
//			
//			if(flag==1) error=1; //keep turn left until the LHS detect nothing
//			
//			//since the above step moving the car to left a little bit, the LHS sensor should sense nothing, in this case, flag=2
//			if((flag==1) & !(c&128)){
//				flag=2;
//				classic_linetrack();
//			}
//			
//			//flag =2 indicate that the next time the LHS sensor detect something, need to turn left to move into the small circle
//			if((flag==2)&((c&128)|(c&64))){
//				error=3;
//				
//				//already inside the inner circle, reset the variables to jump out the 'if' condition, just follow the line
//				if((c&1)&!(c&128)){
//					flag=0;
//					count=0;
//					inner_circle_count=1;
//				}
//			}
//		}
//	}else{
//		//if(flag==0) classic_linetrack();
//		if(c&1){
//			flag=1;
//			classic_linetrack();
//		}
//		if((flag==1)&!(c&1)){
//			flag=2;
//			classic_linetrack();
//		}
//		if((flag==2) & (c&4)) error=-1;
//		else classic_linetrack();
//			
//	}
}
		



//			//if count>=2, next state go to the small circle
//			if(count>=2){
//				//when count>2, the car still moving in the big circle, detect the small circle first
//				if((c&128)|(c&64)){
//					flag=1; //the LHS sensor have detect the small circle, move to left a liitle bit for the ease of checking the next state
//				}
//				if(flag==1) error=1; //keep turn left until the LHS detect nothing
//				
//				//since the above step moving the car to left a little bit, the LHS sensor should sense nothing, in this case, flag=2
//				if((flag==1) & !(c&128)){
//					flag=2;
//					error=0;
//				}
//				
//				//flag =2 indicate that the next time the LHS sensor detect something, need to turn left to move into the small circle
//				if((flag==2)&((c&128)|(c&64))){
//					error=3;
//					
//					//already inside the inner circle, reset the variables to jump out the 'if' condition, just follow the line
//					if((c&1)&!(c&128)){
//						flag=0;
//						count=0;
//						error=0;
//						inner_circle_count=1;
//					}
//				}
//			}

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
