#ifndef _MENU_H
#define _MENU_H
//#include "codetab.h"

#include "BMP.h"
#include "delay.h"
#include "stm32f10x.h"
#include "OLED_I2C.h"
#include "exti.h"
#include "stdio.h"
#include "key.h"
#include "stmflash.h"
//温度
#include "Temp.h"
//三色灯
#include "lamp.h"
//通信
#include "usart.h"

#define FLASH_SAVE_ADDR  0X08009000		//设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小+0X08000000)
#define linenumber 4

struct MenuItem
{
	short MenuCount;//当前菜单项目总数
	u8 *DisplayString;//当前项目要显示的字符
	void(*Subs)();//选择某一菜单后执行的功能函数
	struct MenuItem *ChildrenMenus;//当前项目的子菜单
	struct MenuItem *ParentMenus;//当前项目的父菜单
};
struct mydata
{
	float number1;
	float number2;
	float number3;
};
struct mydata rmydata;
int selectItem_current,selectItem_hidden,selectItem;
//    当前行数          隐藏的行数      前面两项之和
int key_num=0;
int juli,jiaodu;

void caidan(void);
int  key_scan(void);//是否按下确认键
void display(struct MenuItem * MenuPoint,int selectItem_current,int selectItem_hidden);
void caidan_init(void);
void fun1(void);
void f_init(void);
void f_show(void);
void f_set(void);

void Celsius();   //华氏温度
void Fahrenheit();//摄氏温度

void light(int colur);
void light1();
int Compare(int temp);

void USA();
void us();

int my_min(int a,int b)
{
	if (a<b)return a;
	return b;
}
//由于定义从上往下，数组定义时子类都为NULL
//第一级
struct MenuItem MainMenu[5] = {
{ 5,(u8 *)"Hello!(@^_^@)"  ,NULL,NULL,NULL },
{ 5,(u8 *)"温度模块",NULL,NULL,NULL },
{ 5,(u8 *)"串口通信"   ,NULL,NULL,NULL },
{ 5,(u8 *)"Flash"   ,NULL,NULL,NULL },
{ 5,(u8 *)"About us",us,NULL,NULL },
};

//第二级父菜单为根目录
//第二级(温度模块)
struct MenuItem Setmenu1[5]={
{ 5,(u8 *)"返回上一级",NULL,      NULL,MainMenu },
{ 5,(u8 *)"三色灯"    ,light1,    NULL,MainMenu },
{ 5,(u8 *)"华氏温度"  ,Fahrenheit,NULL,MainMenu },
{ 5,(u8 *)"摄氏温度"  ,Celsius,   NULL,MainMenu },
{ 5,(u8 *)"确定"      ,NULL,      NULL,MainMenu },
};

//第二级2(DAC)
struct MenuItem Setmenu2[3] = {
{ 3,(u8 *)"返回上一级",NULL,NULL,MainMenu },
{ 3,(u8 *)"USART"     ,USA, NULL,MainMenu },
{ 3,(u8 *)"确定"      ,NULL,NULL,MainMenu }
};

//第二级(flash)
struct MenuItem Setmenu3[4]={
{ 4,(u8 *)"返回上一级",NULL,  NULL,MainMenu },
{ 4,(u8 *)"参数初始化",f_init,NULL,MainMenu },
{ 4,(u8 *)"读取学号"  ,f_show,NULL,MainMenu },//读取学号并显示
{ 4,(u8 *)"修改学号"  ,f_set ,NULL,MainMenu },//读取学号并显示
};



struct MenuItem* MenuPoint=MainMenu;//当前菜单

void caidan_init(void)
{
	MainMenu[1].ChildrenMenus = Setmenu1;
	MainMenu[2].ChildrenMenus = Setmenu2;
	MainMenu[3].ChildrenMenus = Setmenu3;
	selectItem_current =1;
	selectItem_hidden  =0;
	selectItem=selectItem_current+selectItem_hidden;
	display(MenuPoint,selectItem_current,selectItem_hidden);
}

void display(struct MenuItem * MenuPoint,int selectItem_current,int selectItem_hidden)
{
	int j;
	u16 x=16;
	u16 y=0;
	OLED_Show(0,selectItem_current*2-2,(u8 *)"->");
	for ( j= selectItem_hidden; j < my_min(MenuPoint->MenuCount,linenumber+selectItem_hidden);j++)
	{                               //j循环到设置的行数+隐藏的行数 停止 刚好显示设置当前行
		OLED_Show(x,y,MenuPoint[j].DisplayString);
		y+=2;
	}
}

