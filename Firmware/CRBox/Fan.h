#ifndef FAN_H
#define FAN_H

#include "Arduino.h"

class Fan {

  public:

    Fan(
      uint8_t minimumSpeed = 25,
      uint8_t maximumSpeed = 100
    );
    void setSpeed(uint8_t speed);

  private:

    uint8_t _minimumSpeed;
    uint8_t _maximumSpeed;

};

#endif