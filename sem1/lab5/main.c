//Yip Lung Fei 19052736d
#include "stm32f10x.h"                  // Device header






////Section A
//int main(){
//	RCC->APB2ENR |=RCC_APB2Periph_GPIOA;
//	GPIOA->CRL &=~0x00F00000;
//	GPIOA->CRL |= 0<<22 | 2<<20;
//	GPIOA-> BSRR |=0x20;
//	while(1);
//}

















////Section B
//void delay(int t){
//	int i;
//	for(i=0;i<t;i++){
//	GPIOA->BSRR |=0x01;
//	}
//}

// int main(void){
//	 
//	 RCC->APB2ENR|=RCC_APB2Periph_GPIOA;
//	 GPIOA->CRL&=~0x00F00000;
//	 GPIOA->CRL |=0<<22 | 2 <<20;
//	 while(1){
//		 /*GPIOA->BSRR |=0x20;
//		 delay(3000000);
//		 GPIOA->BRR |=0x20;
//		 delay(3000000);*/
//		 GPIOA->ODR =0x20;
//		 delay(3000000);
//		 GPIOA->ODR =0;
//		 delay(3000000);
//		
//	}
// }
















////Section C
//static __IO uint32_t msTicks;

//void DelayMs(uint32_t ms){
//	msTicks=ms;
//	while(msTicks);
//}

//void delay(int t){
//	int i;
//	for(i=0;i<t;i++){
//	GPIOA->BSRR |=0x01;
//	}
//}

//void SysTick_Handler(void){
//	if(msTicks !=0){
//		msTicks--;
//	}
//}

//int main(void){
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//enable APB2
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_5;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
//	SysTick_Config(SystemCoreClock / 1000);
//	SystemCoreClockUpdate();
//	
//	while(1){
//		GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET);
//		DelayMs(1000);
//		//delay(300000);
//		GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET);
//		DelayMs(1000);
//		//delay(300000);
//	}
//}



















////Section D
//int state=0;

//int main(void){
//	GPIO_InitTypeDef GPIO_InitStructure;
//	EXTI_InitTypeDef EXTI_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStruct;
//	
//	//GPIO clock for I/O
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); //enable on board button
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //enable on board led
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); // enable alternative function I/O
//	
//	//Config I/O for on board LED PA5
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
//	
//	//config I/O for on board button PC13
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU; //input pull-up
//	GPIO_Init(GPIOC,&GPIO_InitStructure);
//	
//	//EXT1 config, GPIOC, Pin13
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13);
//	EXTI_InitStructure.EXTI_Line=EXTI_Line13;
//	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising_Falling;
//	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
//	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
//	EXTI_Init(&EXTI_InitStructure);
//	
//	//enable interrupt
//	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_InitStruct.NVIC_IRQChannel=EXTI15_10_IRQn;
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x02; //why 2
//	NVIC_Init(&NVIC_InitStruct);
//	
//	while(1){
//		if(state==1){
//			GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET);
//		}else if(state==2){
//			GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET);
//			state=0;
//		}
//	}
//}

//void EXTI15_10_IRQHandler(void){
//	if(EXTI_GetITStatus(EXTI_Line13)==SET){
//		state++;
//		EXTI_ClearITPendingBit(EXTI_Line13);
//	}

//}


















////Section E
//int stage=0;

//int main(void){
//	GPIO_InitTypeDef GPIO_InitStructure;
//	EXTI_InitTypeDef EXTI_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStruct;
//	
//	//GPIO clock for I/O
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); //enable on board button
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //enable on board led
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); // enable alternative function I/O
//	
//	//Config I/O for on board LED PA5
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
//	
//	//config I/O for on board button PC13
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU; //input pull-up
//	GPIO_Init(GPIOC,&GPIO_InitStructure);
//	
//	//EXT1 config, GPIOC, Pin13
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13);
//	EXTI_InitStructure.EXTI_Line=EXTI_Line13;
//	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
//	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
//	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
//	EXTI_Init(&EXTI_InitStructure);
//	
//	//enable interrupt
//	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_InitStruct.NVIC_IRQChannel=EXTI15_10_IRQn;
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x02; //why 2
//	NVIC_Init(&NVIC_InitStruct);
//	
//	while(1){
//		if(stage==0){
//			GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET);
//		}else{
//			GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET);
//		}
//	}
//}

