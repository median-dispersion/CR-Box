// Pin configuration
#define SPEED_POTENTIOMETER_PIN    A0 // Must be an analog pin!
#define ON_TIME_POTENTIOMETER_PIN  A2 // Must be an analog pin!
#define OFF_TIME_POTENTIOMETER_PIN A4 // Must be an analog pin!
#define FAN_SPEED_CONTROL_PIN      9  // Must be pin 9!

// Potentiometer configuration
#define POTENTIOMETER_SAMPLE_COUNT   128
#define POTENTIOMETER_INVERTED       false
#define POTENTIOMETER_LOWER_DEADBAND 32
#define POTENTIOMETER_UPPER_DEADBAND 970

// Fan configuration
#define FAN_MINIMUM_SPEED_PERCENT 0
#define FAN_MAXIMUM_SPEED_PERCENT 100

// On and off time configuration
constexpr uint16_t ON_TIME_STEPS_MINUTES[]  = {0, 30, 60, 120, 240, 480, 720};
constexpr uint16_t OFF_TIME_STEPS_MINUTES[] = {0, 30, 60, 120, 240, 480, 720};

// Serial configuration
#define SERIAL_BAUD_RATE 9600