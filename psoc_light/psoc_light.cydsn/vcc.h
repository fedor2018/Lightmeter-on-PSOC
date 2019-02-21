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

void vcc_init();
uint16_t vcc_get();

#define IMAX 306   //uA =>Vmax
#define RES  6800 //sink resistor Vmax/Imax
//#define VBAT 4200
//#define VMAX (VBAT*(5100/(5100+5600))) //2V
#define VBIT ((float)(RES*IMAX)/0x7F) //Vref max/0x7F (V)
#define RDIV ((float)(5100+5600)/5100) //2.08
/* [] END OF FILE */
