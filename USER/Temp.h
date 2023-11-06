#ifndef __TEMP_H
#define __TEMP_H	
#include "stm32f10x.h"
int  Get_Temprate(void);             //获取内部温度传感器温度值
void  ADC_Configuration(void);       //ADC通道初始化
u16   Get_Adc(u8 ch);                //获得某个通道值  
u16   Get_Adc_Average(u8 ch,u8 time);//得到某个通道TIME次采样的平均值 	  
void  ADC_NVIC_Config();

void Temp_Init();

#endif 
