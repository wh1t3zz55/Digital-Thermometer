#include "temp.h"
#include "delay.h"
#include "sys.h"

void ADC_Configuration(void)  //ADC通道初始化
{
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //使能GPIOA,ADC1通道时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //分频因子6时钟为72M/6=12MHz

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  ADC_DeInit(ADC1);  //将外设 ADC1 的全部寄存器重设为缺省值
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器

	ADC_TempSensorVrefintCmd(ENABLE); //开启内部温度传感器
	
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1

	ADC_ResetCalibration(ADC1);	//重置指定的ADC1的复位寄存器

  while(ADC_GetResetCalibrationStatus(ADC1));	//获取ADC1重置校准寄存器的状态,设置状态则等待

	ADC_StartCalibration(ADC1);	 //

	while(ADC_GetCalibrationStatus(ADC1));		//获取指定ADC1的校准程序,设置状态则等待
	
}

u16 Get_Adc(u8 ch)   
{
 
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道3,第一个转换,采样时间为239.5周期	  			    
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
	}

//获取通道ch的转换值,取times次,然后平均
u16 Get_Adc_Average(u8 ch,u8 time)
{
	u32 num=0;
	u8 t;
	for(t=0;t<time;t++)
	{
		num+=Get_Adc(ch);
		delay_ms(5);
	}
	return num/time;
} 	   

void  ADC_NVIC_Config()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void ADC1_2_IRQHandler()
{
	int AD_value;
	if(ADC_GetITStatus(ADC1,ADC_IT_EOC )==SET )
	{
		AD_value = ADC_GetConversionValue (ADC1);
	}
	ADC_ClearITPendingBit (ADC1,ADC_IT_EOC );
}

void Temp_init()
{
	ADC_Configuration();
	ADC_NVIC_Config();
}

//得到温度值
//返回值:温度值(扩大了100倍,单位:℃.)
int     Get_Temprate(void)	//获取内部温度传感器温度值
{
	u32 adcx;
	int  result;
 	double temperate;
	adcx=Get_Adc_Average(ADC_Channel_0,20);	//读取通道0,20次取平均
	temperate=(float)adcx*(3.3/4096);		//电压值 
	temperate=(1.43-temperate)/0.0043+25;	//转换为温度值 	 
	result=temperate*=100;	//扩大100倍.
	//result=temperate;
	return    result;
}
