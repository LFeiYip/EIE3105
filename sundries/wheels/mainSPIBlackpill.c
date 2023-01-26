#include "stm32f10x.h"                  // Device header
#include "string.h"
#include "stdbool.h"
#include "stdio.h"

//IM1 CH1 **A8
#define TIM1_CH1_PWM_RCC_GPIO RCC_APB2Periph_GPIOA
#define TIM1_CH1_PWM_PIN      GPIO_Pin_8
#define TIM1_CH1_PWM_GPIO     GPIOA

//TIM1 CH1N **B13
#define TIM1_CH1N_PWM_RCC_GPIO RCC_APB2Periph_GPIOB
#define TIM1_CH1N_PWM_PIN      GPIO_Pin_13
#define TIM1_CH1N_PWM_GPIO     GPIOB

//TIM1 CH2 **A9
#define TIM1_CH2_PWM_RCC_GPIO RCC_APB2Periph_GPIOA
#define TIM1_CH2_PWM_PIN      GPIO_Pin_9
#define TIM1_CH2_PWM_GPIO     GPIOA

//TIM1 CH2N **B14
#define TIM1_CH2N_PWM_RCC_GPIO RCC_APB2Periph_GPIOB
#define TIM1_CH2N_PWM_PIN      GPIO_Pin_14
#define TIM1_CH2N_PWM_GPIO     GPIOB
void init(void)
{
	RCC_APB2PeriphClockCmd(TIM1_CH1_PWM_RCC_GPIO|TIM1_CH1N_PWM_RCC_GPIO|TIM1_CH2_PWM_RCC_GPIO|TIM1_CH2N_PWM_RCC_GPIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	//conifg GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
  
  /* channel 2 & channel 2N must be initialized at the same time */
	
	//ch1
	GPIO_InitStructure.GPIO_Pin = TIM1_CH1_PWM_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(TIM1_CH1_PWM_GPIO,&GPIO_InitStructure);
	
  
	//ch2
	GPIO_InitStructure.GPIO_Pin = TIM1_CH2_PWM_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(TIM1_CH2_PWM_GPIO,&GPIO_InitStructure);
	
	//ch1n
	GPIO_InitStructure.GPIO_Pin = TIM1_CH1N_PWM_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(TIM1_CH1N_PWM_GPIO,&GPIO_InitStructure);
	
	//ch2n
	GPIO_InitStructure.GPIO_Pin = TIM1_CH2N_PWM_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(TIM1_CH2N_PWM_GPIO,&GPIO_InitStructure);
	
	
	//set TIM1 1000Hz 
  	//range of PWM: 0 to 1000
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	
	TIM_TimeBaseInitTypeDef timerInitStructure;
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Prescaler = 72-1; // 0.001ms
	timerInitStructure.TIM_Period = 1000-1; //1ms
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &timerInitStructure);
	TIM_Cmd(TIM1, ENABLE);
  
	TIM_ARRPreloadConfig(TIM1, ENABLE);
}

void leftforward(unsigned short pwm)
{
	TIM_OCInitTypeDef leftforward;
	leftforward.TIM_OCMode = TIM_OCMode_PWM1;
	leftforward.TIM_Pulse = pwm-1;
	leftforward.TIM_OutputState = TIM_OutputState_Enable;
	leftforward.TIM_OutputNState = TIM_OutputNState_Disable;
	leftforward.TIM_OCPolarity = TIM_OCPolarity_High;
  
	TIM_OC1Init(TIM1, &leftforward);
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
  
}