//void EXTI15_10_IRQHandler(void){
//	if(EXTI_GetITStatus(EXTI_Line13)!=RESET){
//		stage++;
//		if(stage!=1){
//			stage=0;
//		}
//		EXTI_ClearITPendingBit(EXTI_Line13);
//	}
//}




















////Section F

//	/*
//	lightset3	->	PA0-red		PA1-yellow		PA4-green
//	lightset2 ->	PB0-red	 	PC1-yellow		PC0-green
//	lightset1 ->	PA8-red		PB10-green
//	*/


//int t=0;
//int count=10;

//void TIM2_IRQHandler(void){
//	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET){
//		t++;
//		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//	}
//}

//static __IO uint32_t msTicks;

//void DelayMs(uint32_t ms){
//	msTicks=ms;
//	while(msTicks);
//}

//void SysTick_Handler(void){
//	if(msTicks !=0){
//		msTicks--;
//	}
//}

//void traffic_light(){
//	//state1
//	while(t<5){
//		//time duration=5s
//		GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_SET);
//		GPIO_WriteBit(GPIOC, GPIO_Pin_0, Bit_SET);
//		GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
//		//
//		GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_RESET);
//		GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_RESET);
//	}
//	
//	//state2
//	if(t==5){
//		//from count=5 to count=6, time duration=1s
//		GPIO_WriteBit(GPIOC, GPIO_Pin_0, Bit_RESET);
//		GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_SET);
//	}
//	
//	//state3
//	if(t==6){
//		//from count= to count=7, time duration=1s
//		GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_RESET);
//		GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_SET);
//	}
//	
//	//state4
//	if(t==7){
//		//from count=7 to count=8, time duration=1s
//		GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET);
//	}
//	
//	//state5
//	while((t==8)&(t<13)){
//		//from count=8 to count=13, time duration=5s
//		GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);
//		GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
//		GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);
//		GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_RESET);
//		GPIO_WriteBit(GPIOB, GPIO_Pin_10, Bit_SET);
//	}
//	
//	//state6
//	while(t==13){
//		//from count=13 to count=14, time duration=1s
//		TIM_Cmd(TIM3,ENABLE);
//		GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);
//		GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET);
//		GPIO_WriteBit(GPIOB, GPIO_Pin_10, Bit_RESET);
//		DelayMs(100);
//		GPIO_WriteBit(GPIOB, GPIO_Pin_10, Bit_SET);
//		DelayMs(100);
//		GPIO_WriteBit(GPIOB, GPIO_Pin_10, Bit_RESET);
//		DelayMs(100);
//		GPIO_WriteBit(GPIOB, GPIO_Pin_10, Bit_SET);
//		DelayMs(100);
//		GPIO_WriteBit(GPIOB, GPIO_Pin_10, Bit_RESET);
//		DelayMs(100);
//		GPIO_WriteBit(GPIOB, GPIO_Pin_10, Bit_SET);
//		DelayMs(100);
//		GPIO_WriteBit(GPIOB, GPIO_Pin_10, Bit_RESET);
//		DelayMs(100);
//		GPIO_WriteBit(GPIOB, GPIO_Pin_10, Bit_SET);
//		DelayMs(100);
//		GPIO_WriteBit(GPIOB, GPIO_Pin_10, Bit_RESET);
//		DelayMs(100);
//		GPIO_WriteBit(GPIOB, GPIO_Pin_10, Bit_SET);
//		DelayMs(100);
//	}
//	
//	
//	//state7
//	if(t == 14){
//		//from count=14 to count=15, time duration=1s
//		GPIO_WriteBit(GPIOB, GPIO_Pin_10, Bit_RESET);
//		GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_SET);
//		GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);
//		GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
//	}
//	
//	//state8
//	while((t==15)&(t<16)){
//		//from count=15 to count=16, time duration=1s
//		GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_SET);
//	}
//	
//	if(t==16){
//		//reset count to 0
//		t=0;
//	}
//}


