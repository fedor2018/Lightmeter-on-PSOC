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

#include <project.h>

    #define BME_ADDR   (0x76)
    #define WHO_I_AM   (0xD0)
    #define CTRL_HUM   (0xF2)
    #define CTRL_MEAS  (0xF4)
    
    #define OUT_P_MSB  (0xF7)
    #define OUT_P_LSB  (0xF8)
    #define OUT_P_XLSB (0xF9)
    #define OUT_T_MSB  (0xFA)
    #define OUT_T_LSB  (0xFB)
    #define OUT_T_XLSB (0xFC)
    #define OUT_H_MSB  (0xFD)
    #define OUT_H_LSB  (0xFE)
    
uint32 BME_ReadReg(uint8 Reg);
void BME_WriteReg(uint8 Reg, uint8 value);

/* [] END OF FILE */
