#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"


#define KEY0    GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)//��ȡ����0
#define KEY1    GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)//��ȡ����1
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//��ȡ����3(WK_UP) 


#define KEY0_PRES 	1	//KEY0����
#define KEY1_PRES	  2	//KEY1����
#define WKUP_PRES   4	//KEY_UP����(��WK_UP/KEY_UP)


void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(void);//����ɨ�躯��	


#endif
//void EXTIX_Init(void);