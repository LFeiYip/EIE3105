
#include "stm32f10x.h"                  // Device header
#include "stdio.h"
volatile uint16_t ADC_values[3];
// PWM 
void TIM3_PWM_3channel_init(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef go;
	go.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	go.GPIO_Mode = GPIO_Mode_AF_PP;
	go.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&go);

	go.GPIO_Pin = GPIO_Pin_0;
	go.GPIO_Mode = GPIO_Mode_AF_PP;
	go.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&go);
	
//timer 3
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_TimeBaseInitTypeDef tim;
	tim.TIM_Prescaler = 72-1; 
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_Period = 2000-1; 
	tim.TIM_ClockDivision = TIM_CKD_DIV1; 
	tim.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&tim);
	TIM_Cmd(TIM3,ENABLE);
	
//pwm ch1
	TIM_OCInitTypeDef oc;
	oc.TIM_OCMode = TIM_OCMode_PWM1;
	oc.TIM_Pulse = 0;
	oc.TIM_OutputState = TIM_OutputState_Enable;
	oc.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM3,&oc);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

//pwm ch2
	oc.TIM_OCMode = TIM_OCMode_PWM1;
	oc.TIM_Pulse = 0;
	oc.TIM_OutputState = TIM_OutputState_Enable;
	oc.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC2Init(TIM3, &oc);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	// Enable Tim3 Ch3 PWM
	oc.TIM_OCMode = TIM_OCMode_PWM1;
	oc.TIM_Pulse = 0;
	oc.TIM_OutputState = TIM_OutputState_Enable;
	oc.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init(TIM3, &oc);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
}

//ADC 
void ADC1_3channel_init(){
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); //ADCCLK = PCLK2/6 = 72/6 = 12MHz
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	// Enable ADC1 clock 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	ADC_DeInit(ADC1);

	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent; 
	ADC_InitStruct.ADC_ScanConvMode = ENABLE; 
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE; 
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_NbrOfChannel = 3; 
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_4,3,ADC_SampleTime_239Cycles5);
	
  ADC_Init(ADC1, &ADC_InitStruct);
  ADC_Cmd(ADC1, ENABLE);
	ADC_DMACmd(ADC1, ENABLE);
	ADC_ResetCalibration(ADC1);
	
	while(ADC_GetResetCalibrationStatus(ADC1));
	
  ADC_StartCalibration(ADC1);
  while(ADC_GetCalibrationStatus(ADC1));
}


void DMA1_init(){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); // Enable DMA1 clock
	
	DMA_InitTypeDef DMA_InitStruct;
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStruct.DMA_BufferSize = 3;
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)ADC_values;
	DMA_Init(DMA1_Channel1,&DMA_InitStruct);
	DMA_ITConfig(DMA1_Channel1,DMA_IT_TC,ENABLE);
	DMA_Cmd(DMA1_Channel1,ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = DMA1_Channel1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}


volatile uint32_t status = 0;

int main(){
	
	ADC1_3channel_init();
	TIM3_PWM_3channel_init();
	DMA1_init();
	int x = 1200;
	// Start convertion (wll be endless as we are in continuous mode)
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while(1){
		while(!status);
		
		if(ADC_values[0] < x)
			TIM_SetCompare1(TIM3, 0);
		else
			TIM_SetCompare1(TIM3, 2000);
		
		if(ADC_values[1] < x)
			TIM_SetCompare2(TIM3, 0);
		else
			TIM_SetCompare2(TIM3, 2000);
		
		if(ADC_values[2] < 500)
			TIM_SetCompare3(TIM3, 0);
		else
			TIM_SetCompare3(TIM3, 2000);
		
		status = 0;
	}
}

void DMA1_Channel1_IRQHandler(){
	if(DMA_GetITStatus(DMA1_IT_TC1)){
		status = 1;
		DMA_ClearITPendingBit(DMA1_IT_GL1);
	}
}