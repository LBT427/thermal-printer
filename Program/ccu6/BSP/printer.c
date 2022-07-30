/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-08 23:51:52
 * @LastEditors: liubotao
 * @LastEditTime: 2022-07-29 01:05:05
 * @FilePath: \ccu6\BSP\printer.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <string.h>
#include "printer.h"
#include "motor.h"
#include "font.h"
//#include "bsp.h"
uint8_t ff[48];
unsigned char ScreenBuffer[SCREEN_Y_NUM][SCREEN_X_NUM_8];



void printer_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    // GPIO初始化
    GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10|GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10| GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_15, GPIO_PIN_RESET);
	memset(ff,0xff,48);
	GATING_ALL(0);
}

//画点

//点数除以8 =所在 x
//
void show_pixel_Buffer(uint16_t x, uint16_t y, uint8_t color)
{
    if (x >= SCREEN_X_NUM || y >= SCREEN_Y_NUM)
    {
        return;
    }
    if (color)
    ScreenBuffer[y][x / 8] |= 1 << (7-(x % 8 ));//每行有384个点
    else
    ScreenBuffer[y][x / 8] &= ~(1 << (7-(x % 8)));

}
// //打印机画点函数
// void printer_show_pixel(uint16_t x, uint16_t y, uint8_t color)
// {
//     if (x >= SCREEN_X_NUM || y >= SCREEN_Y_NUM)
//     {
//         return;
//     }
//     if (color)
//     ScreenBuffer[y][x / 8] |= 1 << (x % 8 );//每行有384个点
//     else
//     ScreenBuffer[y][x / 8] &= ~(1 << (x % 8));
// }

