
/* ========================================
 *
 The following firmware was developed by Cypress Semiconductor
This work is licensed under a Creative Commons Attribution 3.0 Unported License.
http://creativecommons.org/licenses/by/3.0/deed.en_US
You are free to:
-To Share — to copy, distribute and transmit the work 
-To Remix — to adapt the work 
-To make commercial use of the work
* ========================================
*/

/*
  ColorLCDShield.h - Arduino Library to control a Nokia 6100 LCD, 
  specifically that found on SparkFun's Color LCD Shield.
  This code should work for both Epson and Phillips display drivers 
  normally found on the Color LCD Shield.
	
  License: CC BY-SA 3.0: Creative Commons Share-alike 3.0. Feel free 
  to use and abuse this code however you'd like. If you find it useful
  please attribute, and SHARE-ALIKE!
  
  This is based on code by Mark Sproul, and Peter Davenport.
*/
//The LCD library is taken from the SparkFun website

#include <cytypes.h>

#define PHILLIPS	0
#define PHILIPS     0
#define EPSON		1

//********************************************************************
//
//					LCD Dimension Definitions
//
//********************************************************************
#define ROW_LENGTH	132
#define COL_HEIGHT	132
#define ENDPAGE     132
#define ENDCOL      130

//********************************************************************
//
//					EPSON Controller Definitions
//
//********************************************************************
#define DISON       0xAF	// Display on
#define DISOFF      0xAE	// Display off
#define DISNOR      0xA6	// Normal display
#define DISINV      0xA7	// Inverse display
#define SLPIN       0x95	// Sleep in
#define SLPOUT      0x94	// Sleep out
#define COMSCN      0xBB	// Common scan direction
#define DISCTL      0xCA	// Display control
#define PASET       0x75	// Page address set
#define CASET       0x15	// Column address set
#define DATCTL      0xBC	// Data scan direction, etc.
#define RGBSET8     0xCE	// 256-color position set
#define RAMWR       0x5C	// Writing to memory
#define RAMRD       0x5D	// Reading from memory
#define PTLIN       0xA8	// Partial display in
#define PTLOUT      0xA9	// Partial display out
#define RMWIN       0xE0	// Read and modify write
#define RMWOUT      0xEE	// End
#define ASCSET      0xAA	// Area scroll set
#define SCSTART     0xAB	// Scroll start set
#define OSCON       0xD1	// Internal oscillation on
#define OSCOFF      0xD2	// Internal osciallation off
#define PWRCTR      0x20	// Power control
#define VOLCTR      0x81	// Electronic volume control
#define VOLUP       0xD6	// Increment electronic control by 1
#define VOLDOWN     0xD7	// Decrement electronic control by 1
#define TMPGRD      0x82	// Temperature gradient set
#define EPCTIN      0xCD	// Control EEPROM
#define EPCOUT      0xCC	// Cancel EEPROM control
#define EPMWR       0xFC	// Write into EEPROM
#define EPMRD       0xFD	// Read from EEPROM
#define EPSRRD1     0x7C	// Read register 1
#define EPSRRD2     0x7D	// Read register 2
#define NOP         0x25	// No op

//********************************************************************
//
//			PHILLIPS Controller Definitions
//
//********************************************************************
//LCD Commands
#define	NOPP		0x00	// No operation
#define	BSTRON		0x03	// Booster voltage on
#define SLEEPIN     0x10	// Sleep in
#define	SLEEPOUT	0x11	// Sleep out
#define	NORON		0x13	// Normal display mode on
#define	INVOFF		0x20	// Display inversion off
#define INVON      	0x21	// Display inversion on
#define	SETCON		0x25	// Set contrast
#define DISPOFF     0x28	// Display off
#define DISPON      0x29	// Display on
#define CASETP      0x2A	// Column address set
#define PASETP      0x2B	// Page address set
#define RAMWRP      0x2C	// Memory write
#define RGBSET	    0x2D	// Color set
#define	MADCTL		0x36	// Memory data access control
#define	COLMOD		0x3A	// Interface pixel format
#define DISCTR      0xB9	// Super frame inversion
#define	EC			0xC0	// Internal or external oscillator

//*******************************************************
//				12-Bit Color Definitions
//*******************************************************
#define BLACK		0x000
#define NAVY 		0x008
#define BLUE		0x00F
#define TEAL 		0x088
#define EMERALD		0x0C5
#define	GREEN		0x0F0
#define CYAN		0x0FF
#define SLATE 		0x244
#define INDIGO  	0x408
#define TURQUOISE	0x4ED
#define OLIVE 		0x682
#define MAROON 		0x800
#define PURPLE 		0x808
#define GRAY 		0x888
#define SKYBLUE		0x8CE
#define BROWN		0xB22
#define CRIMSON 	0xD13
#define ORCHID 		0xD7D
#define RED			0xF00
#define MAGENTA		0xF0F
#define ORANGE 		0xF40
#define PINK		0xF6A
#define CORAL 		0xF75
#define SALMON 		0xF87
#define GOLD 		0xFD0
#define YELLOW		0xFF0
#define WHITE		0xFFF

//*******************************************************
//                              Circle Definitions
//*******************************************************
#define FULLCIRCLE 1
#define OPENSOUTH  2
#define OPENNORTH  3
#define OPENEAST   4
#define OPENWEST   5
#define OPENNORTHEAST 6
#define OPENNORTHWEST 7
#define OPENSOUTHEAST 8
#define OPENSOUTHWEST 9

/* LCD functions */

	void LCDCommand(unsigned char datacmd);
	void LCDData(unsigned char datadt);
	uint16 swapColors(uint16 in);

	void init(int type, uint8 colorSwap);
	void clear(int color);
	void contrast(char setting);

	void setPixel(int color, unsigned char x, unsigned char y);
	void setCircle (int x0, int y0, int radius, int color);

	void setChar(char c, int x, int y, int fColor, int bColor);
	void setStr(char *pString, int x, int y, int fColor, int bColor);

	void setLine(int x0, int y0, int x1, int y1, int color);
	void setRect(int x0, int y0, int x1, int y1, unsigned char fill, int color);

	void printLogo(void);

	void on(void);
	void off(void);


