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
#include "MAX44009.h"

#define MAX4400_ADDR 0x4A

void MAX4400_Write(uint8 Reg, uint8 value){
}

void MAX44009_init(){
    uint8 data[2]={0};
    data[0]=0x02;
    data[1]=0x40;

    I2C_I2CMasterWriteBuf(MAX4400_ADDR,data,2,I2C_I2C_MODE_COMPLETE_XFER);
    while((I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT)==0){}
}

float MAX44009_lux(void){
    uint8 data[2]={0};
    data[0]=0x03;
    
    I2C_I2CMasterWriteBuf(MAX4400_ADDR,data,1,I2C_I2C_MODE_NO_STOP);
    while((I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT)==0){}
    
    I2C_I2CMasterReadBuf(MAX4400_ADDR,data,2,I2C_I2C_MODE_REPEAT_START);
    while((I2C_I2CMasterStatus() & I2C_I2C_MSTAT_RD_CMPLT)==0){}
    
	// Convert the data to lux
	int exponent = (data[0] & 0xF0) >> 4;
	int mantissa = ((data[0] & 0x0F) << 4) | (data[1] & 0x0F);
	
	//float luminance = pow(2, exponent) * mantissa * 0.045;
	float luminance = (float)(((0x00000001 << exponent) * (float)mantissa) * 0.045);
  
	return luminance; 
}
/* [] END OF FILE */
