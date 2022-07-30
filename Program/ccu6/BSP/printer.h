/*** 
 * @Author: liubotao
 * @Date: 2022-07-08 23:51:58
 * @LastEditors: liubotao
 * @LastEditTime: 2022-07-28 16:37:23
 * @FilePath: \ccu6\BSP\printer.h
 * @Description: 
 * @
 */
#ifndef _PRINTER_H
#define _PRINTER_H
#include "main.h"

#define SCREEN_X_NUM 384
#define SCREEN_Y_NUM 50

#define SCREEN_X_NUM_8 (SCREEN_X_NUM / 8)//48



#define PRINTER_DI_Pin   GPIO_PIN_1
#define PRINTER_CLK_Pin  GPIO_PIN_2
#define PRINTER_LAT_Pin  GPIO_PIN_10


#define PRINTER_DI( a )   a?(GPIOB->BSRR=(PRINTER_DI_Pin )):(GPIOB->BSRR=((PRINTER_DI_Pin )<<16U))
#define PRINTER_CLK( a )  a?(GPIOB->BSRR=(PRINTER_CLK_Pin)):(GPIOB->BSRR=((PRINTER_CLK_Pin)<<16U))												     
#define PRINTER_LAT( a )  a?(GPIOB->BSRR=(PRINTER_LAT_Pin)):(GPIOB->BSRR=((PRINTER_LAT_Pin)<<16U))	

#define GATING_1_PIN  GPIO_PIN_4
#define GATING_2_PIN  GPIO_PIN_5
#define GATING_3_PIN  GPIO_PIN_6
#define GATING_4_PIN  GPIO_PIN_7
#define GATING_5_PIN  GPIO_PIN_8
#define GATING_6_PIN  GPIO_PIN_9


#define GATING_1(x) x?(GPIOB->BSRR=(GATING_1_PIN)):(GPIOB->BSRR=((GATING_1_PIN)<<16U))
#define GATING_2(x) x?(GPIOB->BSRR=(GATING_2_PIN)):(GPIOB->BSRR=((GATING_2_PIN)<<16U))
#define GATING_3(x) x?(GPIOB->BSRR=(GATING_3_PIN)):(GPIOB->BSRR=((GATING_3_PIN)<<16U))
#define GATING_4(x) x?(GPIOB->BSRR=(GATING_4_PIN)):(GPIOB->BSRR=((GATING_4_PIN)<<16U))
#define GATING_5(x) x?(GPIOB->BSRR=(GATING_5_PIN)):(GPIOB->BSRR=((GATING_5_PIN)<<16U))
#define GATING_6(x) x?(GPIOB->BSRR=(GATING_6_PIN)):(GPIOB->BSRR=((GATING_6_PIN)<<16U))


#define GATING_ALL(x) x?(              \
                            GATING_1(1),\
                            GATING_2(1),\
                            GATING_3(1),\
                            GATING_4(1),\
                            GATING_5(1),\
                            GATING_6(1)\
                            ):(        \
                            GATING_1(0),\
                            GATING_2(0),\
                            GATING_3(0),\
                            GATING_4(0),\
                            GATING_5(0),\
                            GATING_6(0)\
                            )


#define GATING_ODD(x) x?(              \
                            GATING_1(1),\
                            GATING_2(0),\
                            GATING_3(0),\
                            GATING_4(0),\
                            GATING_5(0),\
                            GATING_6(1)\
                            ):(        \
                            GATING_1(0),\
                            GATING_2(0),\
                            GATING_3(0),\
                            GATING_4(0),\
                            GATING_5(0),\
                            GATING_6(0)\
                            )


#define GATING_CBB(x) x?(              \
                            GATING_1(0),\
                            GATING_2(0),\
                            GATING_3(1),\
                            GATING_4(1),\
                            GATING_5(0),\
                            GATING_6(0)\
                            ):(        \
                            GATING_1(0),\
                            GATING_2(0),\
                            GATING_3(0),\
                            GATING_4(0),\
                            GATING_5(0),\
                            GATING_6(0)\
                            )
							

#define GATING_EVEN(x) x?(              \
                            GATING_1(0),\
                            GATING_2(1),\
                            GATING_3(0),\
                            GATING_4(0),\
                            GATING_5(1),\
                            GATING_6(0)\
                            ):(        \
                            GATING_1(0),\
                            GATING_2(0),\
                            GATING_3(0),\
                            GATING_4(0),\
                            GATING_5(0),\
                            GATING_6(0)\
                            )






// #define TFT_RS_SET(x)   x?(GPIOB->BSRR=((1<<10) <<16U)):(GPIOB->BSRR=(1<<10))
// #define TFT_CS_SET(x)   x?(GPIOB->BSRR=((1<<12)<<16U)):(GPIOB->BSRR=(1<<12))												     
// #define TFT_RST_SET(x)  x?(GPIOC->BSRR=((1<<13)<<16U)):(GPIOC->BSRR=(1<<13))	
// #define TFT_WR_SET(x)   x?(GPIOA->BSRR=((1<<8) <<16U)):(GPIOA->BSRR=(1<<8))	

#define black 1
#define white 0



void printer_init(void);
void show_pixel_Buffer(uint16_t x, uint16_t y, uint8_t color);
void show_refresh_Buffer(void);
static int printer_write_line(unsigned char *p);
void OLED_ShowchineseChar_buffer(uint8_t x, uint8_t y, uint8_t *buffer);
void OLED_ShowChar_buffer(uint16_t x, uint16_t y, uint8_t chr);
//static int printer_write_line(unsigned char p[SCREEN_Y_NUM][SCREEN_X_NUM_8]);
void show_rect_Buffer(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void show_line_Buffer(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void show_circle_Buffer(uint8_t x0, uint8_t y0, uint8_t r);
#define bsp_delay_us_1(  )do{\
__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
__NOP();__NOP();__NOP();__NOP();\
}while(0)

#endif
