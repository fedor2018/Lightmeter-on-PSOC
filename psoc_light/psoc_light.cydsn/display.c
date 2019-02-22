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
#include "display.h"
#include "TFT.h"

/*
Light ~620nm          0.045-188000Lux
UVA   320-400nm       
UVB   280-320nm
UVI
Temperature
Humidly
Barometer
Vcc
*/
extern uint16_t MAX_X, MAX_Y ;          // display screen size (TFT.c)

void display_init(){
    SPIM_Start();
    TFT_Init(3);    // landscape with connector on left
    MAX_X=240;
    MAX_Y=320;
    TFT_FillScreen(0, MAX_X, 0, MAX_Y, BLACK);	
}

/* [] END OF FILE */
