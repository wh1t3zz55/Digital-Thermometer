#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define LED0 PBout(5)// PB5
#define LED1 PEout(5)// PE5	

#define KEY_A  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)//��ȡ����0 
#define KEY_B  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)//��ȡ����0 
#define KEY_C  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//��ȡ����0 
#define KEY_D  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//��ȡ����0 
#define KEY_E  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//��ȡ����0 

void LED_Init(void);//��ʼ��
u8 KEY16_Scan(void);
		 				    
#endif
