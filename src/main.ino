const int LED_PINS[]  = {5, 6, 7, 8, 9, 10, 11, 12};
const int numLeds = sizeof(LED_PINS) / sizeof(int);

void setup() {
  setupLeds();
}

void loop() {
  flashLedsInCascadeMirrored(20, 50, true);
  flashLedsInCascadeMirrored(1, 100, false);
  flashLedsInCascadeMirrored(1, 100, true);

  delay(250);
  
  flashCenterLeds(3, 50);
  
  delay(1000);
  
  flashSidesAlternating(5, 500);
  
  delay(250);
}

void setupLeds() {
  // Setting all LEDs as OUTPUT.
  for (int ledPin : LED_PINS) {
    pinMode(ledPin, OUTPUT);
  }
}

/**
 * Flashes the LEDs in cascade while also creating a mirroring effect.
 * 
 * @param iterations The number of times to repeat the flashing pattern.
 * @param delayTime The delay time in milliseconds between each individual flash.
 * @param fromLeft If true, cascades from left. Otherwise, cascades from right.
 */
void flashLedsInCascadeMirrored(int iterations, int delayTime, bool fromLeft) {
  int step = (fromLeft) ? 1 : -1;

  for (int i = 0; i < iterations; i++) {
    int currLedIndex = (fromLeft) ? 0 : numLeds / 2 - 1;

    for (int j = 0; j < numLeds / 2; j++) {
      int currLedPin = LED_PINS[currLedIndex];
      int currRelativeLedPin = LED_PINS[numLeds - currLedIndex - 1];

      digitalWrite(currLedPin, HIGH);
      digitalWrite(currRelativeLedPin, HIGH);

      delay(delayTime);

      digitalWrite(currLedPin, LOW);
      digitalWrite(currRelativeLedPin, LOW);

      currLedIndex += step;
    }
  }
}

/**
 * Flashes the two LEDs in the center.
 *
 * @param iterations The number of times to repeat the flashing pattern.
 * @param flashTime The time in milliseconds before the LEDs stop flashing.
 */ 
void flashCenterLeds(int iterations, int flashTime) {
  int centerLeftPin = LED_PINS[numLeds / 2];
  int centerRightPin = LED_PINS[numLeds / 2 - 1];

  for (int i = 0; i < iterations; i++) {
    digitalWrite(centerLeftPin, HIGH);
    digitalWrite(centerRightPin, HIGH);

    delay(flashTime);

    digitalWrite(centerLeftPin, LOW);
    digitalWrite(centerRightPin, LOW);

    if (i != iterations - 1) {
      delay(100);
    }
  }
}

/**
 * Flashes the first and second half of LEDs in an alternating manner.
 * 
 * @param iterations The number of timesto repeat the flashing pattern.
 * @param delayTime The delay time in milliseconds before alternating sides.
 */
void flashSidesAlternating(int iterations, int delayTime) {
  for (int i = 0; i < iterations; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < numLeds / 2; k++) {
        int currLedPin = LED_PINS[k];

        digitalWrite(currLedPin, HIGH);
      }

      delay(100);

      for (int k = 0; k < numLeds / 2; k++) {
        int currLedPin = LED_PINS[k];

        digitalWrite(currLedPin, LOW);
      }

      delay(100);
    }

    delay(delayTime);

    for(int j = 0; j < 2; j++) {
      for (int k = numLeds / 2; k < numLeds; k++) {
        int currLedPin = LED_PINS[k];

        digitalWrite(currLedPin, HIGH);
      }

      delay(100);

      for (int k = numLeds / 2; k < numLeds; k++) {
        int currLedPin = LED_PINS[k];

        digitalWrite(currLedPin, LOW);
      }

      delay(100);
    }

    if (i != iterations - 1) {
      delay(delayTime);
    }
  }
}