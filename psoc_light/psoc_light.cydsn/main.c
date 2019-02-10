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
#include "lcd_ili9341.h"
#include "project.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    I2C_I2CInit();
    SPI_Master_Init();
    
    lcd_init();
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