// a function to enable the right wheel moving forward 
void rightforward(unsigned short pwm)
{
	TIM_OCInitTypeDef rightforward;
	rightforward.TIM_OCMode = TIM_OCMode_PWM1;
	rightforward.TIM_Pulse = pwm-1;
	rightforward.TIM_OutputNState = TIM_OutputNState_Enable;
	rightforward.TIM_OutputState = TIM_OutputState_Disable;
	rightforward.TIM_OCNPolarity = TIM_OCNPolarity_High;
	
	TIM_OC2Init(TIM1, &rightforward);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

// a function to enable the left wheel moving backward 
void leftbackward(unsigned short pwm)
{
	TIM_OCInitTypeDef leftbackward;
	leftbackward.TIM_OCMode = TIM_OCMode_PWM1;
	leftbackward.TIM_Pulse = pwm-1;
	leftbackward.TIM_OutputNState = TIM_OutputNState_Enable;
	leftbackward.TIM_OutputState = TIM_OutputState_Disable;
	leftbackward.TIM_OCNPolarity = TIM_OCNPolarity_High;
	
	TIM_OC1Init(TIM1, &leftbackward);
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
  	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

// a function to enable the right wheel moving backward 
void rightbackward(unsigned short pwm)
{
	TIM_OCInitTypeDef rightbackward;
	rightbackward.TIM_OCMode = TIM_OCMode_PWM1;
	rightbackward.TIM_Pulse = pwm-1;
	rightbackward.TIM_OutputState = TIM_OutputState_Enable;
	rightbackward.TIM_OutputNState = TIM_OutputNState_Disable;
	rightbackward.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC2Init(TIM1, &rightbackward);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
  	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}
// UART setup
void UART3_init(void){
	//USART2 TX RX
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	
	//Tx pin
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
		
	//Rx pin
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
	//USART2 ST-LINK USB
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 115200;
  	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
 	USART_InitStructure.USART_StopBits = USART_StopBits_1;
  	USART_InitStructure.USART_Parity = USART_Parity_No;
  	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_Init(USART3, &USART_InitStructure);
	USART_Cmd(USART3, ENABLE);
}

void USARTSend(char *pucBuffer, unsigned long ulCount)
{
	//
	// Loop while there are more characters to send.
	//
	while(ulCount--)
	{
		USART_SendData(USART3, *pucBuffer++);
		/* Loop until the end of transmission */
		while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET){}
	}
}

char buffer[50] = {'\0'};
bool pulseHigh = false;
u32 pulseWidth = 0;

int count;
char state_int = 0;

int mask=24;

// get the readings once
void readFloor() 
{
	// Set PA7 to 1
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
	// Initialize the data transmission from the master to the slave
	SPI_I2S_SendData(SPI1, 0);
	count = 4;
	// Enable the interrupt to receive data by using the ISR handler
	NVIC_EnableIRQ(SPI1_IRQn);
}

// this program gets the readings once in every 0.1s
// the infra-red LEDs are turned on when PA7 is set to 1
// it waits for sending four packets from the MCU to the shift register (it takes 10 ms)
// and then turn off the LEDs and get the readings from the photoresistors
// the readings can be obtained from USART2

int direction=0;

int main()
{
	//SPI init
	// Setup PA5, PA6, PA7
	// PA5 = SPI1_SCK, PA7 = SPI1_MOSI, PA6 = SPI1_MISO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2ENR_SPI1EN, ENABLE);
	// SPI initialization
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	// 36 MHz / 256 = 140.625 kHz
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_Init(SPI1, &SPI_InitStructure);
	// Enable the receive interrupt
	SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);
	// Enable SPI1
	SPI_Cmd(SPI1, ENABLE);
	
	
	//TIM2 init, read once each 0.1s
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
 
	TIM_TimeBaseInitTypeDef timerInitStructure; 
  	timerInitStructure.TIM_Prescaler = 18000;  //1/(72Mhz/18000)=0.25ms
  	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  	timerInitStructure.TIM_Period = 400;  //400->0.1s
  	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  	timerInitStructure.TIM_RepetitionCounter = 0;
  	TIM_TimeBaseInit(TIM2, &timerInitStructure);
  	TIM_Cmd(TIM2, ENABLE);
	
	//Enable update event for Timer2
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	NVIC_EnableIRQ(TIM2_IRQn);
	
	init();
	UART3_init();
	while(1)
	{
//		if(direction==1)
//		{
//				while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);
//				USART_SendData(USART3,'1');
//			
//			leftforward(200);
//			rightforward(200);
//		}
//		else if(direction==2)
//		{
//				while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);
//				USART_SendData(USART3,'2');
//			rightforward(200);
//			leftforward(400);
//		}
//		else if(direction==3)
//		{
//				while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);
//				USART_SendData(USART3,'3');
//			rightforward(400);
//			leftforward(200);
//		}
	}
	return 0;
}

bool state = false;

void SPI1_IRQHandler(void)
{
	state_int = (char) SPI_I2S_ReceiveData(SPI1) & 0xff;

	// the received character has all the readings
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_7) == 1)
	{
		if (count != 0)
		{
			// keep turning on LEDs
			SPI_I2S_SendData(SPI1, 0xff);
			count--;
		}
		else
		{
			// Set PA7 to 0 to trigger the shift register
			GPIO_ResetBits(GPIOA, GPIO_Pin_7);
			// Go to get the next reading
			SPI_I2S_SendData(SPI1, 0);
			state = true;
		}
	} 
	else 
	{
		if(count == 0 && state == true)
		{
			state = false;
//			sprintf(buffer, "%d\r\n", state_int);
//			USARTSend(buffer, sizeof(buffer));
			//code here
			if((state_int & mask)== mask)
			{	
				direction=1;
				leftforward(200);
				rightforward(200);

			}
			else if((state_int & mask)== 8)
			{
				direction=2;
				rightforward(200);
				leftforward(400);
			}
			else if((state_int & mask)== 16)
			{
				direction=3;
				rightforward(400);
				leftforward(200);
			}
			else if((state_int & mask) ==0)
			{
				rightforward(0);
				leftforward(0);
			}
		}
		// disable the interrupt because it is not ready
		NVIC_DisableIRQ(SPI1_IRQn);
	}
}

//Interrupt Subroutine
void TIM2_IRQHandler(void) 
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 
	{
		readFloor();
	}
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}