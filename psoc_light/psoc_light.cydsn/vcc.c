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
#include "vcc.h"

void vcc_init(){
    DAC_Start();
    DAC_SetValue(0);
    Comp_Start();
}

uint16_t vcc_get(){//Vcc*10
    for(uint8_t i=0; i<8; i++){
        DAC_SetValue(i);
        if(StatReg_Read()&0x1){
            return ((float)i*VBIT*RDIV)*10;
        }
    }
    return 0;
}

/* [] END OF FILE */
