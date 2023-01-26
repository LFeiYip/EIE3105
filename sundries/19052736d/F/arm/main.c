#include "stm32f10x.h"                  // Device header
#include "stdbool.h"
#include "stdio.h"
#include "string.h"

void timer(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef go2;
	go2.GPIO_Pin = GPIO_Pin_6;
	go2.GPIO_Mode = GPIO_Mode_AF_PP;
	go2.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&go2);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_TimeBaseInitTypeDef tim;
	tim.TIM_Prescaler = 72-1; 
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_Period = 2000-1; 
	tim.TIM_ClockDivision = TIM_CKD_DIV1; 
	tim.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&tim);
	TIM_Cmd(TIM3,ENABLE);

	
	TIM_OCInitTypeDef oc;
	oc.TIM_OCMode = TIM_OCMode_PWM1;
	oc.TIM_Pulse = 0;
	oc.TIM_OutputState = TIM_OutputState_Enable;
	oc.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM3,&oc);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef go3;
	go3.GPIO_Pin = GPIO_Pin_2;
	go3.GPIO_Mode = GPIO_Mode_AF_PP;
	go3.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&go3);
	
	go3.GPIO_Pin = GPIO_Pin_3;
	go3.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&go3);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	//usart 2
	USART_InitTypeDef us;
	us.USART_BaudRate = 9600;
	us.USART_StopBits = USART_StopBits_1;
	us.USART_WordLength = USART_WordLength_8b;
	us.USART_Parity = USART_Parity_No;
	us.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  
	us.USART_Mode = USART_Mode_Rx |USART_Mode_Tx;
	USART_Init(USART2,&us);
	USART_Cmd(USART2, ENABLE);

	// usart2 interrput
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	NVIC_InitTypeDef nv2;
	nv2.NVIC_IRQChannel = USART2_IRQn;
	nv2.NVIC_IRQChannelPreemptionPriority = 0;
	nv2.NVIC_IRQChannelSubPriority = 0;
	nv2.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nv2);
}

void send(char *pucBuffer, unsigned int x){
	while(x--){
		USART_SendData(USART2,*pucBuffer++);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC) == RESET);
	}
}

char temp[30];
int d0, d1, sum,width,count=0;
char i,j;
char a[] = " Input value: ";
int countNum = 0;
// USART Interrupt Handler
void USART2_IRQHandler(){
	if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET && count == 0){
		i = (char) USART_ReceiveData(USART2);
		count = 1;
	}
	if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET && count == 1){
		j = (char) USART_ReceiveData(USART2);
		count = 2;
	}
	if(count == 2){
		d0 = (int)(i-'0');
		d1 = (int)(j-'0');
		width = d0*10 + d1;
		sum = (int)(width*0.01*2000);
		TIM3-> CCR1 = sum;
		send(a,sizeof(a));
		sprintf(temp, "%d\r\n", width);
		send(temp,sizeof(temp));
		count = 0;
	}
}

int main(){
	timer();
	while(1){
	}
}