
#include "Menu.h"

int main(void)
{
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	I2C_Configuration();
	OLED_Init();	
	OLED_CLS();
	KEY_Init();
	
	uart_init();

	ADC_Configuration();//ADC��ʼ��	
	ADC_NVIC_Config();
	
	Lamp_Init(); //��ɫ�Ƴ�ʼ��
	
	caidan_init();
	f_init();//��һ��������Ҫȥ��fun2()ǰ���ע�ͣ���Ȼ����ֱ�ӿ���
	STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)&rmydata,sizeof(rmydata));
		
	while(1)
	{
		key_num=KEY_Scan();
		caidan();
		delay_ms(20);
	}
	return 0;
}
