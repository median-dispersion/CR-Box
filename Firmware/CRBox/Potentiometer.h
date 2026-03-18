#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "Arduino.h"

class Potentiometer {

  public:

    Potentiometer(
      uint8_t pin,
      uint8_t sampleCount = 128,
      bool inverted = false,
      uint16_t lowerDeadband = 32,
      uint16_t upperDeadband = 992
    );
    uint16_t read();

  private:

    uint8_t _pin;
    uint8_t _sampleCount;
    bool _inverted;
    uint16_t _lowerDeadband;
    uint16_t _upperDeadband;

};

#endif