//int main(){
//	GPIO_InitTypeDef GPIO_InitStructure;
//	TIM_TimeBaseInitTypeDef timerInitStruct;
//	
//	//GPIO clock for I/O
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); // enable alternative function I/O
//	
//	//Config I/O for portA
//	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_8;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
//	
//	//Config I/O for portB
//	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_0 | GPIO_Pin_10;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOB,&GPIO_InitStructure);
//	
//	//Config I/O for portC
//	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_0 | GPIO_Pin_1;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOC,&GPIO_InitStructure);
//	
//	//Timer 2 setup
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
//	timerInitStruct.TIM_Prescaler = 18000-1;//0.25ms
//	timerInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
//	timerInitStruct.TIM_Period=4000-1;//4000*0.25ms=1s
//	timerInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
//	timerInitStruct.TIM_RepetitionCounter = 0;
//	TIM_TimeBaseInit(TIM2,&timerInitStruct);
//	TIM_Cmd(TIM2,ENABLE);

//	//enable update event for timer2
//	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
//	NVIC_EnableIRQ(TIM2_IRQn);
//	
//	//systick delay
//	SysTick_Config(SystemCoreClock / 1000);
//	SystemCoreClockUpdate();
//	
//	while(1){
//		traffic_light();
//	}
//}

















////Section G
///*	PB8 connect to led, PB9 is external interrupt
//*/
//int state=0;

//void EXTI9_5_IRQHandler(void){
//	if(EXTI_GetITStatus(EXTI_Line9)!=RESET){
//		state++;
//		EXTI_ClearITPendingBit(EXTI_Line9);
//	}
//	if(state==2){
//		state=0;
//	}
//}
//                                                                                                                                                                                                                                                                                                                    
//int main(){
//	GPIO_InitTypeDef GPIO_InitStructure;
//	EXTI_InitTypeDef EXTI_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStruct;
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
//	
//	//config I/O for led PB8
//	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_8;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOB,&GPIO_InitStructure);
//	
//	//config I/O for switch
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
//	//GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU; //input pull-up
//	GPIO_Init(GPIOB,&GPIO_InitStructure);
//	
//	//EXTI config, GPIOB, Pin9
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource9);
//	EXTI_InitStructure.EXTI_Line=EXTI_Line9;
//	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
//	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
//	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
//	EXTI_Init(&EXTI_InitStructure);
//	
//	//enable interrupt
//	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_InitStruct.NVIC_IRQChannel=EXTI9_5_IRQn;
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x02;
//	NVIC_Init(&NVIC_InitStruct);
//	
//	while(1){
//		if(state==1){
//			GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_SET);
//		}else{
//			GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_RESET);
//		}
//	}
//}















////Section H
///* config same as section F */
//int t=0;
//int count=10;
//int state=0;

//void TIM2_IRQHandler(void){
//	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET){
//		t++;
//		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//	}
//}

//static __IO uint32_t msTicks;

//void DelayMs(uint32_t ms){
//	msTicks=ms;
//	while(msTicks);
//}

//void SysTick_Handler(void){
//	if(msTicks !=0){
//		msTicks--;
//	}
//}

