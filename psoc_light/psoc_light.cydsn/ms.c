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
#include "ms.h"

void ms_init(){
    TimerADC_Init();
    OPA_Start();

    ADC_Start();
    ISR_ADC_StartEx(ISR_ADC_Handler);
    ADC_StartConvert();
}

CY_ISR(ISR_ADC_Handler){
}

/* [] END OF FILE */
