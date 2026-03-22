#include "Arduino.h"
#include "Configuration.h"
#include "Constants.h"
#include "Potentiometer.h"
#include "Fan.h"

// ------------------------------------------------------------------------------------------------
// Global

// Potentiometer for adjusting the fan speed
Potentiometer speedPotentiometer(
  SPEED_POTENTIOMETER_PIN,
  POTENTIOMETER_SAMPLE_COUNT,
  POTENTIOMETER_INVERTED,
  POTENTIOMETER_LOWER_DEADBAND,
  POTENTIOMETER_UPPER_DEADBAND
);

// Potentiometer for adjusting the on time portion of the duty cycle
Potentiometer onTimePotentiometer(
  ON_TIME_POTENTIOMETER_PIN,
  POTENTIOMETER_SAMPLE_COUNT,
  POTENTIOMETER_INVERTED,
  POTENTIOMETER_LOWER_DEADBAND,
  POTENTIOMETER_UPPER_DEADBAND
);

// Potentiometer for adjusting the off time portion of the duty cycle
Potentiometer offTimePotentiometer(
  OFF_TIME_POTENTIOMETER_PIN,
  POTENTIOMETER_SAMPLE_COUNT,
  POTENTIOMETER_INVERTED,
  POTENTIOMETER_LOWER_DEADBAND,
  POTENTIOMETER_UPPER_DEADBAND
);

// Create a fan object to control the fans via PWM
Fan fans(
  FAN_MINIMUM_SPEED_PERCENT,
  FAN_MAXIMUM_SPEED_PERCENT
);

// On and off time step counts
const uint8_t onTimeSteps = sizeof(ON_TIME_STEPS_MINUTES) / sizeof(ON_TIME_STEPS_MINUTES[0]) - 1;
const uint8_t offTimeSteps = sizeof(OFF_TIME_STEPS_MINUTES) / sizeof(OFF_TIME_STEPS_MINUTES[0]) - 1;

// Flag for checking if the fan are running
bool running;

// Timer for measuring the on / off time duration
uint64_t timer;

// ================================================================================================
// Setup
// ================================================================================================
void setup() {

  // Initialize serial communication
  Serial.begin(SERIAL_BAUD_RATE);

  // Initialize the potentiometers
  speedPotentiometer.begin();
  onTimePotentiometer.begin();
  offTimePotentiometer.begin();

  // Initialize the fans
  fans.begin();

  // Get the fan speed
  uint8_t speedPercent = map(
    speedPotentiometer.read(),
    MINIMUM_10_BIT_VALUE,
    MAXIMUM_10_BIT_VALUE,
    MINIMUM_PERCENT_VALUE,
    MAXIMUM_PERCENT_VALUE
  );

  // Set the fan speed
  fans.setSpeed(speedPercent);

  // Set the running flag to true
  running = true;

  // Start the timer
  timer = millis();

}

// ================================================================================================
// Loop
// ================================================================================================
void loop() {

  // Get the fan speed
  uint8_t speedPercent = map(
    speedPotentiometer.read(),
    MINIMUM_10_BIT_VALUE,
    MAXIMUM_10_BIT_VALUE,
    MINIMUM_PERCENT_VALUE,
    MAXIMUM_PERCENT_VALUE
  );

  // Get the on time index
  uint8_t onTimeIndex = map(
    onTimePotentiometer.read(),
    MINIMUM_10_BIT_VALUE,
    MAXIMUM_10_BIT_VALUE,
    0,
    onTimeSteps
  );

  // Get the off time index
  uint8_t offTimeIndex = map(
    offTimePotentiometer.read(),
    MINIMUM_10_BIT_VALUE,
    MAXIMUM_10_BIT_VALUE,
    0,
    offTimeSteps
  );

  // Get the on and of time in minutes based on the select index
  uint16_t onTimeMinutes = ON_TIME_STEPS_MINUTES[onTimeIndex];
  uint16_t offTimeMinutes = OFF_TIME_STEPS_MINUTES[offTimeIndex];

  // Check if the on or off time is set to 0 minutes
  if (onTimeMinutes == 0 || offTimeMinutes == 0) {

    // Immediately set the fan speed
    fans.setSpeed(speedPercent);

    // Set running flag to true
    running = true;

    // Update the timer
    timer = millis();

  // If the on or off time is set to something different that 0 minutes
  } else {

    // Check if the fans should be running
    if (running) {

      // Update the fan speed
      fans.setSpeed(speedPercent);

      // Check if the on time duration has been reached
      if (millis() - timer >= onTimeMinutes * 60000) {

        // Set the running flag to false and update the timer
        running = false;
        timer = millis();

      }

    // If the fans should not be running
    } else {

      // Set the fan speed to 0 %
      fans.setSpeed(MINIMUM_PERCENT_VALUE);

      // Check if the off time duration has been reached
      if (millis() - timer >= offTimeMinutes * 60000) {

        // Set the running flag to true and update the timer
        running = true;
        timer = millis();

      }

    }

  }

}