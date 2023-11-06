#include "lamp.h"
void GPIO_Configuration()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure1;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure1);
}

void RCC_Configuration()
{
	/*TIM2 GPIO Configuration    
	PB10     ------> TIM2_CH3
	PB11     ------> TIM2_CH4 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//ʹ�ܻ���ʧ��APB1����ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
  
	//�ı�ָ���ܽŵ�ӳ��
	GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2,ENABLE);//���ù��ܲ���ӳ��
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
	
	//PA7     ------> TIM3_CH2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
  
	//GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);//SWJ��ȫʧ�ܣ�JTAG+SW-DP��
}



void TIM_Configuration()
{
	//TIM2
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure1;
  TIM_TimeBaseStructure.TIM_Period = 100; //����������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
  TIM_TimeBaseStructure.TIM_Prescaler = 0;//TIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ                 ��Ԫ��Ƶ��72��????
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x000;//
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	//TIM3
  TIM_TimeBaseStructure1.TIM_Period = 100; //����������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
  TIM_TimeBaseStructure1.TIM_Prescaler = 0;//TIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
  TIM_TimeBaseStructure1.TIM_ClockDivision = 0x000;//
  TIM_TimeBaseStructure1.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure1);
}
void PWM_Configuration()
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure1;
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//TIM1�����ȵ���ģʽ1 
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//TIM1����Ƚ�N���Ը�
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//ʹ������Ƚ�N״̬
  TIM_OCInitStructure.TIM_Pulse = 500;//��װ�벶��ȽϼĴ���������ֵ
  TIM_OC4Init(TIM2, &TIM_OCInitStructure);//
  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);//ʹ�ܻ���ʧ��TIM1��CCR3�ϵ�Ԥװ�ؼĴ���2
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);//
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM2, ENABLE);
  TIM_Cmd(TIM2, ENABLE);
	
  TIM_OCInitStructure1.TIM_OCMode = TIM_OCMode_PWM1;//TIM1�����ȵ���ģʽ1 
  TIM_OCInitStructure1.TIM_OCPolarity = TIM_OCPolarity_High;//TIM1����Ƚ�N���Ը�
  TIM_OCInitStructure1.TIM_OutputState = TIM_OutputState_Enable;//ʹ������Ƚ�N״̬
  TIM_OCInitStructure1.TIM_Pulse = 500;//��װ�벶��ȽϼĴ���������ֵ
  TIM_OC2Init(TIM3, &TIM_OCInitStructure1);//
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);//ʹ�ܻ���ʧ��TIM1��CCR3�ϵ�Ԥװ�ؼĴ���
  TIM_ARRPreloadConfig(TIM3, ENABLE);
  TIM_Cmd(TIM3, ENABLE);
}
void Lamp_Init()
{
	 RCC_Configuration();
	 GPIO_Configuration();
	 TIM_Configuration();
	 PWM_Configuration();
}
