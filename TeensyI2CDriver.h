#include "Arduino.h"

class TeensyI2CDriver {
  public:
    void begin();
    uint8_t readRegister(uint8_t addr, uint8_t reg);
    uint16_t readTwoBytesFromRegister(uint8_t addr, uint8_t reg);
    void writeRegister(uint8_t addr, uint8_t reg, uint8_t val);
};

