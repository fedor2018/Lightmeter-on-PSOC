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
#include "key.h"

uint8_t btn_old=0x7;//left | right | delay
uint8_t btn_press=0;

void key_init(){
    POFF_Start();
    Key_Timer_Init();
    ISR_UP_ClearPending();
    ISR_UP_StartEx(ISR_UP_Handler); 
    ISR_DOWN_ClearPending();
    ISR_DOWN_StartEx(ISR_DOWN_Handler); 
}

CY_ISR(ISR_UP_Handler){
    uint8_t btn=(StatReg_Read()&0x6);
    btn|=(Key_Timer_ReadPeriod()>SHORT_DELAY)?0x0:0x1;
    if(btn==btn_old){
        btn_press=0;
        return;
    }
    switch(btn){
        default:
        break;
    }
    btn_old=btn;
}

CY_ISR(ISR_DOWN_Handler){
    Key_Timer_WriteCounter(0);
    Key_Timer_Start();
}
/* [] END OF FILE */
