#ifndef __EXTI_H
#define __EXIT_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//外部中断 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 
void EXTIX_Init(void);//外部中断初始化		 				

#define S1   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键0
#define S2   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)//读取按键1
#define KEY  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)//读取按键2 
#define LED PCout(13)// PE5	

#endif

