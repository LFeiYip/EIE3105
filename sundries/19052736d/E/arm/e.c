#include "stm32f10x.h"                  // Device header
#include "stdbool.h"
#include "stdio.h"
#include "string.h"

bool level = false;
u32 t1 = 0;
char temp[30];
char b[] = " The pulse width: ";
void timer(){
	//Capture

	GPIO_InitTypeDef go1;
	go1.GPIO_Pin = GPIO_Pin_6;
	go1.GPIO_Mode = GPIO_Mode_AF_PP;
	go1.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&go1);
	
	//timer 4
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_TimeBaseInitTypeDef tim4;
	tim4.TIM_Prescaler = 72-1; 
	tim4.TIM_CounterMode = TIM_CounterMode_Up;
	tim4.TIM_Period = 2000-1; 
	tim4.TIM_ClockDivision = TIM_CKD_DIV1; 
	tim4.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &tim4);
	TIM_Cmd(TIM4,ENABLE);
	
//ic
	TIM_ICInitTypeDef ic;
	ic.TIM_Channel = TIM_Channel_1;
	ic.TIM_ICPrescaler = TIM_ICPSC_DIV1;	
	ic.TIM_ICPolarity = TIM_ICPolarity_Rising; 
	ic.TIM_ICSelection =  TIM_ICSelection_DirectTI;  
	ic.TIM_ICFilter = 0;
	TIM_ICInit(TIM4, &ic);
	
	//Enable Input Capture Interrupt
	
	NVIC_InitTypeDef nv;
	nv.NVIC_IRQChannelCmd = ENABLE;
	nv.NVIC_IRQChannel = TIM4_IRQn;
	nv.NVIC_IRQChannelPreemptionPriority = 2;
	nv.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nv);
	TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC1, ENABLE);// Allow updates to interrupt, allows the CC1IE to capture interrupt
	
//usart

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef go3;
	go3.GPIO_Pin = GPIO_Pin_2;
	go3.GPIO_Mode = GPIO_Mode_AF_PP;
	go3.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&go3);
	
	go3.GPIO_Pin = GPIO_Pin_3;
	go3.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&go3);
	
//usart2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	USART_InitTypeDef us;
	us.USART_BaudRate = 9600;
	us.USART_StopBits = USART_StopBits_1;
	us.USART_WordLength = USART_WordLength_8b;
	us.USART_Parity = USART_Parity_No;
	us.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  
	us.USART_Mode = USART_Mode_Rx |USART_Mode_Tx;
	USART_Init(USART2,&us);
	USART_Cmd(USART2, ENABLE);
}

void send(char *pucBuffer, unsigned int x){
	while(x--){
		USART_SendData(USART2,*pucBuffer++);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC) == RESET);
	}
}

// Input Capture Interrupt Handler

void TIM4_IRQHandler(){
	if(TIM_GetITStatus(TIM4,TIM_IT_CC1) != RESET){
		if(!level){
			level = true;
			TIM_SetCounter(TIM4,0);
			TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Falling); // change to detect 
		}
		else{
			t1 += TIM_GetCounter(TIM4);
			TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Rising);
			t1 = (int)(t1*0.05);
			send(b,sizeof(b));
			sprintf(temp, "%d\r\n", t1);
			send(temp,sizeof(temp));
			t1 = 0;
			level = false;
		}
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update|TIM_IT_CC1);
}

int main(){
	timer();
	
	while(1){
	}
}