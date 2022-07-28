/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-06 00:55:28
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-07 12:36:04
 * @FilePath: \MDK-ARMd:\desk\ccu6\Core\Inc\ili9325.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#ifndef __ILI9325_H
#define __ILI9325_H

//#ifdef __cplusplus
// extern "C" {
//#endif 

#include "stm32f4xx_hal.h"

#define WINDOW_XADDR_START	0x0050 // Horizontal Start Address Set
#define WINDOW_XADDR_END	0x0051 // Horizontal End Address Set
#define WINDOW_YADDR_START	0x0052 // Vertical Start Address Set
#define WINDOW_YADDR_END	0x0053 // Vertical End Address Set
#define GRAM_XADDR		    0x0020 // GRAM Horizontal Address Set
#define GRAM_YADDR		    0x0021 // GRAM Vertical Address Set
#define GRAMWR 			    0x0022 // memory write
   
/*-----------------------------------------------------------------------
                           液晶端口定义
-----------------------------------------------------------------------*/
#define	TFT_WR	(1<<8)  //写数据控制线		PB11
#define	TFT_RS	(1<<10)  //数据/命令选择端口	PB10
#define	TFT_CS	(1<<12)  //片选端口  	    PB9
#define	TFT_RST	(1<<13)  //硬复位			PB8


#define TFT_RS_SET(x)   x?(GPIOB->BSRR=((1<<10) <<16U)):(GPIOB->BSRR=(1<<10))
#define TFT_CS_SET(x)   x?(GPIOB->BSRR=((1<<12)<<16U)):(GPIOB->BSRR=(1<<12))												     
#define TFT_RST_SET(x)  x?(GPIOC->BSRR=((1<<13)<<16U)):(GPIOC->BSRR=(1<<13))	
#define TFT_WR_SET(x)   x?(GPIOA->BSRR=((1<<8) <<16U)):(GPIOA->BSRR=(1<<8))	
 


//#define	LCD_CS_SET  GPIOB->BSRR=1<<12    //片选端口  		PC9  
//#define	LCD_RS_SET	GPIOB->BSRR=1<<10    //数据/命令 		PC8	   
//#define	LCD_WR_SET	GPIOA->BSRR=1<<8    //写数据			PC7
////#define	LCD_RD_SET	GPIOB->BSRR=1<<6    //读数据			PC6
//								    
//#define	LCD_CS_CLR  GPIOB->BSRR=(1<<9)<<16U     //片选端口  		PC9
//#define	LCD_RS_CLR	GPIOB->BSRR=(1<<8)<<16U     //数据/命令		PC8	   
//#define	LCD_WR_CLR	GPIOA->BSRR=(1<<8)<<16U     //写数据			PC7
#define DATAOUT(x) GPIOA->ODR=(GPIOA->ODR&0xffffff00)|(x&0xff);//定义8位数据操作端口  
 

/*-----------------------------------------------------------------------
                             函数声明
-----------------------------------------------------------------------*/
void ILI9325_Initial(void);
void show_colour_bar (void);
void Write_Cmd_Data(unsigned char x, unsigned int y);
void Write_Cmd(unsigned char DH,unsigned char DL);
void Write_Data(unsigned char DH,unsigned char DL);
void delayms(unsigned int tt);
void show_photo(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1,const unsigned char *pic)  ;
void Show_RGB (unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1,unsigned int Color);
void  Write_Data_U16(unsigned int y);
static void LCD_SetPos(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1);
void ClearScreen(unsigned int bColor);
void LCD_PutChar8x16(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor);
void LCD_PutChar(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor);
void LCD_PutString(unsigned short x, unsigned short y, unsigned char *s, unsigned int fColor, unsigned int bColor);

void LCD_PutChar8x8(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor);
void PutGB1616(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor);





#endif 

