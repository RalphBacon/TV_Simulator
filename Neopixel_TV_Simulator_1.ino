#include "Arduino.h"

// This is the library we need
#include "FastLED.h"

// How many LEDs are connected?
#define NUM_LEDS 12

// Define the Pins
#define DATA_PIN 2

// Define the array of LEDs
CRGB leds[NUM_LEDS];

// ---------------------------------------------------------------
// SETUP     SETUP     SETUP     SETUP     SETUP     SETUP
// ---------------------------------------------------------------
void setup() {
	// Initialise Neopixel ring
	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

	// Seed the random number generator
	randomSeed(analogRead(4));

	// Debug window
	Serial.begin(9600);
}

// ---------------------------------------------------------------
// LOOP     LOOP     LOOP     LOOP     LOOP     LOOP     LOOP
// ---------------------------------------------------------------
void loop() {

	// All LEDs set to 'black'
	FastLED.clear(true);

	// White LEDs, min to max-1
	int whiteLEDs = random(0, 4);

	// If we have no white colours at all...
	if (whiteLEDs == 0) {
		// ... then blank everything for a small time, one time in x times
		if (random(1, 4) == 1)
			delay(random(500, 2000));
	}

	// Set the white LEDs first:
	// colour (irrelevant here as we want white), saturation (always 0, no colour), brightness (a random value)
	for (int led = 0; led < whiteLEDs; led++) {
		leds[led] = CHSV(100, 0, random(10, 255));
	}

	// Now fill the remaining LEDs with colour
	int cycles = random(1, 10);
	for (int cycle = 0; cycle < cycles; cycle++) {
		for (int led = whiteLEDs; led < NUM_LEDS; led++) {
			leds[led] = CHSV(random(1, 255), random(128, 255), random(10, 255));
		}

		// Update the display
		FastLED.show();

		// random delay between 'scenes' aka cycles
		delay(random(100, 2000));
	}
}
