#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"

void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;//KEY
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOE4 5 6
}

u8 KEY_Scan(void)
{	 
	u8 key=0,i=0;
	if(KEY0==0||KEY1==0||WK_UP==0)
	{
		delay_ms(10);//去抖动 
		if(KEY0==0)key=1;
		else if(KEY1==0)key=2;
		else if(WK_UP==0)key=4;
		while(i++<200)delay_ms(1);
	}
 	return key;// 无按键按下
}
