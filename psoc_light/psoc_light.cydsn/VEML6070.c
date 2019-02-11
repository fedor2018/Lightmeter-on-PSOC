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

//#include <Wire.h>
#define VEML6070_ADDR_A (0x18>>1)
#define VEML6070_ADDR_C 0x38 //(0x70>>1)
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
    I2C_ReadBuffer(VEML6070_ADDR_H, 0, &data, 1);
    uint16 uv = (data<<8);
    I2C_ReadBuffer(VEML6070_ADDR_L, 0, &data, 1);
    uv|= data;
    return (float)uv;
}

/*
void setup()
{
  Wire.beginTransmission(I2C_ADDR);
  Wire.write((IT_1<<2) | 0x02);
  Wire.endTransmission();
}

void loop()
{
  byte msb=0, lsb=0;
  uint16_t uv;

  Wire.requestFrom(I2C_ADDR+1, 1); //MSB
  delay(1);
  if(Wire.available())
    msb = Wire.read();

  Wire.requestFrom(I2C_ADDR+0, 1); //LSB
  delay(1);
  if(Wire.available())
    lsb = Wire.read();

  uv = (msb<<8) | lsb;
  Serial.println(uv, DEC); //output in steps (16bit)

  delay(1000);
}
*/
/* [] END OF FILE */