void caidan(void)
{
	
	if(key_num>0)
	{
	switch(key_num)
	{
		case WKUP_PRES:
		{//上
			OLED_CLS();
			selectItem_current--;   //当前行数减一
			if (selectItem_current==0)
			{
				if(selectItem_hidden>0)selectItem_hidden--;//如果存在隐藏的行数  隐藏行数减一
				selectItem_current++;//当前行数加一
			}
			selectItem=selectItem_current+selectItem_hidden;
			display(MenuPoint,selectItem_current,selectItem_hidden);
			
		};break;
		case KEY1_PRES:
		{//下
			OLED_CLS();
			selectItem_current++;//当前的行数加一
			
			if(selectItem_current>linenumber)//当前的行数超过设定行数(4)
			{
				if (selectItem_current+selectItem_hidden <= MenuPoint->MenuCount)//当前的行数<=菜单总行数
					selectItem_hidden++;
				selectItem_current--;
			}       
			else if(selectItem_current>MenuPoint->MenuCount)//当前的行数超过菜单总行数  比如当前菜单只有一行
				selectItem_current--;
			selectItem=selectItem_current+selectItem_hidden;
			display(MenuPoint,selectItem_current,selectItem_hidden);
			

		};break;
		case KEY0_PRES:
		{//右 确认进入此项目
			if(selectItem== 1&&MenuPoint!=MainMenu)//满足退回上一级条件
			{
					OLED_CLS();
					MenuPoint = MenuPoint[selectItem - 1].ParentMenus;
					selectItem_current =1;//当前页面的初始化
					selectItem_hidden  =0;//当前页面的初始化
					//selectItem = 1;
					display(MenuPoint,selectItem_current,selectItem_hidden);
			}
			else if (MenuPoint[selectItem - 1].ChildrenMenus != NULL)//判断是否有下一级
			{				
				OLED_CLS();
				MenuPoint = MenuPoint[selectItem - 1].ChildrenMenus;   //等于当前菜单的子集
				selectItem_current =1;
				selectItem_hidden  =0;
				display(MenuPoint,selectItem_current,selectItem_hidden);
			}
			else if(MenuPoint[selectItem - 1].Subs != NULL)
				MenuPoint[selectItem - 1].Subs();//功能函数执行
		};break;
	}
	
 }
	
}
int Compare(int temp)
{
	int flag;
	if(temp<2500)
		flag = 0;
	else if(temp>2500&&temp<30000)
		flag = 1;
	else if(temp>30000)
    flag = 2;
  return flag;	
}

void light1()//
{
	char str[5];
	OLED_CLS();
	sprintf(str,"1红色%d",1);
	OLED_Show(32,3,(u8*)str);
  TIM_SetCompare4(TIM2,000);//红
	delay_ms(20000);
	TIM_SetCompare4(TIM2,999);//?
	OLED_CLS();
	
	sprintf(str,"1绿色%d",1);
	OLED_Show(32,3,(u8*)str);
	TIM_SetCompare3(TIM2,000);//绿
	delay_ms(20000);
	TIM_SetCompare3(TIM2,999);//?
	OLED_CLS();
	
	sprintf(str,"1蓝色%d",1);
	OLED_Show(32,3,(u8*)str);
  TIM_SetCompare2(TIM3,000);//蓝
	delay_ms(20000);
	TIM_SetCompare2(TIM3,999);//?
	OLED_CLS();
}
void light(int temp)
{
	char str[30];
	if(temp<2500)
	{
	  sprintf(str,"1[-0,25]绿色%d",1);
	  OLED_Show(16,6,(u8*)str);
		TIM_SetCompare3(TIM2,000);//绿
	}
	if(temp>2500&&temp<3000)
	{
		sprintf(str,"1(25,30]蓝色%d",1);
		OLED_Show(16,6,(u8*)str);
    TIM_SetCompare2(TIM3,000);//蓝
	}
	if(temp>3000)
	{
		sprintf(str,"1(30,100]红色%d",1);
		OLED_Show(16,6,(u8*)str);
    TIM_SetCompare4(TIM2,000);//红
	}
}
void Celsius()//摄氏温度
{
	int  temp;
	char I[10],C[1],D[10];
	C[0] ='.';
	temp = Get_Temprate ();	
	sprintf(I,"%d",temp/100);//ShowStr只能接收字符型
	sprintf(D,"%d",temp%100);
	OLED_CLS();
	//一个汉字16个位
  OLED_ShowCN(32,0,26);//摄
	OLED_ShowCN(48,0,25);//氏
	OLED_ShowCN(64,0,1);//温
	OLED_ShowCN(80,0,2);//度

  OLED_ShowStr(40,3,I,2);//整数部分+16 +8
  OLED_ShowStr(56,3,C,2);//小数点(居中)
  OLED_ShowStr(64,3,D,2);//小数部分
	
  light(temp);
}

