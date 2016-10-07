#include "MAX21K.h"

const uint8_t MAX21K_ADDR = 0x58;

const uint8_t USER_BANK_0 = 0b0000;
const uint8_t USER_BANK_1 = 0b0001;

//Bank 0 registers
const uint8_t POWER_CFG = 0x00;
const uint8_t SENSE_CFG2 = 0x02;

//Bank 1 registers
const uint8_t INT_CFG2 = 0x0B;
const uint8_t INT1_MSK = 0x10;
const uint8_t INT_TMO  = 0x0C;

const uint8_t REG_BANK_SELECT = 0x21;

//Common Bank registers
const uint8_t SYSTEM_STATUS = 0x22;
const uint8_t REG_X = 0x23;
const uint8_t REG_Y = 0x25;
const uint8_t REG_Z = 0x27;


int MAX21K::init() {
	driver.begin();
  switchBank(USER_BANK_0);
  driver.writeRegister(MAX21K_ADDR, POWER_CFG, 0b00001111);
	return 0;
}

void MAX21K::setFreq(uint16_t Hz) {
  switchBank(USER_BANK_0);
  uint8_t n;

  //This function defined on Page 11 of the MAX21000 Programming Guide
  if (100 <= Hz && Hz < 10000)
    n = 10000/Hz - 1;
  else if (20 <= Hz && Hz < 100)
    n = 2000/Hz + 79;
  else if (5 <= Hz && Hz < 20)
    n = 500/Hz + 154;
  else return; //Hz is outside the legal interval [5, 10000]
  
  driver.writeRegister(MAX21K_ADDR, SENSE_CFG2, n);
}

void MAX21K::switchBank(uint8_t bank) {
  driver.writeRegister(MAX21K_ADDR, REG_BANK_SELECT, bank);
}

//Does NOT work; poll using update() instead
/*
void MAX21K::enableInterrupt() {
  switchBank(USER_BANK_1);
  driver.writeRegister(MAX21K_ADDR, INT_CFG2, 0b00100000);
  driver.writeRegister(MAX21K_ADDR, INT1_MSK, 0b10000000);
  driver.writeRegister(MAX21K_ADDR, INT_TMO,  0b11110011);
}*/

bool MAX21K::update() {
  if (driver.readRegister(MAX21K_ADDR, SYSTEM_STATUS) == 0)
    return false;
  rawX = driver.readTwoBytesFromRegister(MAX21K_ADDR, REG_X);
  rawY = driver.readTwoBytesFromRegister(MAX21K_ADDR, REG_Y);
  rawZ = driver.readTwoBytesFromRegister(MAX21K_ADDR, REG_Z);
  return true;
}

float MAX21K::getX() {
  int16_t x = (rawX >= 32768) ? rawX-65536 : rawX;
  return x/960.0;
}

float MAX21K::getY() {
  int16_t y = (rawY >= 32768) ? rawY-65536 : rawY;
  return y/960.0;
}

float MAX21K::getZ() {
  int16_t z = (rawZ >= 32768) ? rawZ-65536 : rawZ;
  return z/960.0;
}


