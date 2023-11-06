#ifndef __OLED_I2C_H
#define	__OLED_I2C_H

#include "stm32f10x.h"

#define OLED_ADDRESS	0x78 //通过调整0R电阻,屏可以0x78和0x7A两个地址 -- 默认0x78
extern char ans[4];
void I2C_Configuration(void);
void I2C_WriteByte(uint8_t addr,uint8_t data);
void WriteCmd(unsigned char I2C_Command);
void WriteDat(unsigned char I2C_Data);
void OLED_Init(void);
void OLED_SetPos(unsigned char x, unsigned char y);
void OLED_Fill(unsigned char fill_Data);
void OLED_CLS(void);
void OLED_ON(void);
void OLED_OFF(void);
void OLED_ShowStr(unsigned char x, unsigned char y,char ch[], unsigned char TextSize);
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);
//void OLED_ShowPicture(u8 x0,u8 y0,u8 x1,u8 y1,const unsigned char BMP[]);
//void OLED_ShowPicture(u8 x0,u8 y0,u8 x1,u8 y1,const unsigned char BMP[]);
//void OLED_ShowPicture(u8 x0,u8 y0,u8 x1,u8 y1,unsigned char BMP[]);
void OLED_ShowoneStr(unsigned char x, unsigned char y,char ch);
u8 OLED_findoneCN(u8 ch1,u8 ch2);
void OLED_Show(unsigned char x, unsigned char y,u8 ch[]);
void OLED_ShowStr1(unsigned char x, unsigned char y,  char ch[], unsigned char TextSize);
//
void OLED_ShowStrD(unsigned char x, unsigned char y,char ch[], unsigned char TextSize);


//void OLED_ShowCN2(unsigned char x, unsigned char y,unsigned char n);
#endif
