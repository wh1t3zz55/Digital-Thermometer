
#include "Menu.h"

int main(void)
{
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	I2C_Configuration();
	OLED_Init();	
	OLED_CLS();
	KEY_Init();
	
	uart_init();

	ADC_Configuration();//ADC初始化	
	ADC_NVIC_Config();
	
	Lamp_Init(); //三色灯初始化
	
	caidan_init();
	f_init();//第一次下载需要去掉fun2()前面的注释，不然程序直接卡死
	STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)&rmydata,sizeof(rmydata));
		
	while(1)
	{
		key_num=KEY_Scan();
		caidan();
		delay_ms(20);
	}
	return 0;
}
