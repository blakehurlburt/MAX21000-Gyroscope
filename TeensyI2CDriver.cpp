#include "TeensyI2CDriver.h"
#include <i2c_t3.h>

void TeensyI2CDriver::begin() {
  //starting I2C protocol
	Wire.begin();
}

uint8_t TeensyI2CDriver::readRegister(uint8_t addr, uint8_t reg) {

	//Begin transmission to slave with address addr
	Wire.beginTransmission(addr);

	//Select the register reg
	Wire.write(reg);

	//Send transmission *without* STOP because the gyro requires repeating starts
	Wire.endTransmission(false);

	//Request 1 byte of data from addr
	Wire.requestFrom(addr, 1);

	//Read a byte from the I2C buffer and return it
	return Wire.read();
}

uint16_t TeensyI2CDriver::readTwoBytesFromRegister(uint8_t addr, uint8_t reg) {

  //Begin transmission to slave with address addr
  Wire.beginTransmission(addr);

  //Select the register reg
  Wire.write(reg);

  //Send transmission *without* STOP because the gyro requires repeating starts
  Wire.endTransmission(false);

  //Request 2 bytes of data from addr
  Wire.requestFrom(addr, 2);

  /*
   * Reads and combines two bytes from addr.
   * The first byte read is the higher of the two.
   * Shifts this over by 8 places to clear 8 zeroes for the lower byte.
   * Reads the lower byte, then takes their bitwise OR to join them.
   */
  return (Wire.read() << 8) | Wire.read();
}

void TeensyI2CDriver::writeRegister(uint8_t addr, uint8_t reg, uint8_t val) {
	//Begin transmission to slave with address addr
	Wire.beginTransmission(addr);

	//Select the register reg
	Wire.write(reg);

	//Write the value val to the register reg
	Wire.write(val);

	//Send transmission
	Wire.endTransmission();	
}