//void traffic_light(){
//	//state1
//	while(t<5){
//		//time duration=5s
//		if(state==1){
//			GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_SET);
//			GPIO_WriteBit(GPIOC, GPIO_Pin_0, Bit_SET);
//			GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
//		//
//			GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_RESET);
//			GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_RESET);
//		}else{
//			GPIO_WriteBit(GPIOA, GPIO_Pin_All, Bit_RESET);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_All, Bit_RESET);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_All, Bit_RESET);
//		}
//	}
//	
//	//state2
//	if(t==5){
//		//from count=5 to count=6, time duration=1s
//		if(state==1){
//			GPIO_WriteBit(GPIOC, GPIO_Pin_0, Bit_RESET);
//			GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_SET);
//		}else{
//			GPIO_WriteBit(GPIOA, GPIO_Pin_All, Bit_RESET);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_All, Bit_RESET);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_All, Bit_RESET);
//		}
//	}
//	
//	//state3
//	if(t==6){
//		//from count= to count=7, time duration=1s
//		if(state==1){
//			GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_RESET);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_SET);
//		}else{
//			GPIO_WriteBit(GPIOA, GPIO_Pin_All, Bit_RESET);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_All, Bit_RESET);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_All, Bit_RESET);
//		}
//	}
//	
//	//state4
//	if(t==7){
//		//from count=7 to count=8, time duration=1s
//		if(state==1){
//			GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET);
//		}else{
//			GPIO_WriteBit(GPIOA, GPIO_Pin_All, Bit_RESET);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_All, Bit_RESET);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_All, Bit_RESET);
//		}
//	}
//	
//	//state5
//	while((t==8)&(t<13)){
//		//from count=8 to count=13, time duration=5s
//		if(state==1){
//			GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);
//			GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
//			GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);
//			GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_RESET);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_10, Bit_SET);
//		}else{
//			GPIO_WriteBit(GPIOA, GPIO_Pin_All, Bit_RESET);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_All, Bit_RESET);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_All, Bit_RESET);
//		}
//	}
//	
//	//state6
//	while(t==13){
//		//from count=13 to count=14, time duration=1s
//		if(state==1){
//			//TIM_Cmd(TIM3,ENABLE);
//			GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);
//			GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_10, Bit_RESET);
//			DelayMs(100);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_10, Bit_SET);
//			DelayMs(100);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_10, Bit_RESET);
//			DelayMs(100);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_10, Bit_SET);
//			DelayMs(100);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_10, Bit_RESET);
//			DelayMs(100);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_10, Bit_SET);
//			DelayMs(100);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_10, Bit_RESET);
//			DelayMs(100);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_10, Bit_SET);
//			DelayMs(100);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_10, Bit_RESET);
//			DelayMs(100);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_10, Bit_SET);
//			DelayMs(100);
//	}else{
//			GPIO_WriteBit(GPIOA, GPIO_Pin_All, Bit_RESET);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_All, Bit_RESET);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_All, Bit_RESET);
//		}
//	}
//	
//	
//	//state7
//	if(t == 14){
//		//from count=14 to count=15, time duration=1s
//		if(state==1){
//			GPIO_WriteBit(GPIOB, GPIO_Pin_10, Bit_RESET);
//			GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_SET);
//			GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);
//			GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
//		}else{
//			GPIO_WriteBit(GPIOA, GPIO_Pin_All, Bit_RESET);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_All, Bit_RESET);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_All, Bit_RESET);
//		}
//	}
//	
//	//state8
//	while((t==15)&(t<16)){
//		//from count=15 to count=16, time duration=1s
//		if(state==1){
//		GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_SET);
//		}else{
//			GPIO_WriteBit(GPIOA, GPIO_Pin_All, Bit_RESET);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_All, Bit_RESET);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_All, Bit_RESET);
//		}
//	}
//	
//	if(t==16){
//		//reset count to 0
//		t=0;
//	}
//}

//void EXTI9_5_IRQHandler(void){
//	if(EXTI_GetITStatus(EXTI_Line9)!=RESET){
//		state++;
//		EXTI_ClearITPendingBit(EXTI_Line9);
//	}
//	if(state==2){
//		state=0;
//	}
//}


