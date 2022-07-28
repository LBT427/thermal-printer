#include "ili9325.h"

/*-----------------------------------------------------------------------
                         清屏函数
-----------------------------------------------------------------------*/
void ClearScreen(unsigned int bColor)
{
 unsigned int i,j;
 LCD_SetPos(0,240,0,320);//320x240
 for (i=0;i<320;i++)
	{
	
	   for (j=0;j<240;j++)
	       Write_Data_U16(bColor);

	}
}



/*-----------------------------------------------------------------------
                         显示RGB颜色
-----------------------------------------------------------------------*/
void Show_RGB (unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1,unsigned int Color)
{
	unsigned int i,j;
	LCD_SetPos(x0,x1,y0,y1);
	for (i=y0;i<=y1;i++)
	{
	   for (j=x0;j<=x1;j++)
	       Write_Data_U16(Color);

	}

}
/*-----------------------------------------------------------------------
                              显示彩条
-----------------------------------------------------------------------*/
void show_colour_bar (void)

{
	int V,H;
	LCD_SetPos(0,240,0,320);//320x240

	for(H=0;H<240;H++)
	{
		for(V=0;V<40;V++)
		Write_Data(0xf8,0x00);
	}

	for(H=0;H<240;H++)
	{
		for(V=40;V<80;V++)
		Write_Data(0x07,0xe0);
	}

	for(H=0;H<240;H++)
	{
		for(V=80;V<120;V++)
		Write_Data(0x00,0x1f);
	}

	for(H=0;H<240;H++)
	{
		for(V=120;V<160;V++)
		Write_Data(0xff,0xe0);
	}

	for(H=0;H<240;H++)
	{
		for(V=160;V<200;V++)
		Write_Data(0xf8,0x1f);
	}

	for(H=0;H<240;H++)
	{
		for(V=200;V<240;V++)
		Write_Data(0x07,0xff);
	}

	for(H=0;H<240;H++)
	{
		for(V=240;V<280;V++)
		Write_Data(0xff,0xff);
	}

	for(H=0;H<240;H++)
	{
		for(V=280;V<320;V++)
		Write_Data(0x00,0x00);
	}

}
/*-----------------------------------------------------------------------
                            显示图片
-----------------------------------------------------------------------*/

void show_photo(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1,const unsigned char *pic)
{
	unsigned int j;
	unsigned int i;
	//unsigned long s=0;

	LCD_SetPos(x0,x1-1,y0,y1-1);//定义坐标和显示范围

	for (i=0;i<y1-y0;i++)
	{
    	for (j=0;j<x1-x0;j++)
		Write_Data(*(pic++-1),*(pic++-1));	
	}

}

/*-----------------------------------------------------------------------
                            写指令和数据	  8位总线
-----------------------------------------------------------------------*/
void  Write_Cmd_Data (unsigned char x,unsigned int y)
{
	unsigned char m,n;
	m=y>>8;
	n=y;
	Write_Cmd(0x00,x);
	Write_Data(m,n);

}

/*-----------------------------------------------------------------------
                            写16位数据
-----------------------------------------------------------------------*/
void  Write_Data_U16(unsigned int y)
{
	unsigned char m,n;
	m=y>>8;
	n=y;
	Write_Data(m,n);

}
/*-----------------------------------------------------------------------
                            写指令	  8位总线
-----------------------------------------------------------------------*/

void Write_Cmd(unsigned char DH,unsigned char DL)
{
	TFT_CS_SET(0); 
	TFT_RS_SET(0);

	DATAOUT(DH);
	TFT_WR_SET(0); 
	TFT_WR_SET(1);

	DATAOUT(DL);
	TFT_WR_SET(0); 
	TFT_WR_SET(1);

	TFT_CS_SET(1); 
}

/*-----------------------------------------------------------------------
                            写数据	  8位总线
-----------------------------------------------------------------------*/

void Write_Data(unsigned char DH,unsigned char DL)
{
 
  
	TFT_CS_SET(0); 
	TFT_RS_SET(1);

	DATAOUT(DH);
	TFT_WR_SET(0); 
	TFT_WR_SET(1);

	DATAOUT(DL);
	TFT_WR_SET(0); 
	TFT_WR_SET(1);

	TFT_CS_SET(1); 
}



