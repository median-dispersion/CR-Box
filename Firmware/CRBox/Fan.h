#ifndef FAN_H
#define FAN_H

#include "Arduino.h"

class Fan {

  public:

    Fan(
      const uint8_t minimumSpeed,
      const uint8_t maximumSpeed
    );
    void begin();
    void setSpeed(const uint8_t speed);

  private:

    const uint8_t _minimumSpeed;
    const uint8_t _maximumSpeed;
    uint8_t _speed;

};

#endif