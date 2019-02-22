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
#include "project.h"

#define SHORT_DELAY 500 //ms

CY_ISR_PROTO(ISR_UP_Handler);
CY_ISR_PROTO(ISR_DOWN_Handler);
void key_init();

enum {
    KEY_NONE,
    KEY_LEFT_SHORT,
    KEY_RIGHT_SHORT,
    KEY_LEFT_LONG,
    KEY_RIGHT_LONG,
    KEY_LEFT_RIGHT,
    KEY_RIGHT_LEFT
};
/*
KEY_NONE - wait press


*/

/* [] END OF FILE */
