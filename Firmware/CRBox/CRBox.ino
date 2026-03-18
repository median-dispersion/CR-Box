#include "Arduino.h"
#include "Configuration.h"
#include "Potentiometer.h"
#include "Fan.h"

Potentiometer speedPotentiometer(
  SPEED_POTENTIOMETER_PIN,
  POTENTIOMETER_SAMPLE_COUNT,
  POTENTIOMETER_INVERTED_STATE,
  POTENTIOMETER_LOWER_DEADBAND,
  POTENTIOMETER_UPPER_DEADBAND
);

Potentiometer durationPotentiometer(
  DURATION_POTENTIOMETER_PIN,
  POTENTIOMETER_SAMPLE_COUNT,
  POTENTIOMETER_INVERTED_STATE,
  POTENTIOMETER_LOWER_DEADBAND,
  POTENTIOMETER_UPPER_DEADBAND
);

Potentiometer dutyCyclePotentiometer(
  DUTY_CYCLE_POTENTIOMETER_PIN,
  POTENTIOMETER_SAMPLE_COUNT,
  POTENTIOMETER_INVERTED_STATE,
  POTENTIOMETER_LOWER_DEADBAND,
  POTENTIOMETER_UPPER_DEADBAND
);

Fan fans(
  FAN_MINIMUM_SPEED,
  FAN_MAXIMUM_SPEED
);

// ================================================================================================
// Setup
// ================================================================================================
void setup() {

  // Set up serial configuration
  Serial.begin(SERIAL_BAUD_RATE);

}

// ================================================================================================
// Loop
// ================================================================================================
void loop() {}