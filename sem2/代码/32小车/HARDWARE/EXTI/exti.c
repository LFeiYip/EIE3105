#include "exti.h"
#include "stm32f10x.h"
//#include "key.h"
#include "led1.h"
#include "delay.h"
void exti_Init(void)
{
	
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
//	KEY_Init();//��ʼ��������Ӧ��IO��ģʽ
	
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA,ENABLE);//ʹ��GPIOA��Ӧ��ʱ�ӣ�ͬʱ��������ʱ�ӣ����Ÿ��ã�
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);//GPIOC.5�ж����Լ��жϳ�ʼ������
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);//GPIOA.15�ж���ӳ��

	//GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); 

	
/*GPIO_InitTypeDef GPIO_InitStucture;
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);//����IO�����ж��ߵ�ӳ���ϵ
	GPIO_InitStucture.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStucture.GPIO_Pin=GPIO_Pin_15;
	GPIO_InitStucture.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStucture);//��ʼ��GPIOA.15Ϊ����
	*///���Ѿ���KEY_Init();������
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Event;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//�½��ش���
	
	
	EXTI_Init(&EXTI_InitStructure);//���ô����жϵ��������
	
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line15;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Event;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//�½��ش���	
	EXTI_Init(&EXTI_InitStructure);//���ô����жϵ��������
	
	  //GPIOA.0   
 
    /*EXTI_InitStructure.EXTI_Line=EXTI_Line0; 
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;    
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�����ش���
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;   
		EXTI_Init(&EXTI_InitStructure); */  
	
	/*NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn; //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02;//������ռ���ȼ�Ϊ2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x01;//���������ȼ�Ϊ1
	NVIC_Init(&NVIC_InitStructure);*/
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI9_5_IRQn; //ʹ��ͨ��5
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02; //????? 2,    
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;  //???? 1 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   //????????    
	NVIC_Init(&NVIC_InitStructure);   
	
	
	NVIC_InitStructure.NVIC_IRQChannel =  EXTI15_10_IRQn; ; //ʹ��ͨ��5
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02; //????? 2,    
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;  //???? 1 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   //????????    
	NVIC_Init(&NVIC_InitStructure);   
}


/*void EXTI0_IRQHandler(void) 
	{   
		delay_ms(10);  
if(WK_UP==1) 
	{     
		LED0=!LED0;   
		LED1=!LED1; 
  } 
	EXTI_ClearITPendingBit(EXTI_Line0);  
	}  
	 
	 
 
 
  void EXTI9_5_IRQHandler(void)
		{    
			delay_ms(10);   
		if(KEY0==0)
  {  
	LED0=!LED0; 
	}
		EXTI_ClearITPendingBit(EXTI_Line5);   
	} 
 
void EXTI15_10_IRQHandler(void) 
	{   delay_ms(10);    //??  
		if(KEY1==0)
			{  
				LED1=!LED1; 
			} 
			EXTI_ClearITPendingBit(EXTI_Line15); 
			
			
	} 
	*/
	
	
	


