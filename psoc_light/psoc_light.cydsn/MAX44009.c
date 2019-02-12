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
#include "i2c1.h"
#include "MAX44009.h"

#define MAX4400_ADDR 0x4A

void MAX44009_init(){
    uint8 data=0x40;
    I2C_WriteBuffer(MAX4400_ADDR, 0x2, &data, 1);
}

float MAX44009_lux(void){
    uint8 data[2]={0};
    data[0]=0x03;
    
    I2C_ReadBuffer(MAX4400_ADDR, 0x3, (uint8*)&data, 2);
	// Convert the data to lux
	int exponent = (data[0] & 0xF0) >> 4;
	int mantissa = ((data[0] & 0x0F) << 4) | (data[1] & 0x0F);
	
	//float luminance = pow(2, exponent) * mantissa * 0.045;
	float luminance = (float)(((0x00000001 << exponent) * (float)mantissa) * 0.045);
  
	return luminance; 
}
/* [] END OF FILE */
