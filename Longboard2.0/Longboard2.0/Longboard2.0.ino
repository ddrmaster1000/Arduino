#include "LPD8806.h"
#include "SPI.h"
#include "SoftwareSerial.h"

// Simple test for 160 (5 meters) of LPD8806-based RGB LED strip
// Not compatible with Trinket/Gemma due to limited RAM

/*****************************************************************************/

// Number of RGB LEDs in strand:
int nLEDs = 20;

// Chose 2 pins for output; can be any valid output pins:
int dataPinLeft  = 2;
int clockPinLeft = 3;

int dataPinRight  = 4;
int clockPinRight = 5;

// First parameter is the number of LEDs in the strand.  The LED strips
// are 32 LEDs per meter but you can extend or cut the strip.  Next two
// parameters are SPI data and clock pins:
LPD8806 stripLeft = LPD8806(nLEDs, dataPinLeft, clockPinLeft);
LPD8806 stripRight = LPD8806(nLEDs, dataPinRight, clockPinRight);

// You can optionally use hardware SPI for faster writes, just leave out
// the data and clock pin parameters.  But this does limit use to very
// specific pins on the Arduino.  For "classic" Arduinos (Uno, Duemilanove,
// etc.), data = pin 11, clock = pin 13.  For Arduino Mega, data = pin 51,
// clock = pin 52.  For 32u4 Breakout Board+ and Teensy, data = pin B2,
// clock = pin B1.  For Leonardo, this can ONLY be done on the ICSP pins.
//LPD8806 strip = LPD8806(nLEDs);

void setup() {
  // Start up the LED strip
  stripLeft.begin();
  stripRight.begin();

  // Update the strip, to start they are all 'off'
  stripLeft.show();
  stripRight.show();
}

void loop() {
//  colorChase(strip.Color(127,  0,  0), 100); // Red
  //colorChase(strip.Color(  0,127,  0), 100); // Green
 // colorChase(strip.Color(  0,  0,127), 100); // Blue
 // colorChase(strip.Color(127,127,127), 100); // White



leftturn(100);
//rightturn(100);
//brake(100);
//off();
//singleled(num,r,g,b);

}

void setall(short r, short g, short b){
      int i;
  for(i=0; i<nLEDs; i++) {
    stripLeft.setPixelColor(i,r,g,b); // Set new pixel 'on'
    stripRight.setPixelColor(i,r,g,b); // Set new pixel 'on'
  }
  stripLeft.show();
  stripRight.show();
}


void singleled(short num, short r, short g, short b){
  stripLeft.setPixelColor(num,r,g,b);
  stripRight.setPixelColor(num,r,g,b);
}



void off(){
    int i;
  for(i=0; i<nLEDs; i++) {
    stripRight.setPixelColor(i, 0); // Set new pixel 'off'
    stripLeft.setPixelColor(i, 0); // Set new pixel 'off'
  }
  stripLeft.show();
  stripRight.show();
}

void brake(short wait){
  int i;
  for(i=0; i<=nLEDs; i++) {
    stripLeft.setPixelColor(i, 127,0,0); // Set new pixel 'on'
    stripRight.setPixelColor(i, 127,0,0); // Set new pixel 'on'
    stripLeft.show();  // Refresh LED states
    stripRight.show(); // Refresh LED states
  }
delay(wait+200);
  for(i=0; i<=nLEDs; i++) {
    stripLeft.setPixelColor(i, 0); // Set new pixel 'on'
    stripRight.setPixelColor(i, 0); // Set new pixel 'on'
    stripLeft.show();              // Refresh LED states
    stripRight.show();            // Refresh LED states
  }
delay(wait);
}

void leftturn(short wait){
  byte i;
  for(i=0; i<=nLEDs; i++) {
    stripLeft.setPixelColor(i, 127,0,0); // Set new pixel 'on'
    stripLeft.show();              // Refresh LED states
  }
delay(100+200);
  for(i=0; i<=nLEDs; i++) {
    stripLeft.setPixelColor(i, 0); // Set new pixel 'on'
    stripLeft.show();              // Refresh LED states
  }
delay(100);
}

void rightturn(short wait){
  byte i;
  for(i=0; i<=nLEDs; i++) {
    stripRight.setPixelColor(i, 127,0,0); // Set new pixel 'on'
    stripRight.show();              // Refresh LED states
  }
delay(100+200);
  for(i=0; i<=nLEDs; i++) {
    stripRight.setPixelColor(i, 0); // Set new pixel 'on'
    stripRight.show();              // Refresh LED states
  }
delay(100);
}

















/*
// Chase one dot down the full strip.  Good for testing purposes.
void colorChase(uint32_t c, uint8_t wait) {
  int i;
  
  // Start by turning all pixels off:
  for(i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, 0);
  strip2.setPixelColor(i, 0);

  // Then display one pixel at a time:
  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c); // Set new pixel 'on'
    strip2.setPixelColor(i, c);
    strip.show();  
    strip2.show(); // Refresh LED states
    strip.setPixelColor(i, 0);
    strip2.setPixelColor(i, 0);// Erase pixel, but don't refresh!
    delay(wait);
  }

  strip.show();
  strip2.show();// Refresh to turn off last pixel
}

*/
