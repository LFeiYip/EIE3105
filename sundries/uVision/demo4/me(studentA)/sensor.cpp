char getPath(void);
void setLeft(bool);
void setRight(bool);
bool uart3_print(const char*);
void pwmLeft(unsigned int);
void pwmRight(unsigned int);
void classic_linetrack(void);
void follow_outer_edge(void);
void follow_inner_edge(void);
void determine_state(void);
int getDistance(void);
bool check_count(unsigned c);

extern char c;
int error=0;
int count=0;
int flag=0;
int state=0;

void read_sensor(void){
	c = getPath();
	char d=c & 0x18;
	determine_state();
}




void determine_state(){
	if(state==0){
//		if(((c&0xFF)==0x1F)|((c&0xFF)==0x3F)|((c&0xFF)==0xEE)|((c&0xFF)==0x0F))state=1;
//	}
//	if(flag==1){
//		if(	((c&0xFF)==0x1E) | ((c&0xFF)==0x0E)| ((c&0xFF)==0x1C)| ((c&0xFF)==0x38)| ((c&0xFF)==0x3C)){
//			state=1;
//			flag=0;
//		}	
//	}
		if(c&128)flag=1;
		if(flag==1){
			if(!(c&128)){
				flag=2;
			}
		}
//		if(flag==2){
//			if(((c&0xFF)==0x3E) | ((c&0xFF)==0x1F)){
//				state=1;
//				flag=0;
//			}
//		}
		if(flag==2){
			if(((c&0xFF)==0x3E) | ((c&0xFF)==0x1F))flag=3;
		}
		if(flag==3){
			if(((c&0xFF)==0x0E) | ((c&0xFF)==0x0F)){
				state=1;
				flag=0;
			}
		}
			
	}		
	
	if(state==1){
		if((c&0xFF)==0x00)flag=1;
		if(flag==1){
			if(!((c&0xFF)==0x00)){
				state=2;
				flag=0;
			}
		}
		
//		//dont know why without the following still work
//		if(flag==2){
//			if((c&0xFF)==0x00)flag=3;
//		}
//		if(flag==3){
//			if(!((c&0xFF)==0x00))state=2;
//		}
	}
	
	if(state==2){
		if((c&0xFF)==0x00)flag=1;
		if(flag==1){
			//if(!((c&0xFF)==0x00)){
			if(c&128){
				state=3;
				flag=0;
			}
		}
	}
	
	if(state==3){
		if((c&0xFF)==0x01)state=4;
	}
	
	if(state==4){
		if((getDistance()<60) & (getDistance()!=0))state=5;
	}
	
	if(state==5){
		if((getDistance()>60) | (getDistance()==0))state=20;
	}
	
	if(state==20){
		if(c&128)state=6;
	}
	
	if(state==6){
		if((c&0x18)==0)flag=1;
		if(flag==1){
			if((c&0x18)==0x18){
				state=7;
				flag=0;
			}
		}
	}
	
	if(state==7){
		if((getDistance()<55) & (getDistance()!=0))state=8;
	}
	
	if(state==8){
		if((c&0x18)==0)flag=1;
		if(flag==1){
			if((c&0x18)==0x18){
				state=9;
				flag=0;
			}
		}
	}
	
	if(state==9){
//		if((c&0xFF)==0xFC)flag=1;
//		if(flag==1){
//			if((c&0xFF)!=0xFC)count++;
//		}
//		if(count==2)state=10;
		if(check_count(800))state=10;
	}
	
	
//	if(state==3){
//		if(getDistance()>60)state=4;
//	}
//	
//	if(state==4){
//		if(c&128)state=5;
//	}
		
		
		
		
//		if(state==1){
//		
//			if(flag==0){
//				if(((c&0xFF)==0x7E)|((c&0xFF)==0xEE)|((c&0xFF)==0x8C)|((c&0xFF)==0xCE)|((c&0xFF)==0x9C)|((c&0xFF)==0x8E))flag=1;
//				}
//			
//				//flag=1:left sensor sense something
//			if(flag==1){
//				if(	((c&0xFF)==0x1C) | ((c&0xFF)==0x0E)){
//					flag=2;
//				}
//			}
//			//flag=2:at the middle
//			if(flag==2){
//				if(	(	(c&0xFF)==0x3b	)	|	(	(c&0xFF)==0x7E)	|	(	(c&0xFF)==0x1F)|	(	(c&0xFF)==0x3F)){
//					flag=3;
//				}
//			}
//			
//			//flag=3:fork road
//			if(flag==3){
//				
//				//after go in, change state
//				if( ((c&0xFF)==0x3b) | ((c&0xFF)==0x78)| ((c&0xFF)==0x3c)| ((c&0xFF)==0x1c) ){
//					flag=4;
//				}
//			}
//			if(flag==4){
//				if(((c&0xFF)==0x3f) | ((c&0xFF)==0x7f)){
//					state=2;
//					flag=0;
//				}
//			}
//		
//		}
//		
//		if(state==2){
//			if(((c&0xFF)==0x3b) | ((c&0xFF)==0xF0) | ((c&0xFF)==0xFC)){
//				flag=1;
//			}
//			
//			if(flag==1){
//				if(((c&0xFF)==0x3C) | ((c&0xFF)==0x38) ){
//					flag=2;
//				}
//			}
//			
//			if(flag==2){
//				if(((c&0xFF)==0xF8)){
//					flag=3;
//				}
//			}
//			
//			if(flag==3){
//				if(((c&0xFF)==0x38) | ((c&0xFF)==0x3C) ){
//					flag=4;
//				}
//			}
//			if(flag==4){
//				if(((c&0xFF)==0xFE) | ((c&0xFF)==0xFC) | ((c&0xFF)==0xF8) |((c&0xFF)==0x7c)){
//					state=3;
//					flag=0;
//				}
//			}
//		}
//		
//		if(state==3){
//			if(((c&0xFF)==0x3d) | ((c&0xFF)==0x1d) |((c&0xFF)==0x7f)){
//				state=4;
//			}
//		}
//		
//		if(state==4){
//			if(/*sensor[0]=1*/(c&1)){
//				temp=1;
//			}
//			if((temp==1) & !(c&1)){
//				count++;
//				temp=0;
//			}
//			if((count==2)){
//				state=5;
//				count=0;
//			}
//		}
//			
//			
}


		