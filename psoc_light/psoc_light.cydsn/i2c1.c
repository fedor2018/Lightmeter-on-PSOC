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
#include "i2c1.h"

int8 I2C_WriteReg(uint8 Addr, uint8 Reg){
    uint32 u32OK = I2C_I2C_MSTR_NO_ERROR;

    u32OK = I2C_I2CMasterWriteBuf(Addr,(uint8 *)&Reg, 1, I2C_I2C_MODE_NO_STOP);
    if(u32OK != I2C_I2C_MSTR_NO_ERROR){
        return -1;
    }
    while(0u == (I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT)){
        /* Wait until master complete write */
    }
    return 0;
}

int8 I2C_WriteBuffer(uint8 Addr, uint8 Reg, uint8 *pBuffer, uint8 Length){
    uint32 u32OK = I2C_I2C_MSTR_NO_ERROR;
    int8 i8Result = 0;
   
    i8Result=I2C_WriteReg(Addr, Reg);
    /* set pointer to indicate the desire register */
/*    u32OK = I2C_I2CMasterWriteBuf(Addr,(uint8 *)&Reg, 1, I2C_I2C_MODE_NO_STOP);
    if(u32OK != I2C_I2C_MSTR_NO_ERROR){
        i8Result = -1;
    }
    while(0u == (I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT)){
        // Wait until master complete write 
    }
*/   
    u32OK = I2C_I2CMasterWriteBuf(Addr, pBuffer, Length, I2C_I2C_MODE_COMPLETE_XFER);
    if(u32OK != I2C_I2C_MSTR_NO_ERROR){
        i8Result = -1;
    }
    while(0u == (I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT)){
        /* Wait until master complete write */
    }
   
    (void) I2C_I2CMasterClearStatus();
   
    return i8Result;
}

int8 I2C_ReadBuffer(uint8 Addr, uint8 Reg, uint8 *pBuffer, uint8 Length){
    uint32 u32OK = I2C_I2C_MSTR_NO_ERROR;
    int8 i8Result = 0;
   
    /* set pointer to indicate the desire register */
    i8Result=I2C_WriteReg(Addr, Reg);
/*    u32OK = I2C_I2CMasterWriteBuf(Addr,(uint8 *)&Reg, 1, I2C_I2C_MODE_NO_STOP);
    if(u32OK != I2C_I2C_MSTR_NO_ERROR){
        i8Result = -1;
    }
    while(0u == (I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT)){
        // Wait until master complete write 
    }
*/   
    /* Read the value from register */
    u32OK = I2C_I2CMasterReadBuf(Addr , pBuffer, Length, I2C_I2C_MODE_REPEAT_START);
    if(u32OK != I2C_I2C_MSTR_NO_ERROR){
        i8Result = -1;
    }
    while(0u == (I2C_I2CMasterStatus() & I2C_I2C_MSTAT_RD_CMPLT)){
        /* Wait until master complete reading */
    }
   
    (void) I2C_I2CMasterClearStatus();
   
    return i8Result;
}

/* [] END OF FILE */
