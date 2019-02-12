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
#include <i2c.h>

uint32 BME_ReadReg(uint8 Reg){
    uint32 Write_Buf[1]={0};
    Write_Buf[0]=Reg;
    
    uint32 Read_Buf[1]={0};
    
    //Step1
    I2C_1_I2CMasterWriteBuf(BME_ADDR,(uint32 *)Write_Buf,1,I2C_1_I2C_MODE_NO_STOP);
    while((I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_WR_CMPLT)==0){}
    
    //Step2
    I2C_1_I2CMasterReadBuf(BME_ADDR,(uint32 *)Read_Buf,1,I2C_1_I2C_MODE_REPEAT_START);
    while((I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_RD_CMPLT)==0){}
    
    return Read_Buf[0];
}


void BME_WriteReg(uint8 Reg, uint8 value){
    uint8 Write_Buf[2]={0};
    Write_Buf[0]=Reg;
    Write_Buf[1]=value;
    
    I2C_1_I2CMasterWriteBuf(BME_ADDR,(uint8 *)Write_Buf,2,I2C_1_I2C_MODE_COMPLETE_XFER);
    while((I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_WR_CMPLT)==0){}
    
    return;
}
/* [] END OF FILE */
