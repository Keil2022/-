#include "motor.h"

int PWM_MAX=7200,PWM_MIN=-7200;	//PWM�޷�����

/*�����ʼ������*/
void Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOG, ENABLE);//����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); //PA15ΪJTAG�ڵ��Կڣ���Ҫ����ӳ��һ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_6;;
	GPIO_Init(GPIOD,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOG,&GPIO_InitStruct);
	
	STBY = 1;
}

/*�޷�����*/
void Limit(int *motoA,int *motoB)
{
	if(*motoA>PWM_MAX)*motoA=PWM_MAX;
	if(*motoA<PWM_MIN)*motoA=PWM_MIN;
	
	if(*motoB>PWM_MAX)*motoB=PWM_MAX;
	if(*motoB<PWM_MIN)*motoB=PWM_MIN;
}

/*����ֵ����*/
int GFP_abs(int p)
{
	int q;
	q=p>0?p:(-p);
	return q;
}

/*��ֵ����*/
/*��ڲ�����PID������ɺ������PWMֵ*/
void Load(int moto1,int moto2)//moto1=-200����ת200������
{
	if(moto1>0)	Bin1=0,Bin2=1;
	else 		Bin1=1,Bin2=0;	
	TIM_SetCompare4(TIM4,GFP_abs(moto1));
	
	//1.�о������ţ���Ӧ����ת
	if(moto2>0)	Ain1=0,Ain2=1;//��ת
	else 		Ain1=1,Ain2=0;//��ת
	//2.�о�PWMֵ
	TIM_SetCompare3(TIM4,GFP_abs(moto2));
}
