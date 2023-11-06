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
//�¶�
#include "Temp.h"
//��ɫ��
#include "lamp.h"
//ͨ��
#include "usart.h"

#define FLASH_SAVE_ADDR  0X08009000		//����FLASH �����ַ(����Ϊż��������ֵҪ���ڱ�������ռ��FLASH�Ĵ�С+0X08000000)
#define linenumber 4

struct MenuItem
{
	short MenuCount;//��ǰ�˵���Ŀ����
	u8 *DisplayString;//��ǰ��ĿҪ��ʾ���ַ�
	void(*Subs)();//ѡ��ĳһ�˵���ִ�еĹ��ܺ���
	struct MenuItem *ChildrenMenus;//��ǰ��Ŀ���Ӳ˵�
	struct MenuItem *ParentMenus;//��ǰ��Ŀ�ĸ��˵�
};
struct mydata
{
	float number1;
	float number2;
	float number3;
};
struct mydata rmydata;
int selectItem_current,selectItem_hidden,selectItem;
//    ��ǰ����          ���ص�����      ǰ������֮��
int key_num=0;
int juli,jiaodu;

void caidan(void);
int  key_scan(void);//�Ƿ���ȷ�ϼ�
void display(struct MenuItem * MenuPoint,int selectItem_current,int selectItem_hidden);
void caidan_init(void);
void fun1(void);
void f_init(void);
void f_show(void);
void f_set(void);

void Celsius();   //�����¶�
void Fahrenheit();//�����¶�

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
//���ڶ���������£����鶨��ʱ���඼ΪNULL
//��һ��
struct MenuItem MainMenu[5] = {
{ 5,(u8 *)"Hello!(@^_^@)"  ,NULL,NULL,NULL },
{ 5,(u8 *)"�¶�ģ��",NULL,NULL,NULL },
{ 5,(u8 *)"����ͨ��"   ,NULL,NULL,NULL },
{ 5,(u8 *)"Flash"   ,NULL,NULL,NULL },
{ 5,(u8 *)"About us",us,NULL,NULL },
};

//�ڶ������˵�Ϊ��Ŀ¼
//�ڶ���(�¶�ģ��)
struct MenuItem Setmenu1[5]={
{ 5,(u8 *)"������һ��",NULL,      NULL,MainMenu },
{ 5,(u8 *)"��ɫ��"    ,light1,    NULL,MainMenu },
{ 5,(u8 *)"�����¶�"  ,Fahrenheit,NULL,MainMenu },
{ 5,(u8 *)"�����¶�"  ,Celsius,   NULL,MainMenu },
{ 5,(u8 *)"ȷ��"      ,NULL,      NULL,MainMenu },
};

//�ڶ���2(DAC)
struct MenuItem Setmenu2[3] = {
{ 3,(u8 *)"������һ��",NULL,NULL,MainMenu },
{ 3,(u8 *)"USART"     ,USA, NULL,MainMenu },
{ 3,(u8 *)"ȷ��"      ,NULL,NULL,MainMenu }
};

//�ڶ���(flash)
struct MenuItem Setmenu3[4]={
{ 4,(u8 *)"������һ��",NULL,  NULL,MainMenu },
{ 4,(u8 *)"������ʼ��",f_init,NULL,MainMenu },
{ 4,(u8 *)"��ȡѧ��"  ,f_show,NULL,MainMenu },//��ȡѧ�Ų���ʾ
{ 4,(u8 *)"�޸�ѧ��"  ,f_set ,NULL,MainMenu },//��ȡѧ�Ų���ʾ
};



