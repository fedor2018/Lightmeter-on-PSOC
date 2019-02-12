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

void VEML6075_init(){
    I2C_WriteReg(VEML6070_ADDR, (IT_1<<2) | 0x02);
}

float VEML6075_uv(void){
    uint8 data;
    I2C_ReadBuffer(VEML6070_ADDR_H, 0x73, &data, 1);
    uint16 uv = (data<<8);
    I2C_ReadBuffer(VEML6070_ADDR_L, 0x71, &data, 1);
    uv|= data;
    return (float)uv;
}

float VEML6075_uvi(void){
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
/*
VEML6075::VEML6075() {

  // Despite the datasheet saying this isn't the default on startup, it appears
  // like it is. So tell the thing to actually start gathering data.
  this->config = 0;
  this->config |= VEML6075_CONF_SD_OFF;

  // App note only provided math for this one...
  this->config |= VEML6075_CONF_IT_100MS;
}

bool VEML6075::begin() {

  Wire.begin();
  if (this->getDevID() != VEML6075_DEVID) {
    return false;
  }

  // Write config to make sure device is enabled
  this->write16(VEML6075_REG_CONF, this->config);

  return true;
}

// Poll sensor for latest values and cache them
void VEML6075::poll() {
  this->raw_uva = this->read16(VEML6075_REG_UVA);
  this->raw_uvb = this->read16(VEML6075_REG_UVB);
  this->raw_dark = this->read16(VEML6075_REG_DUMMY);
  this->raw_vis = this->read16(VEML6075_REG_UVCOMP1);
  this->raw_ir = this->read16(VEML6075_REG_UVCOMP2);
}

uint16_t VEML6075::getRawUVA() {
  return this->raw_uva;
}

uint16_t VEML6075::getRawUVB() {
  return this->raw_uvb;
}

uint16_t VEML6075::getRawDark() {
  return this->raw_dark;
}

uint16_t VEML6075::getRawVisComp() {
  return this->raw_vis;
}

uint16_t VEML6075::getRawIRComp() {
  return this->raw_ir;
}


uint16_t VEML6075::getDevID() {
  return this->read16(VEML6075_REG_DEVID);
}

float VEML6075::getUVA() {
  float comp_vis = this->raw_vis - this->raw_dark;
  float comp_ir = this->raw_ir - this->raw_dark;
  float comp_uva = this->raw_uva - this->raw_dark;

  comp_uva -= (VEML6075_UVI_UVA_VIS_COEFF * comp_vis) - (VEML6075_UVI_UVA_IR_COEFF * comp_ir);

  return comp_uva;
}

float VEML6075::getUVB() {
  float comp_vis = this->raw_vis - this->raw_dark;
  float comp_ir = this->raw_ir - this->raw_dark;
  float comp_uvb = this->raw_uvb - this->raw_dark;

  comp_uvb -= (VEML6075_UVI_UVB_VIS_COEFF * comp_vis) - (VEML6075_UVI_UVB_IR_COEFF * comp_ir);

  return comp_uvb;
}

float VEML6075::getUVIndex() {
  float uva_weighted = this->getUVA() * VEML6075_UVI_UVA_RESPONSE;
  float uvb_weighted = this->getUVB() * VEML6075_UVI_UVB_RESPONSE;
  return (uva_weighted + uvb_weighted) / 2.0;
}

uint16_t VEML6075::read16(uint8_t reg) {
  uint8_t msb = 0;
  uint8_t lsb = 0;

  Wire.beginTransmission(VEML6075_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);

  Wire.requestFrom(VEML6075_ADDR, 2, true);
  lsb = Wire.read();
  msb = Wire.read();

  return (msb << 8) | lsb;
}

void VEML6075::write16(uint8_t reg, uint16_t data) {
  Wire.beginTransmission(VEML6075_ADDR);
  Wire.write(reg);
  Wire.write((uint8_t)(0xFF & (data >> 0))); // LSB
  Wire.write((uint8_t)(0xFF & (data >> 8))); // MSB
  Wire.endTransmission();
}
*/
/* [] END OF FILE */
