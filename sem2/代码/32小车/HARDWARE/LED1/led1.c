#include "led1.h"
#include "stm32f10x.h"

void LED1_Init(void)
{
	
		GPIO_InitTypeDef GPIO_InitStructure;  //GPIO�ܽŵĽṹ�嶨��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��GPIO��ʱ��B

		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//IO�ܽ����ģʽΪ�����������ģʽ�ȿ�������ߵ�ƽ��͵�ƽ
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;//12�Źܽ�
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//IO�ܽŵĴ����ٶ�
		GPIO_Init(GPIOB,&GPIO_InitStructure);//PB12�ܽ�����
	
		GPIO_SetBits(GPIOB,GPIO_Pin_12);	//PB12�ܽ�����ߵ�ƽ
	  



}






