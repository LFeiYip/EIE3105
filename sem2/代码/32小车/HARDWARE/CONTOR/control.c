#include "control.h"	
#include "cs.h"
#include "usart.h"
#include "lunzi.h"
#include "key.h"
#include "lk.h"

int OUTPUT,OUTPUT1,OUTPUT2;// OUTPUT �ǿ��ƶ����PWM���ֵ; OUTPUT1 ��OUTPUT2 �ǿ���С���������ٶȵ�PWM���ֵ

int PID_value=0;//���PID��������PWM���ֵ

int PID_sd=0;//С������PID��������PWM���ֵ

int PID_jc=0;//С�������ٶ�PID��������PWM���ֵ

extern int error;//����lk.c�����error�������ڱ��ļ���ʹ��error�ñ���  //��Ϊ���PID�������Ͳ���PID�������Ĵ�������ֵ

extern int a;//����lk.c�����a�������ڱ��ļ���ʹ��a�ñ���  //��Ϊ�����ٶ�PID�������Ĵ�������ֵ

void TIM3_IRQHandler(void)   //TIM3�жϷ�����
{
	if(TIM3->SR&0X0001)//��ʱ��ÿ10ms��ʱ�ж�һ��
	{   
		  TIM3->SR&=~(1<<0);//�����ʱ�����ļ�ʱ��־��ִ����TIM3�жϷ�������Ĳ�����ʱ�������¼�ʱ
   		PID_value=Position_PD (error,0);//�����PID�����������PWMֵ��ֵ��PID_value  //��error��0����
		  PID_sd=Position_PID (error,0);//������PID�����������PWMֵ��ֵ��PID_sd       //��error��0����
		  PID_jc=Position_P (a,0);//�������ٶ�PID�����������PWMֵ��ֵ��PID_jc         //��a��0����
		  Xianfu_PID();//�޷�����
			Su();//PWM�������
		}
}

/*���������õ�PID����ȫ��������λ��ʽPID*/

int Position_P (int Encoder,int Target)   //�����ٶ�PID������//����Encoder=a��Target=0;
{  
	 float Position_KP=160,Position_KD=90; //������������Ҫ�����ʺ��Լ�С������ֵ��С  //��Ϊû���õ�KI(����)����������ȥ���˺�KI��ص�ʽ��
	 static float Bias,Pwm,Last_Bias;
	 Bias=Encoder-Target; //ƫ��=ʵ��ֵ-Ŀ��ֵ
	 Pwm=7200-Position_KP*Bias+Position_KD*(Bias-Last_Bias);//λ��ʽPID������//����7200��С�����PWM�����ֵ��Ҳ����������TIM2�Ĵ��δ����������errorΪ��ʱ����ʾС�����ں��ߵ����룬û��ƫ�ƣ�������ʱa=0��ʹ����󷵻ص�PWMֵΪ7200��ʹ����ﵽ����ٶ�
	 Last_Bias=Bias;                                       //������һ��ƫ�� 
	 return Pwm;                                           //����PWMֵ
}


int Position_PD (int Encoder,int Target)   //���PID������//����Encoder=error��Target=0;
{ 	
	 float Position_KP=35,Position_KI=0.01,Position_KD=440;
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //����ƫ��
	 Integral_bias+=Bias;	                                 //���ƫ��Ļ���
	 Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       //λ��ʽPID������
	 Last_Bias=Bias;                                       //������һ��ƫ�� 
	 return Pwm;                                           //����PWMֵ
}
int Position_PID (int Encoder,int Target)   //����PID������//����Encoder=error��Target=0;
{ 	
	 float Position_KP=240,Position_KI=0.5,Position_KD=4500;
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //����ƫ��
	 Integral_bias+=Bias;	                                 //���ƫ��Ļ���
	 Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       //λ��ʽPID������
	 Last_Bias=Bias;                                       //������һ��ƫ�� 
	 return Pwm;                                           //����PWMֵ
}
void Su(void)//��OUTPUT��OUTPUT1��OUTPUT2�����ȥ��ʹ�����С������ܵ���Ӧ����
{
		  
			TIM_SetCompare1(TIM4,OUTPUT); //�������
			TIM_SetCompare3(TIM2,OUTPUT1);//�������
	    TIM_SetCompare4(TIM2,OUTPUT2);//�������

}	




void Xianfu_PID(void)//�޷�
{	
	  OUTPUT=1580+PID_value;//1580ʱ����������Ӹ˺ͺ����غϣ�Ҳ���Ǵ�������λ��
	  OUTPUT1=PID_jc+PID_sd;//�����ٶ�+�ٶ�ƫ���� //�����ٶ�Ҳ���Ժ㶨Ϊĳ��ֵ�����������ٺͶ���ͱȽϺõ�
	  OUTPUT2=PID_jc-PID_sd;//�����ٶ�-�ٶ�ƫ����
	
		 /*���ƶ����PWM��Чֵ��ΧΪ500-2500*/
    if(OUTPUT>2500) OUTPUT=2500;
    if(OUTPUT<500) OUTPUT=500;
	   /*����С�������PWM��Чֵ��ΧΪ0-7200*/
	  if(OUTPUT1>7200) OUTPUT1=7200;
    if(OUTPUT1<0) OUTPUT1=0;
	  if(OUTPUT2>7200) OUTPUT2=7200;
    if(OUTPUT2<0) OUTPUT2=0;
		
}



