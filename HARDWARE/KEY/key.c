#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"

void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;//KEY
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOE4 5 6
}

u8 KEY_Scan(void)
{	 
	u8 key=0,i=0;
	if(KEY0==0||KEY1==0||WK_UP==0)
	{
		delay_ms(10);//ȥ���� 
		if(KEY0==0)key=1;
		else if(KEY1==0)key=2;
		else if(WK_UP==0)key=4;
		while(i++<200)delay_ms(1);
	}
 	return key;// �ް�������
}
