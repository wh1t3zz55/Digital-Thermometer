#ifndef __EXTI_H
#define __EXIT_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//�ⲿ�ж� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 
void EXTIX_Init(void);//�ⲿ�жϳ�ʼ��		 				

#define S1   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ����0
#define S2   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)//��ȡ����1
#define KEY  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)//��ȡ����2 
#define LED PCout(13)// PE5	

#endif

