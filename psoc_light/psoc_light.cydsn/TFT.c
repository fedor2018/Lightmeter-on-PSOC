/*
 * TFT.c
 *
 *  Created: 14.10.2013 12:47:54
 *   Author: Ovner
 *
 * My additions: 9.02.2014
 */ 
#include "TFT.h"
#include "fonts.h"

uint16_t MAX_X=0, MAX_Y = 0;
//************************************************************************************
uint16_t constrain(uint16_t a, uint16_t b, uint16_t c)
{
	if (a < b)  { return b; }
	if (c < a)	{ return c;	}
	else return a;
}
//*************************************************************************************
void TFT_SendCMD(uint8_t cmd)
{ D_C_Write(0);   SPIM_WriteTxData(cmd); CyDelayUs(1);}
//*************************************************************************************
void TFT_WriteData(uint8_t Data)
{ D_C_Write(1); SPIM_WriteTxData(Data);CyDelayUs(1);}
//*************************************************************************************
void TFT_SendData(uint16_t Data)
{
	uint8_t data1 = Data>>8;
	uint8_t data2 = Data&0xff;
	TFT_WriteData(data1);
	TFT_WriteData(data2);
}
//*************************************************************************************
void TFT_Init(uint8_t orient)
{
TFT_SendCMD  (0x01);
CyDelay(100);
//************* Start Initial Sequence **********//
//Power control A
TFT_SendCMD  (0xCB);
TFT_WriteData(0x39);
TFT_WriteData(0x2C);
TFT_WriteData(0x00);
TFT_WriteData(0x34);
TFT_WriteData(0x02);

//Power control A
TFT_SendCMD  (0xCF);
TFT_WriteData(0x00);
TFT_WriteData(0XC1);
TFT_WriteData(0X30);

//Driver timing control A
TFT_SendCMD  (0xE8);
TFT_WriteData(0x85);
TFT_WriteData(0x00);
TFT_WriteData(0x78);

//Driver timing control B
TFT_SendCMD  (0xEA);
TFT_WriteData(0x00);
TFT_WriteData(0x00);

//Power on sequence control
TFT_SendCMD(0xED);
TFT_WriteData(0x64);
TFT_WriteData(0x03);
TFT_WriteData(0X12);
TFT_WriteData(0X81);

//Pump ratio control
TFT_SendCMD (0xF7);
TFT_WriteData(0x20);

//Power Control 1
TFT_SendCMD  (0xC0);
TFT_WriteData(0x23);

//Power Control 2
TFT_SendCMD  (0xC1);
TFT_WriteData(0x10);

//VCOM Control 1
TFT_SendCMD(0xC5);
TFT_WriteData(0x2B);
TFT_WriteData(0x2B);

//Memory Access Control
TFT_SetOrientation(orient);

//Frame Rate Control (In Normal Mode/Full Colors)
TFT_SendCMD(0xB1);
TFT_WriteData(0x00);
TFT_WriteData(0x1B);	// 10

//Display Function Control
TFT_SendCMD(0xB6);
TFT_WriteData(0x0A);
TFT_WriteData(0x02);	// A2

//Enable 3G
TFT_SendCMD(0xF2);
TFT_WriteData(0x02);  //off


//COLMOD: Pixel Format Set
TFT_SendCMD(0x3a);
TFT_WriteData(0x05);

//Gamma Set
TFT_SendCMD(0x26);   //Gamma curve 3
TFT_WriteData(0x01);

//Positive Gamma Correction
TFT_SendCMD(0xE0);
TFT_WriteData(0x0F);
TFT_WriteData(0x31);
TFT_WriteData(0x2B);
TFT_WriteData(0x0C);
TFT_WriteData(0x0E);
TFT_WriteData(0x08);
TFT_WriteData(0x4E);
TFT_WriteData(0xF1);
TFT_WriteData(0x37);
TFT_WriteData(0x07);
TFT_WriteData(0x10);
TFT_WriteData(0x03);
TFT_WriteData(0x0E);
TFT_WriteData(0x09);
TFT_WriteData(0x00);

//Negative Gamma Correction
TFT_SendCMD(0XE1);
TFT_WriteData(0x00);
TFT_WriteData(0x0E);
TFT_WriteData(0x14);
TFT_WriteData(0x03);
TFT_WriteData(0x11);
TFT_WriteData(0x07);
TFT_WriteData(0x31);
TFT_WriteData(0xC1);
TFT_WriteData(0x48);
TFT_WriteData(0x08);
TFT_WriteData(0x0F);
TFT_WriteData(0x0C);
TFT_WriteData(0x31);
TFT_WriteData(0x36);
TFT_WriteData(0x0F);
// Sleep Out
TFT_SendCMD(0x11);
CyDelay(120);
//Display On
TFT_SendCMD(0x29);
}
//*************************************************************************************
void TFT_SetCol(uint16_t StartCol,uint16_t EndCol)
{
	TFT_SendCMD(0x2A);                                                      /* Column Command address       */
	TFT_SendData(StartCol);
	TFT_SendData(EndCol);
}
//*************************************************************************************
void TFT_SetPage(uint16_t StartPage,uint16_t EndPage)
{
	TFT_SendCMD(0x2B);                                                      /* Column Command address       */
	TFT_SendData(StartPage);
	TFT_SendData(EndPage);
}
//*************************************************************************************
void TFT_ClearScreen(void)
{
	uint16_t i=0;
	TFT_SetCol(0, MAX_X);
	TFT_SetPage(0, MAX_Y);
	TFT_SendCMD(0x2c);                                                  /* start to write to display ra */
	/* m                            */
	for(i=0; i<38400; i++)
	{
		TFT_WriteData(~0);
		TFT_WriteData(~0);
		TFT_WriteData(~0);
		TFT_WriteData(~0);
	}
}
//*************************************************************************************
void TFT_FillScreen(uint16_t XL, uint16_t XR, uint16_t YU, uint16_t YD, uint16_t color)
{
	unsigned long  XY=0;
	unsigned long i=0;
	color = ~color;
	if(XL > XR)
	{
		XL = XL^XR;
		XR = XL^XR;
		XL = XL^XR;
	}
	if(YU > YD)
	{
		YU = YU^YD;
		YD = YU^YD;
		YU = YU^YD;
	}
	XL = constrain(XL, MIN_X,MAX_X);
	XR = constrain(XR, MIN_X,MAX_X);
	YU = constrain(YU, MIN_Y,MAX_Y);
	YD = constrain(YD, MIN_Y,MAX_Y);

	XY = (XR-XL+1);
	XY = XY*(YD-YU+1);

	TFT_SetCol(XL,XR);
	TFT_SetPage(YU, YD);
	TFT_SendCMD(0x2c);  /* start to write to display ram */

	uint8_t Hcolor = color>>8;
	uint8_t Lcolor = color&0xff;
	for(i=0; i < XY; i++)
	{
		TFT_WriteData(Hcolor);
		TFT_WriteData(Lcolor);
	}

}
//*************************************************************************************
void TFT_SetXY(uint16_t poX, uint16_t poY)
{
	TFT_SetCol(poX, poX);
	TFT_SetPage(poY, poY);
	TFT_SendCMD(0x2c);
}
//*************************************************************************************
void TFT_SetPixel(uint16_t poX, uint16_t poY,uint16_t color)
{
	TFT_SetXY(poX, poY);
	TFT_SendData(~color);
}
//*************************************************************************************
void TFT_FillRectangle(uint16_t poX, uint16_t poY, uint16_t length, uint16_t width, uint16_t color)
{
	TFT_FillScreen(poX, poX+length, poY, poY+width, color);
}
//*************************************************************************************
void  TFT_DrawHorizontalLine( uint16_t poX, uint16_t poY, uint16_t length,uint16_t color)
{
	int i=0;
	TFT_SetCol(poX,poX + length);
	TFT_SetPage(poY,poY);
	TFT_SendCMD(0x2c);
	for(i=0; i<length; i++)
	TFT_SendData(~color);
}
//*************************************************************************************
void TFT_DrawLine( uint16_t x0,uint16_t y0,uint16_t x1, uint16_t y1,uint16_t color)
{
	int x = x1-x0;
	int y = y1-y0;
	int dx = abs(x), sx = x0<x1 ? 1 : -1;
	int dy = -abs(y), sy = y0<y1 ? 1 : -1;
	int err = dx+dy, e2;                                                /* error value e_xy             */
	for (;;){                                                           /* loop                         */
		TFT_SetPixel(x0,y0,color);
		e2 = 2*err;
		if (e2 >= dy) {                                                 /* e_xy+e_x > 0                 */
			if (x0 == x1) break;
			err += dy; x0 += sx;
		}
		if (e2 <= dx) {                                                 /* e_xy+e_y < 0                 */
			if (y0 == y1) break;
			err += dx; y0 += sy;
		}
	}
}
//*************************************************************************************
void TFT_DrawVerticalLine( uint16_t poX, uint16_t poY, uint16_t length,uint16_t color)
{
	int i=0;
	TFT_SetCol(poX,poX);
	TFT_SetPage(poY,poY+length);
	TFT_SendCMD(0x2c);
	for(i=0; i<length; i++)
	TFT_SendData(~color);
}
//*************************************************************************************
void TFT_DrawRectangle(uint16_t poX, uint16_t poY, uint16_t length, uint16_t width,uint16_t color)
{
	TFT_DrawHorizontalLine(poX, poY, length, color);
	TFT_DrawHorizontalLine(poX, poY+width, length, color);
	TFT_DrawVerticalLine(poX, poY, width,color);
	TFT_DrawVerticalLine(poX + length, poY, width,color);
}
//*************************************************************************************
void TFT_DrawCircle(int poX, int poY, int r,uint16_t color)
{
	int x = -r, y = 0, err = 2-2*r, e2;
	do {
		TFT_SetPixel(poX-x, poY+y,color);
		TFT_SetPixel(poX+x, poY+y,color);
		TFT_SetPixel(poX+x, poY-y,color);
		TFT_SetPixel(poX-x, poY-y,color);
		e2 = err;
		if (e2 <= y) {
			err += ++y*2+1;
			if (-x == y && e2 <= x) e2 = 0;
		}
		if (e2 > x) err += ++x*2+1;
	} while (x <= 0);
}
//*************************************************************************************
void TFT_FillCircle(int poX, int poY, int r,uint16_t color)
{
	int x = -r, y = 0, err = 2-2*r, e2;
	do {
		TFT_DrawVerticalLine(poX-x, poY-y, 2*y, color);
		TFT_DrawVerticalLine(poX+x, poY-y, 2*y, color);

		e2 = err;
		if (e2 <= y) {
			err += ++y*2+1;
			if (-x == y && e2 <= x) e2 = 0;
		}
		if (e2 > x) err += ++x*2+1;
	} while (x <= 0);
}
//*************************************************************************************
void TFT_SetOrientation(uint8_t orient)
{
	TFT_SendCMD(0x36);
	switch (orient)
	{
		case 0: TFT_WriteData(0x48);
				break;
		case 1: TFT_WriteData(0x28);
				break;
		case 2: TFT_WriteData(0x88);
				break;
		case 3: TFT_WriteData(0xE8);
				break;
	}
	if (orient == 0 || orient == 2)
	{ MAX_X = 239; MAX_Y = 319;	}
	else
	{ MAX_X = 319;	MAX_Y = 239;}
}
//*************************************************************************************
void TFT_DrawChar( uint8_t ascii, uint16_t poX, uint16_t poY,uint16_t size, uint16_t fgcolor)
{
	int i = 0;   uint8_t f =0 ;
	uint8_t temp=0, k;
	if((ascii>=32)&&(ascii<=255))	{;}
	else	{ascii = '?'-32;}
	
	for (i = 0; i < FONT_X; i++ ) 
	{
		if ((ascii >= 0x20) && (ascii <= 0x7F))
		{
			temp = (Font16x16[ascii-0x20][i]);// temp = (&Font16x16[ascii-0x20][i]);
		}
		else if ( ascii >= 0xC0 )
		{
			temp = (Font16x16[ascii-0x65][i]);//  temp = (&Font16x16[ascii-0x65][i]);+++++++++++++++++++
		}
		k=i / 8;
		for(f =0 ; f < FONT_Y; f++)
		{
			if((temp>>f)&0x01)
			{
				if (size == 0)TFT_SetPixel(poX+i-(k*8), poY+f+(k*8),fgcolor);
				else TFT_FillRectangle(poX+i*size-(k*8)*size, poY+f*size+(k*8)*size, size, size, fgcolor);
			}
		}
	}
}

