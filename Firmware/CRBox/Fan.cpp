#include "Fan.h"
#include "Constants.h"
#include "Configuration.h"

// ================================================================================================
// Constructor
// ================================================================================================
Fan::Fan(
  const uint8_t minimumSpeed,
  const uint8_t maximumSpeed
):
  _minimumSpeed(
    constrain(
      minimumSpeed,
      MINIMUM_PERCENT_VALUE,
      MAXIMUM_PERCENT_VALUE
    )
  ),
  _maximumSpeed(
    constrain(
      maximumSpeed,
      MINIMUM_PERCENT_VALUE,
      MAXIMUM_PERCENT_VALUE
    )
  ),
  _speed(MAXIMUM_8_BIT_VALUE)
{}

// ================================================================================================
// Initialize fan control
// ================================================================================================
void Fan::begin() {

  // Set pin mode
  pinMode(
    FAN_SPEED_CONTROL_PIN,
    OUTPUT
  );

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

  // Set the fan speed to 0 %
  setSpeed(MINIMUM_PERCENT_VALUE);

}

// ================================================================================================
// Set the fan speed
// ================================================================================================
void Fan::setSpeed(const uint8_t speed) {

  // If new speed it equal to current speed
  if (speed == _speed) {

    // Return early
    return;

  }

  // Check if the fan speed is set to 0 %
  if (speed <= MINIMUM_PERCENT_VALUE) {

    // Turn off the fan
    analogWrite(
      FAN_SPEED_CONTROL_PIN,
      MINIMUM_25_KHZ_DUTY_CYCLE_VALUE
    );

    // Update current speed
    _speed = MINIMUM_PERCENT_VALUE;

    // Return early
    return;

  }

  // Update current speed
  _speed = speed;

  // Constrain the speed to a range of 0 to 100 %
  _speed = constrain(
    _speed,
    MINIMUM_PERCENT_VALUE,
    MAXIMUM_PERCENT_VALUE
  );

  // Map the speed to the allowed speed range
  _speed = map(
    _speed,
    MINIMUM_PERCENT_VALUE,
    MAXIMUM_PERCENT_VALUE,
    _minimumSpeed,
    _maximumSpeed
  );

  // Map the speed to a duty cycle
  uint16_t dutyCycle = map(
    _speed,
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
  analogWrite(
    FAN_SPEED_CONTROL_PIN,
    dutyCycle
  );

}