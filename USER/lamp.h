#ifndef _LAMP_H
#define _LAMP_H
#include "stm32f10x.h"                 

  void RCC_Configuration();
	void GPIO_Configuration();
	void TIM_Configuration();
	void PWM_Configuration();
  void Lamp_Init();
#endif
