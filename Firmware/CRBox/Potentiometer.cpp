#include "Potentiometer.h"

// ================================================================================================
// Insertion sort (https://en.wikipedia.org/wiki/Insertion_sort#Implementation)
// ================================================================================================
void insertionSort(
  uint16_t array[],
  uint8_t size
) {

  // Treat the array[0..i-1] as the sorted part, and array[i..end] as unsorted
  for (uint8_t i = 1; i < size; i++) {

    uint16_t key = array[i]; // The value to insert into the sorted prefix
    int16_t j = i - 1;

    // Shift larger elements one position to the right util the position of the key is correct
    while (j >= 0 && array[j] > key) {

      array[j + 1] = array[j];
      j--;

    }

    // Place key into the gap created by shifting
    array[j + 1] = key;

  }

}

// ================================================================================================
// Get the mean of the inter quartile range
// ================================================================================================
uint16_t getIQRMean(
  uint16_t array[],
  uint8_t size
) {

  // Get the index of the 25th and 75th percentile of the data
  uint8_t start = round(size * 0.25);
  uint8_t end = round(size * 0.75);

  // Constrain the indexes to fit inside the array
  start = constrain(start, 0, size);
  end = constrain(end, start + 1, size);

  // Check if the start and end index are the same value
  if (start == end) {

    // Check if the start index is already the lowest value it can be
    if (start == 0) {

      // There are no values to loop trough so return 0
      return 0;

    }

    // Decrease the start index by 1 to loop through at least 1 value
    start--;

  }

  // Sum of values
  uint32_t sum = 0;

  // Loop through the inter quartile range
  for (uint8_t index = start; index < end; index++) {

    // Add the value to the sum
    sum += array[index];

  }

  // Get the length of the IQR and calculate the mean
  uint8_t length = end - start;
  uint16_t mean = round(sum / length);

  // Return the IQR mean
  return mean;

}

// ================================================================================================
// Constructor
// ================================================================================================
Potentiometer::Potentiometer(
  uint8_t pin,
  uint8_t sampleCount,
  bool inverted,
  uint16_t lowerDeadband,
  uint16_t upperDeadband
):
  _pin(pin),
  _sampleCount(sampleCount),
  _inverted(inverted),
  _lowerDeadband(lowerDeadband),
  _upperDeadband(upperDeadband)
{

  // Set the pin mode
  pinMode(_pin, INPUT);

  // Constrain the sample count to atleast 1 sample
  _sampleCount = constrain(_sampleCount, 1, 255);

}

// ================================================================================================
// Read the potentiometer
// ================================================================================================
uint16_t Potentiometer::read() {

  // Array of potentiometer samples
  uint16_t samples[_sampleCount];

  // Loop for the number of samples to take
  for (uint8_t sample = 0; sample < _sampleCount; sample++) {

    // Take array sample
    samples[sample] = analogRead(_pin);

  }

  // Sort the samples
  insertionSort(samples, _sampleCount);

  // Get the mean IQR reading from the samples
  uint16_t reading = getIQRMean(samples, _sampleCount);

  // Clamp the mean reading to the lower and upper dead band
  reading = constrain(reading, _lowerDeadband, _upperDeadband);

  // Check if reading is inverted
  if (_inverted) {

    // Map the clamped mean value to a range of 0 - 1023 (inverted)
    reading = map(reading, _lowerDeadband, _upperDeadband, 1023, 0);
  
  } else {

    // Map the clamped mean value to a range of 0 - 1023
    reading = map(reading, _lowerDeadband, _upperDeadband, 0, 1023);

  }

  // Constrain the reading to a range from 0 to 1023
  reading = constrain(reading, 0, 1023);

  // Return the reading
  return reading;

}