#include "Fan.h"
#include "Constants.h"

// ================================================================================================
// Constructor
// ================================================================================================
Fan::Fan(
  uint8_t minimumSpeed,
  uint8_t maximumSpeed
):
  _minimumSpeed(minimumSpeed),
  _maximumSpeed(maximumSpeed)
{

  // Set pin mode
  pinMode(9, OUTPUT);

  // Clear control registers
  TCCR1A = 0;
  TCCR1B = 0;

  // Set Fast PWM mode using ICR1 as TOP (Mode 14)
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM12) | (1 << WGM13);

  // Non-inverting PWM on OC1A (Pin 9)
  TCCR1A |= (1 << COM1A1);

  // No prescaler (N = 1)
  TCCR1B |= (1 << CS10);

  // Set TOP for 25 kHz
  ICR1 = MAXIMUM_25_KHZ_DUTY_CYCLE_VALUE;

  // Set inital duty cycle
  OCR1A = MINIMUM_25_KHZ_DUTY_CYCLE_VALUE;

}

// ================================================================================================
// Set the fan speed
// ================================================================================================
void Fan::setSpeed(uint8_t speed) {

  // Check if speed is set to 0 %
  if (speed <= MINIMUM_PERCENT_VALUE) {

    // Turn off fan
    OCR1A = MINIMUM_25_KHZ_DUTY_CYCLE_VALUE;

    // Return
    return;

  }

  // Constrain the speed to a range of 0 to 100 %
  speed = constrain(
    speed,
    MINIMUM_PERCENT_VALUE,
    MAXIMUM_PERCENT_VALUE
  );

  // Map the provided speed to the allowed speed range
  speed = map(
    speed,
    MINIMUM_PERCENT_VALUE,
    MAXIMUM_PERCENT_VALUE,
    _minimumSpeed,
    _maximumSpeed
  );

  // Map the speed to a duty cycle
  uint16_t dutyCycle = map(
    speed,
    MINIMUM_PERCENT_VALUE,
    MAXIMUM_PERCENT_VALUE,
    MINIMUM_25_KHZ_DUTY_CYCLE_VALUE,
    MAXIMUM_25_KHZ_DUTY_CYCLE_VALUE
  );

  // Constrain the duty cycle to a safe range
  dutyCycle = constrain(
    dutyCycle,
    MINIMUM_25_KHZ_DUTY_CYCLE_VALUE,
    MAXIMUM_25_KHZ_DUTY_CYCLE_VALUE
  );

  // Set the duty cycle
  OCR1A = dutyCycle;

}