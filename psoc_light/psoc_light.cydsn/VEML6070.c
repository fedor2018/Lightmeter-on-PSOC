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
/*
  Example sketch for VEML6070-Breakout (Digital UV Light Sensor).
  Rset=270k on breakout, UVA sensitivity: 5.625 uW/cm²/step
  Board           I2C/TWI Pins
                  SDA, SCL
  ----------------------------
  Uno, Ethernet    A4, A5
  Mega             20, 21
  Leonardo          2,  3
  Due              20, 21
  Integration Times and UVA Sensitivity:
    Rset=240k -> 1T=100.0ms ->   5.000 uW/cm²/step
    Rset=270k -> 1T=112.5ms ->   5.625 uW/cm²/step
    Rset=300k -> 1T=125.0ms ->   6.250 uW/cm²/step
    Rset=600k -> 1T=250.0ms ->  12.500 uW/cm²/step
*/

#define VEML6070_ADDR_L 0x38 //(0x71>>1) //0x38
#define VEML6070_ADDR_H 0x39 //(0x73>>1) //0x39
#define VEML6070_T	0x4|0x2	//1T 125ms

#define VEML6070_ADDR 0x38 //0x38 and 0x39

//Integration Time
#define IT_1_2 0x0 //1/2T
#define IT_1   0x1 //1T
#define IT_2   0x2 //2T
#define IT_4   0x3 //4T

void VEML6070_init(){
    I2C_WriteReg(VEML6070_ADDR, (IT_1<<2) | 0x02);
}

float VEML6070_uv(void){
    uint8 data;
    I2C_ReadBuffer(VEML6070_ADDR_H, 0x73, &data, 1);
    uint16 uv = (data<<8);
    I2C_ReadBuffer(VEML6070_ADDR_L, 0x71, &data, 1);
    uv|= data;
    return (float)uv;
}

float VEML6070_uvi(void){
/*    uint16_t uva;
    uint16_t uvb;
    uint16_t uvComp1;
    uint16_t uvComp2;

    //if ((_lastReadTime + _integrationTime) > millis())
    //{
//        return _lastIndex;
 //   }

    float uvaCalc = this->uva();
    float uvbCalc = this->uvb();

    float uvia = uvaCalc * (1.0 / UV_ALPHA) * _aResponsivity;
    float uvib = uvbCalc * (1.0 / UV_BETA) * _bResponsivity;
    _lastIndex = (uvia + uvib) / 2.0;
    if (_hdEnabled)
    {
        _lastIndex *= HD_SCALAR;
    }
    
    _lastReadTime = millis();
    return _lastIndex;*/
    return 0.0;
}


/* [] END OF FILE */