//int main(){
//	GPIO_InitTypeDef GPIO_InitStructure;
//	TIM_TimeBaseInitTypeDef timerInitStruct;
//	NVIC_InitTypeDef NVIC_InitStruct;
//	EXTI_InitTypeDef EXTI_InitStructure;
//	
//	//GPIO clock for I/O
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); // enable alternative function I/O
//	
//	//Config I/O for portA
//	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_8;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
//	
//	//Config I/O for portB
//	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_0 | GPIO_Pin_10;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOB,&GPIO_InitStructure);
//	
//	//Config I/O for portC
//	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_0 | GPIO_Pin_1;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOC,&GPIO_InitStructure);
//	
//	//Timer 2 setup
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
//	timerInitStruct.TIM_Prescaler = 18000-1;//0.25ms
//	timerInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
//	timerInitStruct.TIM_Period=4000-1;//4000*0.25ms=1s
//	timerInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
//	timerInitStruct.TIM_RepetitionCounter = 0;
//	TIM_TimeBaseInit(TIM2,&timerInitStruct);
//	TIM_Cmd(TIM2,ENABLE);

//	//enable update event for timer2
//	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
//	NVIC_EnableIRQ(TIM2_IRQn);
//	
//	//systick delay
//	SysTick_Config(SystemCoreClock / 1000);
//	SystemCoreClockUpdate();
//	
//	//config I/O for switch
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
//	//GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
//	GPIO_Init(GPIOB,&GPIO_InitStructure);
//	
//	//EXTI config, GPIOB, Pin9
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource9);
//	EXTI_InitStructure.EXTI_Line=EXTI_Line9;
//	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
//	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
//	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
//	EXTI_Init(&EXTI_InitStructure);
//	
//	//enable interrupt
//	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_InitStruct.NVIC_IRQChannel=EXTI9_5_IRQn;
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x02;
//	NVIC_Init(&NVIC_InitStruct);
//	
//	while(1){
//		traffic_light();
//	}
//}


















////Section I
//char a='a';
//unsigned char ch;
//uint8_t msg=0;
//int state=0;
//int count=0;
//char temp;

//void USART2_IRQHandler(){
///*
//	state 0:keep sending 'a'
//	any input recieved->state1
//	state 1:repeat the input 10 times
//	after sending->state 2
//	state 2:determine whether the input equal to the previous one
//	if yes->state 0. if no, wait until equal.
//*/
//	if(USART_GetITStatus(USART2,USART_IT_TC)!=RESET){
//		if(state==0){
//			USART_SendData(USART2,a);
//		}else if(state==1){
//			USART_SendData(USART2,ch);
//			count++;
//			temp=ch;
//		}
//		if(count==10){
//			state=2;
//			count=0;
//		}
//	}
//	//USART_ClearITPendingBit(USART2,USART_IT_TC);
//	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET){
//		ch=(unsigned char)USART_ReceiveData(USART2);
//		if(state==0){
//			state=1;
//		}else if(state==2){
//			if(ch==temp){
//				state=0;
//			}
//		}
//	}
//}

//int main(){
//	
//	//USART2 TX RX
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
//	
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_3;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
//	
//	USART_InitTypeDef USART_InitStructure;
//	USART_InitStructure.USART_BaudRate=9600;
//	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;
//	USART_InitStructure.USART_Parity=USART_Parity_No;
//	USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None;
//	USART_InitStructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;
//	USART_Init(USART2,&USART_InitStructure);
//	USART_Cmd(USART2,ENABLE);
//	
//	NVIC_InitTypeDef NVIC_InitStruct;
//	//Enable the USART2 TX Interrupt
//	USART_ITConfig(USART2, USART_IT_TC, ENABLE);
//	NVIC_InitStruct.NVIC_IRQChannel=USART2_IRQn;
//	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
//	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
//	NVIC_Init(&NVIC_InitStruct);
//	
//	//Enable the USART2 RX Interrupt
//	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
//	NVIC_InitStruct.NVIC_IRQChannel=USART2_IRQn;
//	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
//	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
//	NVIC_Init(&NVIC_InitStruct);	
//	
//	while(1){

//	}
//}