//*************************************************************************************
void TFT_DrawString(char *string,uint16_t poX, uint16_t poY, uint16_t size,uint16_t fgcolor)
{
	while(*string)
	{
		if((poX + FONT_SPACE) > MAX_X)		{poX = 1; poY = poY + FONT_X*size;}
		
		TFT_DrawChar(*string, poX, poY, size, fgcolor);
		if (size > 0) poX += FONT_SPACE*size;
		else poX += FONT_SPACE;
		string++;
	}
}

//************************************************************************************++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void TFT_FillBitmap(uint16_t XL, uint16_t XR, uint16_t YU, uint16_t YD, unsigned short *Bitmap)
{
	unsigned long  XY=0;
	unsigned long i=0;
	XY = (XR-XL+1);
	XY = XY*(YD-YU+1);

	TFT_SetCol(XL,XR);
	TFT_SetPage(YU, YD);
	TFT_SendCMD(0x2c);                     /* start to write to display ra */

	for(i=0; i < XY; i++)
	{										 //color[i] =( ~color[i+1]);	
	uint8_t Hcolor = (~Bitmap[i])>>8;
	uint8_t Lcolor = (~Bitmap[i])&0xff;	
		TFT_WriteData(Hcolor);
		TFT_WriteData(Lcolor);
	}
}

