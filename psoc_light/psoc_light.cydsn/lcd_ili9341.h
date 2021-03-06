/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef LCD_ILI9341_H_
#define LCD_ILI9341_H_


#include <stdint.h>	

    
#define MAX_HORIZ	240
#define MAX_VERT	320
//#define ILI9341_TFTWIDTH   240
//#define ILI9341_TFTHEIGHT  320

#define ILI9341_NOP        0x00
#define ILI9341_SWRESET    0x01
#define ILI9341_RDDID      0x04
#define ILI9341_RDDST      0x09

#define ILI9341_SLPIN      0x10
#define ILI9341_SLPOUT     0x11
#define ILI9341_PTLON      0x12
#define ILI9341_NORON      0x13

#define ILI9341_RDMODE     0x0A
#define ILI9341_RDMADCTL   0x0B
#define ILI9341_RDPIXFMT   0x0C
#define ILI9341_RDIMGFMT   0x0D
#define ILI9341_RDSELFDIAG 0x0F

#define ILI9341_INVOFF     0x20
#define ILI9341_INVON      0x21
#define ILI9341_GAMMASET   0x26
#define ILI9341_DISPOFF    0x28
#define ILI9341_DISPON     0x29

#define ILI9341_CASET      0x2A
#define ILI9341_PASET      0x2B
#define ILI9341_RAMWR      0x2C
#define ILI9341_RAMRD      0x2E

#define ILI9341_PTLAR      0x30
#define ILI9341_MADCTL     0x36
#define ILI9341_VSCRSADD   0x37
#define ILI9341_PIXFMT     0x3A

#define ILI9341_FRMCTR1    0xB1
#define ILI9341_FRMCTR2    0xB2
#define ILI9341_FRMCTR3    0xB3
#define ILI9341_INVCTR     0xB4
#define ILI9341_DFUNCTR    0xB6

#define ILI9341_PWCTR1     0xC0
#define ILI9341_PWCTR2     0xC1
#define ILI9341_PWCTR3     0xC2
#define ILI9341_PWCTR4     0xC3
#define ILI9341_PWCTR5     0xC4
#define ILI9341_VMCTR1     0xC5
#define ILI9341_VMCTR2     0xC7

#define ILI9341_RDID1      0xDA
#define ILI9341_RDID2      0xDB
#define ILI9341_RDID3      0xDC
#define ILI9341_RDID4      0xDD

#define ILI9341_GMCTRP1    0xE0
#define ILI9341_GMCTRN1    0xE1
/*
#define ILI9341_PWCTR6     0xFC

 */

// Color definitions
#define ILI9341_BLACK       0x0000      /*   0,   0,   0 */
#define ILI9341_NAVY        0x000F      /*   0,   0, 128 */
#define ILI9341_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define ILI9341_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define ILI9341_MAROON      0x7800      /* 128,   0,   0 */
#define ILI9341_PURPLE      0x780F      /* 128,   0, 128 */
#define ILI9341_OLIVE       0x7BE0      /* 128, 128,   0 */
#define ILI9341_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define ILI9341_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define ILI9341_BLUE        0x001F      /*   0,   0, 255 */
#define ILI9341_GREEN       0x07E0      /*   0, 255,   0 */
#define ILI9341_CYAN        0x07FF      /*   0, 255, 255 */
#define ILI9341_RED         0xF800      /* 255,   0,   0 */
#define ILI9341_MAGENTA     0xF81F      /* 255,   0, 255 */
#define ILI9341_YELLOW      0xFFE0      /* 255, 255,   0 */
#define ILI9341_WHITE       0xFFFF      /* 255, 255, 255 */
#define ILI9341_ORANGE      0xFD20      /* 255, 165,   0 */
#define ILI9341_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define ILI9341_PINK        0xF81F

