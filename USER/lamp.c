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
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//使能或者失能APB1外设时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
  
	//改变指定管脚的映射
	GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2,ENABLE);//复用功能部分映射
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
	
	//PA7     ------> TIM3_CH2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
  
	//GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);//SWJ完全失能（JTAG+SW-DP）
}



void TIM_Configuration()
{
	//TIM2
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure1;
  TIM_TimeBaseStructure.TIM_Period = 100; //设置了在下一个更新事件装入活动的自动重装载寄存器周期的值
  TIM_TimeBaseStructure.TIM_Prescaler = 0;//TIMx时钟频率除数的预分频值                 到元件频率72降????
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x000;//
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	//TIM3
  TIM_TimeBaseStructure1.TIM_Period = 100; //设置了在下一个更新事件装入活动的自动重装载寄存器周期的值
  TIM_TimeBaseStructure1.TIM_Prescaler = 0;//TIMx时钟频率除数的预分频值
  TIM_TimeBaseStructure1.TIM_ClockDivision = 0x000;//
  TIM_TimeBaseStructure1.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure1);
}
void PWM_Configuration()
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure1;
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//TIM1脉冲宽度调制模式1 
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//TIM1输出比较N极性高
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//使能输出比较N状态
  TIM_OCInitStructure.TIM_Pulse = 500;//待装入捕获比较寄存器的脉冲值
  TIM_OC4Init(TIM2, &TIM_OCInitStructure);//
  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);//使能或者失能TIM1在CCR3上的预装载寄存器2
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);//
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM2, ENABLE);
  TIM_Cmd(TIM2, ENABLE);
	
  TIM_OCInitStructure1.TIM_OCMode = TIM_OCMode_PWM1;//TIM1脉冲宽度调制模式1 
  TIM_OCInitStructure1.TIM_OCPolarity = TIM_OCPolarity_High;//TIM1输出比较N极性高
  TIM_OCInitStructure1.TIM_OutputState = TIM_OutputState_Enable;//使能输出比较N状态
  TIM_OCInitStructure1.TIM_Pulse = 500;//待装入捕获比较寄存器的脉冲值
  TIM_OC2Init(TIM3, &TIM_OCInitStructure1);//
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);//使能或者失能TIM1在CCR3上的预装载寄存器
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