/*

void Read_SD_Pictute(uint16_t XL, uint16_t XR, uint16_t YU, uint16_t YD, unsigned short *FileName)
{
char  fp;
long  XY=0, i=0;
XY = (XR-XL+1);
XY = 2*XY*(YD-YU)+1;
TFT_SetCol(XL,XR);
TFT_SetPage(YU, YD);
TFT_SendCMD(0x2c);     // start to write to display ra 
fp = SDCard_fopen((uint8 *)FileName, (uint8 *)"r");

 while(! SDCard_feof(fp))           // Check for end of input file
{
extern uint8   SDCard_SectBuf1[];
extern uint8   SDCard_SectBuf2[];

  SDCard_ReadFileSect(fp);    // Read sector

	for(i=0; i < 256 ; i++)
		{	if(XY<0)  break;
		TFT_WriteData(~SDCard_SectBuf1[i]); XY--; }

	for(i=0; i < 256; i++)
		{ 	if(XY<0)  break;
		TFT_WriteData(~SDCard_SectBuf2[i]); XY--; }
	
SDCard_NextSect(fp);               // Advance to next read sector
}
	SDCard_fclose(fp); 
}

*/

//----------------------------------------------------------------------------------
void TFT_Graf(uint16_t XL, uint16_t YU, uint16_t YD, char  Ydata , char last)
{
	unsigned long  XY=0;
	unsigned long i=0;
//	volatile char last;
	//XY = (XR-XL+1);
	XY = YD-YU+1;

	TFT_SetCol(XL,XL);
	TFT_SetPage(YU, YD);
	TFT_SendCMD(0x2c);                     /* start to write to display ra */

	for(i=0; i < XY; i++)
	{										 //color[i] =( ~color[i+1]);	
   //  uint8_t Hcolor = 255*( (i<last )    );
	//uint8_t Hcolor = ~(255*( ((i>=last)&(i<=Ydata))|((i<=last)&(i>=Ydata))  ) );
 uint8_t Hcolor =  (255*( ((i<last)|(i>Ydata))&((i>last)|(i<Ydata))  ) );
	//uint8_t Hcolor = 255*(Ydata!=i);//(~Bitmap[i])>>8;
	uint8_t Lcolor = 128;//(~Bitmap[i])&0xff;	
		TFT_WriteData(Hcolor);
		TFT_WriteData(Lcolor);
		
		
	}
last =Ydata;

}
