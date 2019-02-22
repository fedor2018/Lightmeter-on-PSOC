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
#include "MAX44009.h"
#include "VEML6070.h"
#include "vcc.h"
#include "key.h"
#include "ms.h"

int main(void)
{
    vcc_init();
    if(vcc_get()<30){
        CySysPmStop();//poweroff
    }
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    key_init();
    I2C_I2CInit();
    ms_init();
    MAX44009_init();
    VEML6070_init();
    display_init();
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
