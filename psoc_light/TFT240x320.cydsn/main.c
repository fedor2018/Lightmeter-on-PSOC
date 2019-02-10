/*
M. Ray Burnette / 20140720
PSoC 4200 Prototype or 4200 Pioneer Boards
Demostration of ILI9340 TFT SPI display running on PSoC 4200

Flash used: 12966 of 32768 bytes (39.6 %).
SRAM used: 1592 of 4096 bytes (38.9 %).

This project path: C:\Users\owner\Documents\PSoC Creator\Working\TFT240_320_4200\TFT240x320.cydsn\TFT240x320.cyprj
*/

#include <project.h>   
#include <TFT.h> 
#include <device.h>
#include <stdio.h>                      // sprintf function

extern uint16_t MAX_X, MAX_Y ;          // display screen size (TFT.c)

static char Text[] = {'T','h','e',32,
                      'Q','u','i','c','k',32,
                      'B','r','o','w','n',32,
                      'F','o','x','!','!'};

int main()
{
    SPIM_Start();
    while(1)
    {
    TFT_Init(3);    // landscape with connector on left
    TFT_FillScreen(0, MAX_X, 0, MAX_Y, BLACK);	
    //     DrawStringBl(char *string,uint16_t poX, uint16_t poY, uint16_t size,uint16_t fgcolor,uint16_t bgcolor);
    //DrawStringBl("TFT Testing...",  15, 50, 2, RED, GREEN);
    TFT_DrawString("TFT Testing...",  15, 50, 2, GREEN);

    CyDelay(5000);

    //  FillRectangle(X, Y, length, width, color);
    TFT_FillRectangle(0,  0,   320,    20, BLACK);

    //  DrawString(char *string, poX, poY, size,    fgcolor);
    TFT_DrawString (Text,          5,   1,    1,    WHITE);
    CyDelay(5000);
    }
}