/*-----------------------------------------------------------------------
                          系统时钟设置
-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------
                          液晶初始化
-----------------------------------------------------------------------*/

void ILI9325_Initial(void)
{ 
	TFT_CS_SET(1); 
 	TFT_RST_SET(1);
	TFT_RS_SET(1);
	TFT_WR_SET(1);
	HAL_Delay(500);
	
	
	TFT_RST_SET(0);
	HAL_Delay(200);
	TFT_RST_SET(1);

 Write_Cmd_Data(0x0001,0x0100); 
 Write_Cmd_Data(0x0002,0x0700); 
 Write_Cmd_Data(0x0003,0x1030); 
 Write_Cmd_Data(0x0004,0x0000); 
 Write_Cmd_Data(0x0008,0x0207);  
 Write_Cmd_Data(0x0009,0x0000);
 Write_Cmd_Data(0x000A,0x0000); 
 Write_Cmd_Data(0x000C,0x0000); 
 Write_Cmd_Data(0x000D,0x0000);
 Write_Cmd_Data(0x000F,0x0000);
//power on sequence VGHVGL
 Write_Cmd_Data(0x0010,0x0000);   
 Write_Cmd_Data(0x0011,0x0007);  
 Write_Cmd_Data(0x0012,0x0000);  
 Write_Cmd_Data(0x0013,0x0000); 
//vgh 
 Write_Cmd_Data(0x0010,0x1290);   
 Write_Cmd_Data(0x0011,0x0227);
 //HAL_Delay(100);
 //vregiout 
 Write_Cmd_Data(0x0012,0x001d); //0x001b
 //HAL_Delay(100); 
 //vom amplitude
 Write_Cmd_Data(0x0013,0x1500);
 //HAL_Delay(100); 
 //vom H
 Write_Cmd_Data(0x0029,0x0018); 
 Write_Cmd_Data(0x002B,0x000D); 

//gamma
 Write_Cmd_Data(0x0030,0x0004);
 Write_Cmd_Data(0x0031,0x0307);
 Write_Cmd_Data(0x0032,0x0002);// 0006
 Write_Cmd_Data(0x0035,0x0206);
 Write_Cmd_Data(0x0036,0x0408);
 Write_Cmd_Data(0x0037,0x0507); 
 Write_Cmd_Data(0x0038,0x0204);//0200
 Write_Cmd_Data(0x0039,0x0707); 
 Write_Cmd_Data(0x003C,0x0405);// 0504
 Write_Cmd_Data(0x003D,0x0F02); 
 //ram
 Write_Cmd_Data(0x0050,0x0000); 
 Write_Cmd_Data(0x0051,0x00EF);
 Write_Cmd_Data(0x0052,0x0000); 
 Write_Cmd_Data(0x0053,0x013F);  
 Write_Cmd_Data(0x0060,0xA700); 
 Write_Cmd_Data(0x0061,0x0001); 
 Write_Cmd_Data(0x006A,0x0000); 
 //
 Write_Cmd_Data(0x0080,0x0000); 
 Write_Cmd_Data(0x0081,0x0000); 
 Write_Cmd_Data(0x0082,0x0000); 
 Write_Cmd_Data(0x0083,0x0000); 
 Write_Cmd_Data(0x0084,0x0000); 
 Write_Cmd_Data(0x0085,0x0000); 
 //
 Write_Cmd_Data(0x0090,0x0010); 
 Write_Cmd_Data(0x0092,0x0600); 
 Write_Cmd_Data(0x0093,0x0003); 
 Write_Cmd_Data(0x0095,0x0110); 
 Write_Cmd_Data(0x0097,0x0000); 
 Write_Cmd_Data(0x0098,0x0000);
 Write_Cmd_Data(0x0007,0x0133);
		
}
/*-----------------------------------------------------------------------
                        设置坐标点
-----------------------------------------------------------------------*/
static void LCD_SetPos(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1)
{
  Write_Cmd_Data(WINDOW_XADDR_START,x0);
  Write_Cmd_Data(WINDOW_XADDR_END,x1);
  Write_Cmd_Data(WINDOW_YADDR_START,y0);
  Write_Cmd_Data(WINDOW_YADDR_END,y1);
  Write_Cmd_Data(GRAM_XADDR,x0);
  Write_Cmd_Data(GRAM_YADDR,y0);
  Write_Cmd (0x00,0x22);
}