//画线
void show_line_Buffer(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{

    int x, y;
    int dx, dy;
    int stepx, stepy;//步进值
    int fraction;
    if (x1 > x2)
    {
        x = x2;
        y = y2;
        dx = x1 - x2;
        dy = y1 - y2;
    }
    else
    {
        x = x1;
        y = y1;
        dx = x2 - x1;
        dy = y2 - y1;
    }
    if (dx == 0)
    {
        for (y = y; y <= y2; y++)
        {
            show_pixel_Buffer(x, y,1);
        }
        return;
    }
    if (dy == 0)
    {
        for (x = x; x <= x2; x++)
        {
            show_pixel_Buffer(x, y,1);
        }
        return;
    }
    stepx = 1;
    if (dx < 0)
    {
        dx = -dx;
        stepx = -1;
    }
    stepy = 1;
    if (dy < 0)
    {
        dy = -dy;
        stepy = -1;
    }
    fraction = dx * 2;
    for (x = x; x != x2; x += stepx)
    {
        fraction += dy * 2;
        if (fraction >= dx)
        {
            y += stepy;
            fraction -= dx;
        }
        show_pixel_Buffer(x, y,1);
    }
}
//画矩形
void show_rect_Buffer(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    int x, y;
    if (x1 > x2)
    {
        x = x2;
    }
    else
    {
        x = x1;
    }
    if (y1 > y2)
    {
        y = y2;
    }
    else
    {
        y = y1;
    }
    for (; x <= x2; x++)
    {
        show_pixel_Buffer(x, y1,1);
        show_pixel_Buffer(x, y2,1);
    }
    for (; y <= y2; y++)
    {
        show_pixel_Buffer(x1, y,1);
        show_pixel_Buffer(x2, y,1);
    }
}

 //画圆
 void show_circle_Buffer(uint8_t x0, uint8_t y0, uint8_t r)
 {
     int a, b;
     int di;
     a = 0;
     b = r;
     di = 3 - (r << 1);
     while (a <= b)
     {
         show_pixel_Buffer(x0 + a, y0 - b,1);
         show_pixel_Buffer(x0 - a, y0 - b,1);
         show_pixel_Buffer(x0 + a, y0 + b,1);
         show_pixel_Buffer(x0 - a, y0 + b,1);
         show_pixel_Buffer(x0 + b, y0 - a,1);
         show_pixel_Buffer(x0 - b, y0 - a,1);
         show_pixel_Buffer(x0 + b, y0 + a,1);
         show_pixel_Buffer(x0 - b, y0 + a,1);
         if (di < 0)
         {
             di += 4 * a + 6;
         }
         else
         {
             di += 10 + 4 * (a - b);
             b--;
         }
         a++;
     }
 }
// //画圆弧
// void show_arc_Buffer(uint8_t x0, uint8_t y0, uint8_t r, uint8_t start_angle, uint8_t end_angle)
// {
//     int a, b;
//     int di;
//     a = 0;
//     b = r;
//     di = 3 - (r << 1);
//     while (a <= b)
//     {
//         if (start_angle <= end_angle)
//         {
//             if (a * 180 / 3.1415926 < start_angle || a * 180 / 3.1415926 > end_angle)
//             {
//                 show_pixel_Buffer(x0 + a, y0 - b,1);
//                 show_pixel_Buffer(x0 - a, y0 - b,1);
//                 show_pixel_Buffer(x0 + a, y0 + b,1);
//                 show_pixel_Buffer(x0 - a, y0 + b,1);
//                 show_pixel_Buffer(x0 + b, y0 - a,1);
//                 show_pixel_Buffer(x0 - b, y0 - a,1);
//                 show_pixel_Buffer(x0 + b, y0 + a,1);
//                 show_pixel_Buffer(x0 - b, y0 + a,1);
//             }
//         }
//         else
//         {
//             if (a * 180 / 3.1415926 < end_angle && a * 180 / 3.1415926 > start_angle)
//             {
//                 show_pixel_Buffer(x0 + a, y0 - b,1);
//                 show_pixel_Buffer(x0 - a, y0 - b,1);
//                 show_pixel_Buffer(x0 + a, y0 + b,1);
//                 show_pixel_Buffer(x0 - a, y0 + b,1);
//                 show_pixel_Buffer(x0 + b, y0 - a,1);
//                 show_pixel_Buffer(x0 - b, y0 - a,1);
//                 show_pixel_Buffer(x0 + b, y0 + a,1);
//                 show_pixel_Buffer(x0 -
//                                     b, y0 + a,1);
//             }
//         }
//         if (di < 0)
//         {
//             di += 4 * a + 6;
//         }
//         else
//         {
//             di += 10 + 4 * (a - b);
//             b--;
//         }
//         a++;
//     }
// }


// //画字符串
// void show_string_Buffer_16(uint8_t x, uint8_t y, uint8_t *str)
// {
//     uint8_t i, j;
//     uint8_t temp;
//     for (i = 0; str[i] != '\0'; i++)
//     {
//         temp = str[i] - ' ';
//         for (j = 0; j < 16; j++)
//         {
//             if (asc16[temp][j] == 1)
//             {
//                 show_pixel_Buffer(x + j, y + i,1);
//             }
//         }
//     }
// }
// //画字符串
// void show_string_Buffer_8(uint8_t x, uint8_t y, uint8_t *str)
// {
//     uint8_t i, j;
//     uint8_t temp;
//     for (i = 0; str[i] != '\0'; i++)
//     {
//         temp = str[i] - ' ';
//         for (j = 0; j < 8; j++)
//         {
//             if (asc8[temp][j] == 1)
//             {
//                 show_pixel_Buffer(x + j, y + i,1);
//             }
//         }
//     }
// }



/*******************************************************************************
 函 数 名         : void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t Char_Size)
 函数功能         : 显示一个字符
 输    入         : x  坐标 y 坐标 *chr 字符串  Char_Size 字体大小
 输    出         : 无
 说    明         :  x:0~127 y:0~63
*******************************************************************************/
void OLED_ShowChar_buffer(uint16_t x, uint16_t y, uint8_t chr)
{
    unsigned char c = 0;
    c = chr - ' '; //得到偏移后的值
    if (x > SCREEN_X_NUM - 1)
        x = 0;
    // for (i = 0; i < 8; i++)
    // WriteByteBuffer(y, x+i, F8X16[c * 16 + i]);
    // for (i = 0; i < 8; i++)
    // WriteByteBuffer(y+1, x+i, F8X16[c * 16 + i + 8]);

    for (unsigned char i = 0; i < 16; i++)
    {
        ScreenBuffer[y + i][x] = F8X16[c * 16 + i];
        // ScreenBuffer[y+i][x+1] = buffer[i+1];
    }
}

/*******************************************************************************
 函 数 名         : void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t Char_Size)
 函数功能         : 显示一个中文字符
 输    入         : x  坐标 y 坐标 *chr 字符串  Char_Size 字体大小
 输    出         : 无
 说    明         :  x:0~127 y:0~63
*******************************************************************************/
void OLED_ShowchineseChar_buffer(uint8_t x, uint8_t y, uint8_t *buffer)
{
    unsigned char yNum=0;
        for (unsigned char i = 0; i < 32; i++)
        {
        //   ScreenBuffer[yNum++][x] = buffer[i];
        //   ScreenBuffer[yNum++][x+1] = buffer[i+1];
          if(i%2==0)ScreenBuffer[yNum][x] = buffer[i];
			
          else ScreenBuffer[yNum][x+1] = buffer[i];

          yNum++;
        }

}








unsigned char p[48];
//刷新屏幕
void show_refresh_Buffer(void)
{
	//int num =0;
        //供电使能
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);

    for (uint16_t i = 0; i < SCREEN_Y_NUM; i++)
    {
		
//		
//			for (int j=0;j<SCREEN_X_NUM_8;j++)
//			{
//			p[j]=ScreenBuffer[i][j];
//				
//			}
//			
		
		printer_write_line(*(ScreenBuffer+i));
        //数据写入
       // printer_write_line(ff);
		//printer_write_line(ff+i);

        //控制选通
		GATING_1(1);
		HAL_Delay(10);
		GATING_1(0);
		//HAL_Delay(10);
		
		GATING_2(1);
		HAL_Delay(10);
		GATING_2(0);
		//HAL_Delay(10);
		
		GATING_3(1);
		HAL_Delay(10);
		GATING_3(0);
		//HAL_Delay(10);
		
		GATING_4(1);
		HAL_Delay(10);
		GATING_4(0);
		//HAL_Delay(4);
		
		GATING_5(1);
		HAL_Delay(10);
		GATING_5(0);
		//HAL_Delay(4);
		
		GATING_6(1);
		HAL_Delay(10);
		GATING_6(0);
		//HAL_Delay(4);
		
			//memset(p,0,48);

        //GATING_ODD(0);
       // HAL_Delay(2);
       // GATING_ODD(1);
		// HAL_Delay(10);
//        GATING_EVEN(1);
//        HAL_Delay(10);
//        GATING_EVEN(0);
//		HAL_Delay(10);
//		GATING_CBB(1);
//        HAL_Delay(10);
//        GATING_CBB(0);
//		HAL_Delay(10);
		
        //GATING_ALL(1);
        //电机运动
		//HAL_Delay(50);
		//HAL_Delay(10);
        motor_turn_now(advance,2, 25); //电机在主函数中阻塞转动
    }

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
}



