#ifndef __TEMP_H
#define __TEMP_H	
#include "stm32f10x.h"
int  Get_Temprate(void);             //��ȡ�ڲ��¶ȴ������¶�ֵ
void  ADC_Configuration(void);       //ADCͨ����ʼ��
u16   Get_Adc(u8 ch);                //���ĳ��ͨ��ֵ  
u16   Get_Adc_Average(u8 ch,u8 time);//�õ�ĳ��ͨ��TIME�β�����ƽ��ֵ 	  
void  ADC_NVIC_Config();

void Temp_Init();

#endif 
