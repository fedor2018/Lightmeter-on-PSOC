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
#include "TFT.h"
#include "MAX44009.h"
#include "VEML6070.h"
#include "vcc.h"
#include "key.h"

extern uint16_t MAX_X, MAX_Y ;          // display screen size (TFT.c)

int main(void)
{
    vcc_init();
    if(vcc_get()<30){
        CySysPmStop();//poweroff
    }
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    key_init();
    I2C_I2CInit();
    MAX44009_init();
    VEML6070_init();
    SPIM_Start();
    
    TFT_Init(3);    // landscape with connector on left
    MAX_X=240;
    MAX_Y=320;
    TFT_FillScreen(0, MAX_X, 0, MAX_Y, BLACK);	
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
