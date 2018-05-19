#include "Pixel-Hotel-Shankar.h"

#define DATA_PIN 7

const uint8_t kMatrixWidth  = 12;
const uint8_t kMatrixHeight = 19;
const uint8_t kBorderWidth = 1;

#define NUM_LEDS    (kMatrixWidth*kMatrixHeight)
CRGB leds_plus_safety_pixel[NUM_LEDS + 1];
CRGB *const leds(leds_plus_safety_pixel + 1);

// Color correction for the SmartMatrix
// #define COLOR_CORRECTION CRGB(255,110,178)

void setup() 
{
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop()
{
  // Apply some blurring to whatever's already on the matrix
  // Note that we never actually clear the matrix, we just constantly
  // blur it repeatedly.  Since the blurring is 'lossy', there's
  // an automatic trend toward black -- by design.
  uint8_t blurAmount = beatsin8(2,10,255);
  blur2d( leds, kMatrixWidth, kMatrixHeight, blurAmount);

  // Use two out-of-sync sine waves
  uint8_t  i = beatsin8( 27, kBorderWidth, kMatrixHeight-kBorderWidth);
  uint8_t  j = beatsin8( 41, kBorderWidth, kMatrixWidth-kBorderWidth);
  // Also calculate some reflections
  uint8_t ni = (kMatrixWidth-1)-i;
  uint8_t nj = (kMatrixWidth-1)-j;
  
  // The color of each point shifts over time, each at a different speed.
  uint16_t ms = millis();  
  leds[XY( i, j)] += CHSV( ms / 11, 200, 255);
  leds[XY( j, i)] += CHSV( ms / 13, 200, 255);
  leds[XY(ni,nj)] += CHSV( ms / 17, 200, 255);
  leds[XY(nj,ni)] += CHSV( ms / 29, 200, 255);
  leds[XY( i,nj)] += CHSV( ms / 37, 200, 255);
  leds[XY(ni, j)] += CHSV( ms / 41, 200, 255);
  
  FastLED.show();
}

// Trivial XY function for the SmartMatrix; use a different XY 
// function for different matrix grids.  See XYMatrix example for code.
uint16_t XY( uint8_t x, uint8_t y) { return Hotel_H[x][y]; } //(y * kMatrixWidth) + x
/* 
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
} */
