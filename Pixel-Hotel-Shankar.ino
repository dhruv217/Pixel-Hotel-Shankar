#include "Pixel-Hotel-Shankar.h"

// How many leds in your strip?
#define NUM_LEDS 168

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 7

// Define the array of leds

CRGB leds_plus_safety_pixel[NUM_LEDS + 1];
CRGB *const leds(leds_plus_safety_pixel + 1);

void setup()
{
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop()
{
    // Turn the LED on, then pause
    for(int i=0; i<12;i++){
        for(int j=0; j<19; j++){
            if(i%2==0){
                leds[Hotel_H[j][i]] = CRGB::Green;
            }
            else {
                leds[Hotel_H[j][i]] = CRGB::Blue;
            }
        }
        FastLED.show();
        delay(100);
    }
}
