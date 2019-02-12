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
#include <i2c.h>

uint16 BME_P =0xFFFF;
uint16 BME_O =0xFFFF;

int BME_Notify;



void updateBME(){
    
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED)
    return;
    
    CYBLE_GATTS_HANDLE_VALUE_NTF_T tempHandle;
    tempHandle.attrHandle =CYBLE_BME280_BME_BLE_CHAR_HANDLE;
    tempHandle.value.val =(uint8 *)&BME_P;
    tempHandle.value.len =2;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);
    
    if(BME_Notify && (BME_P != BME_O)){
        CyBle_GattsNotification(cyBle_connHandle,&tempHandle);
        BME_O=BME_P;
    }
}



void BleCallBack(uint32 event,void* eventParam){
    
    switch(event){
        
        //When stack is on and device getts disconnected
        case CYBLE_EVT_STACK_ON:
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
        BME_Notify=0;
        CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
        break;
        
        
        //when device again getts connected
        case CYBLE_EVT_GATT_CONNECT_IND:
        updateBME();
        break;
        
        default:
        break;
    }
}



int main(void)
{
    I2C_1_Start();
    CyGlobalIntEnable; /* Enable global interrupts. */


    uint8 PressM,PressL,PressXL, TempM,TempL,TempXL, HumM,HumL;
    uint32 deviceID;
    int x=0xF7;
    BME_WriteReg(CTRL_HUM,0x00);
    BME_WriteReg(CTRL_MEAS,0x03);
    
    CyBle_Start(BleCallBack);    
    
    for(;;)
    {
       deviceID=BME_ReadReg(WHO_I_AM);
    
        PressM=BME_ReadReg(OUT_P_MSB);
        BME_P=PressM;
        updateBME();
        PressL=BME_ReadReg(OUT_P_LSB);
        BME_P=PressL;
        updateBME();
        PressXL=BME_ReadReg(OUT_P_XLSB);
        BME_P=PressXL;
        updateBME();
        
        TempM=BME_ReadReg(OUT_T_MSB);
        BME_P=TempM;
        updateBME();
        TempL=BME_ReadReg(OUT_T_LSB);
        BME_P=TempL;
        updateBME();
        TempXL=BME_ReadReg(OUT_T_XLSB);
        BME_P=TempXL;
        updateBME();
        
        HumM=BME_ReadReg(OUT_H_MSB);
        BME_P=HumM;
        updateBME();
        HumL=BME_ReadReg(OUT_H_LSB);
        BME_P=HumL;
        updateBME();
        
        CyBle_ProcessEvents();
        CyBle_EnterLPM(CYBLE_BLESS_DEEPSLEEP);
    
    }
}

/* [] END OF FILE */
