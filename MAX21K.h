#include "TeensyI2CDriver.h"

class MAX21K {
  public:
    int init();
    float getX();
    float getY();
    float getZ();
    bool update();
    void setFreq(uint16_t Hz);
  //void enableInterrupt(); does NOT work; poll using update() instead
    
  private:
    TeensyI2CDriver driver;
    uint16_t rawX;
    uint16_t rawY;
    uint16_t rawZ;
    void switchBank(uint8_t bank);
};