void Fahrenheit()//华氏温度
{ int  temp,i;
	char I[10],C[1],D[10];
	i=16;
	C[0] ='.';
	temp = Get_Temprate ();	
	temp = temp*180+3200;
	sprintf(I,"%d",temp/100);//ShowStr只能接收字符型
	sprintf(D,"%d",temp%100);

	OLED_CLS();
  OLED_ShowCN(32,0,24);//华
	OLED_ShowCN(48,0,25);//氏
	OLED_ShowCN(64,0,1); //温
	OLED_ShowCN(80,0,2); //度

  OLED_ShowStr(40,3,I,2);//整数部分+16 +8
  OLED_ShowStr(56,3,C,2);//小数点(居中)
  OLED_ShowStr(64,3,D,2);//小数部分
}
void Delayms(vu32 m)
{
	u32 i;
	for(;m!=0;m--)
		for(i=0;i<50000;i++);
}
void USA()
{
	int  temp;
	int F,N;
	u32 adcx;
	temp = Get_Temprate ();	
	printf("/*************************************/\r\n");
	printf("/*                                   */\r\n");
	printf("/*    This is ADC Demo! ^_^   *\r\n");
	printf("/*************************************/\r\n");
	F=temp/1000;
	N=temp%100;
	printf("r\n  Current temperature :%d.%d    \r\n",F,N);

	Delayms(2);
}

void us()
{
  char H[20],Y[20],T[20];
	OLED_CLS();
	
	sprintf(T,"感谢使用1(^O^)%d",1);
	OLED_Show(8,0,(u8*)T);
	
	sprintf(H,"%d 郝久程",(int)rmydata.number1);
	OLED_Show(16,3,(u8*)H);
	
	sprintf(Y,"%d 云逸阳",(int)rmydata.number2);
	OLED_Show(16,6,(u8*)Y);
	
	
}

         
void f_init()//初始化参数
{
	rmydata.number1 =190414;
	rmydata.number2 =190418;
	rmydata.number3 =190;
	STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)&rmydata,sizeof(rmydata));
}
void f_show()//读取并显示
{
	u8 key;
	char str[10];
	OLED_CLS();
	STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)&rmydata,sizeof(rmydata));
	sprintf(str,"学号1:%d",(int)rmydata.number1);
	OLED_Show(16,0,(u8*)str);
	sprintf((char*)str,"学号2:%d",(int)rmydata.number2 );
	OLED_Show(16,2,(u8*)str);
	sprintf((char*)str,"学号3:%d",(int)rmydata.number3 );
	OLED_Show(16,4,(u8*)str);
	while(1)
	{
		key=KEY_Scan();
		delay_ms(20);
		if(key!=0)
		{
			OLED_CLS();
			display(MenuPoint,selectItem_current,selectItem_hidden);
			return;
		}
	}
}

void f_set()
{
	char str[10];
	u8 ans[3],flg=2,sign=0;//jieshu =1 时可以对对象本体进行操作 
	int current_length;
	u8 i,key;
	int time=0;
	current_length=rmydata.number3 *1000;
	ans [0] = current_length/10000; //年级
	ans [1] = current_length/100%10;//班级
	ans [2] = current_length%100;   //班级位数
	OLED_CLS();
	while(1)
	{
		key=KEY_Scan();
		delay_ms(20);
		if(key!=0)
		{    //右按键
			if(key==1)sign=!sign;
			else if(key==2)//下键
			{
				if(sign==0)flg++;
				else if(flg<=2) ans [flg]--;
			}
			else if(key==3)//左键
			{
				OLED_CLS();
				display(MenuPoint,selectItem_current,selectItem_hidden);
				rmydata.number3 =current_length;
				STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)&rmydata,sizeof(rmydata));
				return;
			}
			else if(key==4)
			{
				if(sign==0)flg--;
				else if(flg<=2) ans [flg]++;
			}
			if(flg>=3)flg=2;
			OLED_CLS();
		}          
		time++;      
		if(time<=20)
		{//.前一位的正下方显示^
			if(flg==0)OLED_Show(8*9,2,(u8*)"^");//5
			//.后的某一位正下方显示↑
			else OLED_Show(8*9+8*flg,2,(u8*)"^");
		}
		else if(time<=40){if(sign==0)OLED_Show(0,2,(u8*)"                ");}
		else time=0;
		for(i=0;i<3;i++)
		current_length=ans [0]*10000+ans [1]*100+ans [2];
		sprintf((char*)str,"学号3:%d",(int)current_length);
		OLED_Show(0,0,(u8*)str);
	}
}
#endif