//void write666()





void WriteByteBuffer(int page, int x, unsigned char byte)//刷新数据到缓冲区
{

  ScreenBuffer[page][x] = byte;
}


//打印机每行有384个点，点距为0.125mm。每个点1bite数据表示，所以每行48byte。
static int printer_write_line(unsigned char *p)
{
 //int ret = 0;
 unsigned char data;
 //int *tmp = (int *)p;
 
 for(uint8_t j=0; j<48; j++){
     data = p[j];
     for(uint8_t i=0; i<8; i++)
     {
         if((data&0x80) == 0)  PRINTER_DI(0);//gpio_set_value(IUNIN_GPIO_LPT_DIN, 0);
         else PRINTER_DI(1);//gpio_set_value(IUNIN_GPIO_LPT_DIN, 1);
        
         data = data << 1;
		// HAL_Delay(1);		 
         bsp_delay_us_1();//ndelay(twCLK_DELAY);
         PRINTER_CLK(1);//gpio_set_value(IUNIN_GPIO_LPT_CLK, 1);
         bsp_delay_us_1();//ndelay(twCLK_DELAY);
         PRINTER_CLK(0);//gpio_set_value(IUNIN_GPIO_LPT_CLK, 0);
     }
 }
 PRINTER_LAT(0);//gpio_set_value(IUNIN_GPIO_LPT_LAT, 0);
 bsp_delay_us_1();//ndelay(twLAT_DELAY);
 PRINTER_LAT(1);//gpio_set_value(IUNIN_GPIO_LPT_LAT, 1);
 bsp_delay_us_1();//ndelay(setup_LAT_DELAY);  
 return 0;
}