struct MenuItem* MenuPoint=MainMenu;//��ǰ�˵�

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
	{                               //jѭ�������õ�����+���ص����� ֹͣ �պ���ʾ���õ�ǰ��
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
		{//��
			OLED_CLS();
			selectItem_current--;   //��ǰ������һ
			if (selectItem_current==0)
			{
				if(selectItem_hidden>0)selectItem_hidden--;//����������ص�����  ����������һ
				selectItem_current++;//��ǰ������һ
			}
			selectItem=selectItem_current+selectItem_hidden;
			display(MenuPoint,selectItem_current,selectItem_hidden);
			
		};break;
		case KEY1_PRES:
		{//��
			OLED_CLS();
			selectItem_current++;//��ǰ��������һ
			
			if(selectItem_current>linenumber)//��ǰ�����������趨����(4)
			{
				if (selectItem_current+selectItem_hidden <= MenuPoint->MenuCount)//��ǰ������<=�˵�������
					selectItem_hidden++;
				selectItem_current--;
			}       
			else if(selectItem_current>MenuPoint->MenuCount)//��ǰ�����������˵�������  ���統ǰ�˵�ֻ��һ��
				selectItem_current--;
			selectItem=selectItem_current+selectItem_hidden;
			display(MenuPoint,selectItem_current,selectItem_hidden);
			

		};break;
		case KEY0_PRES:
		{//�� ȷ�Ͻ������Ŀ
			if(selectItem== 1&&MenuPoint!=MainMenu)//�����˻���һ������
			{
					OLED_CLS();
					MenuPoint = MenuPoint[selectItem - 1].ParentMenus;
					selectItem_current =1;//��ǰҳ��ĳ�ʼ��
					selectItem_hidden  =0;//��ǰҳ��ĳ�ʼ��
					//selectItem = 1;
					display(MenuPoint,selectItem_current,selectItem_hidden);
			}
			else if (MenuPoint[selectItem - 1].ChildrenMenus != NULL)//�ж��Ƿ�����һ��
			{				
				OLED_CLS();
				MenuPoint = MenuPoint[selectItem - 1].ChildrenMenus;   //���ڵ�ǰ�˵����Ӽ�
				selectItem_current =1;
				selectItem_hidden  =0;
				display(MenuPoint,selectItem_current,selectItem_hidden);
			}
			else if(MenuPoint[selectItem - 1].Subs != NULL)
				MenuPoint[selectItem - 1].Subs();//���ܺ���ִ��
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
	sprintf(str,"1��ɫ%d",1);
	OLED_Show(32,3,(u8*)str);
  TIM_SetCompare4(TIM2,000);//��
	delay_ms(20000);
	TIM_SetCompare4(TIM2,999);//?
	OLED_CLS();
	
	sprintf(str,"1��ɫ%d",1);
	OLED_Show(32,3,(u8*)str);
	TIM_SetCompare3(TIM2,000);//��
	delay_ms(20000);
	TIM_SetCompare3(TIM2,999);//?
	OLED_CLS();
	
	sprintf(str,"1��ɫ%d",1);
	OLED_Show(32,3,(u8*)str);
  TIM_SetCompare2(TIM3,000);//��
	delay_ms(20000);
	TIM_SetCompare2(TIM3,999);//?
	OLED_CLS();
}
void light(int temp)
{
	char str[30];
	if(temp<2500)
	{
	  sprintf(str,"1[-0,25]��ɫ%d",1);
	  OLED_Show(16,6,(u8*)str);
		TIM_SetCompare3(TIM2,000);//��
	}
	if(temp>2500&&temp<3000)
	{
		sprintf(str,"1(25,30]��ɫ%d",1);
		OLED_Show(16,6,(u8*)str);
    TIM_SetCompare2(TIM3,000);//��
	}
	if(temp>3000)
	{
		sprintf(str,"1(30,100]��ɫ%d",1);
		OLED_Show(16,6,(u8*)str);
    TIM_SetCompare4(TIM2,000);//��
	}
}
void Celsius()//�����¶�
{
	int  temp;
	char I[10],C[1],D[10];
	C[0] ='.';
	temp = Get_Temprate ();	
	sprintf(I,"%d",temp/100);//ShowStrֻ�ܽ����ַ���
	sprintf(D,"%d",temp%100);
	OLED_CLS();
	//һ������16��λ
  OLED_ShowCN(32,0,26);//��
	OLED_ShowCN(48,0,25);//��
	OLED_ShowCN(64,0,1);//��
	OLED_ShowCN(80,0,2);//��

  OLED_ShowStr(40,3,I,2);//��������+16 +8
  OLED_ShowStr(56,3,C,2);//С����(����)
  OLED_ShowStr(64,3,D,2);//С������
	
  light(temp);
}

void Fahrenheit()//�����¶�
{ int  temp,i;
	char I[10],C[1],D[10];
	i=16;
	C[0] ='.';
	temp = Get_Temprate ();	
	temp = temp*180+3200;
	sprintf(I,"%d",temp/100);//ShowStrֻ�ܽ����ַ���
	sprintf(D,"%d",temp%100);

	OLED_CLS();
  OLED_ShowCN(32,0,24);//��
	OLED_ShowCN(48,0,25);//��
	OLED_ShowCN(64,0,1); //��
	OLED_ShowCN(80,0,2); //��

  OLED_ShowStr(40,3,I,2);//��������+16 +8
  OLED_ShowStr(56,3,C,2);//С����(����)
  OLED_ShowStr(64,3,D,2);//С������
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
	
	sprintf(T,"��лʹ��1(^O^)%d",1);
	OLED_Show(8,0,(u8*)T);
	
	sprintf(H,"%d �¾ó�",(int)rmydata.number1);
	OLED_Show(16,3,(u8*)H);
	
	sprintf(Y,"%d ������",(int)rmydata.number2);
	OLED_Show(16,6,(u8*)Y);
	
	
}

         
void f_init()//��ʼ������
{
	rmydata.number1 =190414;
	rmydata.number2 =190418;
	rmydata.number3 =190;
	STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)&rmydata,sizeof(rmydata));
}
void f_show()//��ȡ����ʾ
{
	u8 key;
	char str[10];
	OLED_CLS();
	STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)&rmydata,sizeof(rmydata));
	sprintf(str,"ѧ��1:%d",(int)rmydata.number1);
	OLED_Show(16,0,(u8*)str);
	sprintf((char*)str,"ѧ��2:%d",(int)rmydata.number2 );
	OLED_Show(16,2,(u8*)str);
	sprintf((char*)str,"ѧ��3:%d",(int)rmydata.number3 );
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
	u8 ans[3],flg=2,sign=0;//jieshu =1 ʱ���ԶԶ�������в��� 
	int current_length;
	u8 i,key;
	int time=0;
	current_length=rmydata.number3 *1000;
	ans [0] = current_length/10000; //�꼶
	ans [1] = current_length/100%10;//�༶
	ans [2] = current_length%100;   //�༶λ��
	OLED_CLS();
	while(1)
	{
		key=KEY_Scan();
		delay_ms(20);
		if(key!=0)
		{    //�Ұ���
			if(key==1)sign=!sign;
			else if(key==2)//�¼�
			{
				if(sign==0)flg++;
				else if(flg<=2) ans [flg]--;
			}
			else if(key==3)//���
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
		{//.ǰһλ�����·���ʾ^
			if(flg==0)OLED_Show(8*9,2,(u8*)"^");//5
			//.���ĳһλ���·���ʾ��
			else OLED_Show(8*9+8*flg,2,(u8*)"^");
		}
		else if(time<=40){if(sign==0)OLED_Show(0,2,(u8*)"                ");}
		else time=0;
		for(i=0;i<3;i++)
		current_length=ans [0]*10000+ans [1]*100+ans [2];
		sprintf((char*)str,"ѧ��3:%d",(int)current_length);
		OLED_Show(0,0,(u8*)str);
	}
}
#endif