#define LCD_SOFT_RESET				0x01
#define LCD_GET_RED_CHANNEL			0x06
#define LCD_GET_GREEN_CHANNEL		0x07
#define LCD_GET_BLUE_CHANNEL		0x08
#define LCD_GET_PIXEL_FMT			0x0C
#define LCD_GET_PWR_MODE			0x0A
#define LCD_GET_ADDRESS_MODE		0x0B
#define LCD_GET_DISP_MODE			0x0D
#define LCD_GET_SIGNAL_MODE			0x0E
#define LCD_GET_DIAG_RESULT			0x0F
#define LCD_ENTER_SLEEP_MODE		0x10
#define LCD_EXIT_SLEEP_MODE			0x11
#define LCD_ENTER_PART_MODE			0x12
#define LCD_ENTER_NORM_MODE			0x13
#define LCD_EXIT_INVERT_MODE		0x20
#define LCD_ENTER_INVERT_MODE		0x21
#define LCD_SET_GAMMA_CURVE			0x26
#define LCD_SET_DISP_OFF			0x28
#define LCD_SET_DISP_ON				0x29
#define LCD_SET_COL_ADDRESS			0x2A
#define LCD_SET_PAGE_ADDRESS		0x2B
#define LCD_WRITE_MEM_START			0x2C
#define LCD_WRITE_LUT				0x2D
#define LCD_READ_MEM_START			0x2E
#define LCD_SET_PARTIAL_AREA		0x30
#define LCD_SET_SCROLL_AREA			0x33
#define LCD_SET_TEAR_OFF			0x34
#define LCD_SET_TEAR_ON				0x35
#define LCD_SET_ADDRESS_MODE		0x36
#define LCD_SET_SCROLL_START		0x37
#define LCD_EXIT_IDLE_MODE			0x38
#define LCD_ENTER_IDLE_MODE			0x39
#define LCD_SET_PIXEL_FMT			0x3A
#define LCD_WRITE_MEM_CONTINUE		0x3C
#define LCD_READ_MEM_CONTINUE		0x3E
#define LCD_SET_TEAR_SCANLINE		0x44
#define LCD_GET_SCANLINE			0x45
#define LCD_READ_ID1				0xDA
#define LCD_READ_ID2				0xDB
#define LCD_READ_ID3				0xDC
#define LCD_FRAME_RATE_CTRL1		0xB1
#define LCD_FRAME_RATE_CTRL2		0xB2
#define LCD_FRAME_RATE_CTRL3		0xB3
#define LCD_DISPLAY_INVERSION		0xB4
#define LCD_SOURCE_DRIVER_DIRECTION 0xB7
#define LCD_GATE_DRIVER_DIRECTION   0xB8
#define LCD_POWER_CONTROL1          0xC0
#define LCD_POWER_CONTROL2          0xC1
#define LCD_POWER_CONTROL3          0xC2
#define LCD_POWER_CONTROL4          0xC3
#define LCD_POWER_CONTROL5          0xC4
#define LCD_VCOM_CONTROL1           0xC5
#define LCD_VCOM_CONTROL2           0xC6
#define LCD_VCOM_OFFSET_CONTROL     0xC7
#define LCD_WRITE_ID4_VALUE         0xD3
#define LCD_NV_MEMORY_FUNCTION1     0xD7
#define LCD_NV_MEMORY_FUNCTION2     0xDE
#define LCD_POSITIVE_GAMMA_CORRECT  0xE0
#define LCD_NEGATIVE_GAMMA_CORRECT  0xE1
#define LCD_GAM_R_SEL               0xF2

#define BLACK	0x0000
#define BLUE	0xF800
#define GREEN	0x07E0
#define RED	    0x001F
#define WHITE	0xFFFF


void lcd_drawPixel(uint16_t x, uint16_t y, uint16_t color);
void lcd_setScreen(uint16_t Color);
void lcd_setArea(uint16_t Color, uint16_t sizeX, uint16_t sizeY, uint16_t startX, uint16_t startY);
void lcd_init(void);
 

#endif /* LCD_ILI9341_H_ */

/* [] END OF FILE */
