#include "stm32f10x.h"                  // Device header
//Yip Lung Fei
//19052736d

//pa5 led1   pa6 led2    pa7 led3

static __IO uint32_t msTicks;

void DelayMs(uint32_t ms){
	msTicks=ms;
	while(msTicks);
}

void delay(int t){
	int i;
	for(i=0;i<t;i++){
	GPIOA->BSRR |=0x01;
	}
}

void SysTick_Handler(void){
	if(msTicks !=0){
		msTicks--;
	}
}

int main(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//enable APB2
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	SysTick_Config(SystemCoreClock / 1000);
	SystemCoreClockUpdate();
	
	while(1){
		GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET);
		GPIO_WriteBit(GPIOA, GPIO_Pin_6, Bit_SET);
		GPIO_WriteBit(GPIOA, GPIO_Pin_7, Bit_SET);
		DelayMs(1000);
		GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET);
		GPIO_WriteBit(GPIOA, GPIO_Pin_6, Bit_RESET);
		GPIO_WriteBit(GPIOA, GPIO_Pin_7, Bit_SET);
		DelayMs(1000);
		GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET);
		GPIO_WriteBit(GPIOA, GPIO_Pin_6, Bit_SET);
		GPIO_WriteBit(GPIOA, GPIO_Pin_7, Bit_RESET);
		DelayMs(2000);
		GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET);
		GPIO_WriteBit(GPIOA, GPIO_Pin_6, Bit_SET);
		GPIO_WriteBit(GPIOA, GPIO_Pin_7, Bit_SET);
		DelayMs(1000);
	}
}