#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "Arduino.h"

class Potentiometer {

  public:

    Potentiometer(
      const uint8_t pin,
      const uint8_t sampleCount = 128,
      const bool inverted = false,
      const uint16_t lowerDeadband = 32,
      const uint16_t upperDeadband = 992
    );
    void begin();
    uint16_t read();

  private:

    const uint8_t _pin;
    const uint8_t _sampleCount;
    const bool _inverted;
    const uint16_t _lowerDeadband;
    const uint16_t _upperDeadband;

};

#endif