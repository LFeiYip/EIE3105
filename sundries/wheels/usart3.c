#include "stm32f10x.h"
char a='a';
unsigned char ch;
uint8_t msg=0;
int state=0;
int count=0;
char temp;

void USART3_IRQHandler(){

	if(USART_GetITStatus(USART3,USART_IT_TC)!=RESET){
		if(state==0){
			USART_SendData(USART3,a);
		}else if(state==1){
			USART_SendData(USART3,ch);
			count++;
			temp=ch;
		}
		if(count==10){
			state=2;
			count=0;
		}
	}
	//USART_ClearITPendingBit(USART2,USART_IT_TC);
	if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET){
		ch=(unsigned char)USART_ReceiveData(USART3);
		if(state==0){
			state=1;
		}else if(state==2){
			if(ch==temp){
				state=0;
				
			}
		}
	}
}

int main(){
	
	//USART3 TX RX
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	//TX
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//RX
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate=115200;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3,&USART_InitStructure);
	USART_Cmd(USART3,ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	//Enable the USART2 TX Interrupt
	USART_ITConfig(USART3, USART_IT_TC, ENABLE);
	NVIC_InitStruct.NVIC_IRQChannel=USART3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStruct);
	
	//Enable the USART2 RX Interrupt
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	NVIC_InitStruct.NVIC_IRQChannel=USART3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStruct);	
	
	while(1){

	}
}