#include "stm32f10x.h"                  // Device header

int main(void) {
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//GPIO set up for PA5 (on board LED)
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
		
	//Timer 2 set up 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
 
	TIM_TimeBaseInitTypeDef timerInitStructure; 
	timerInitStructure.TIM_Prescaler = 18000-1;  //1/(72Mhz/18000)=0.25ms
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Down;
	timerInitStructure.TIM_Period = 4000-1;  //0.25ms*4000 = 1s
	timerInitStructure.TIM_ClockDivision = 0; //TIM_CKD_DIV1;
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &timerInitStructure);
	TIM_Cmd(TIM2, ENABLE);
	
	//Enable update event for Timer2
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	char state = 0;

	while(1) {
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
      			if(state == 0)  {
				GPIO_ResetBits(GPIOA, GPIO_Pin_5);
				state = 1;
			} else {
				GPIO_SetBits(GPIOA, GPIO_Pin_5);	
				state = 0;
			}
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);	
		}
	}
}	
