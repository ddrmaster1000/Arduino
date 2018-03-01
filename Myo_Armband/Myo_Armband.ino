#include "LPD8806.h"

int nLEDs = 48;

// Chose 2 pins for output; can be any valid output pins:
int dataPin  = 6;
int clockPin = 5;
LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);
int val;
int arr[3];
int x, y, state;
int serialln = 0;
uint32_t color[3] = {0, 0, 0};
byte r, g, b = 10;
int xarr[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  strip.begin();
  strip.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available())
  { // If data is available to read,
    //   // read it and store it in val


    readIncomingBytes();
    if (state == 1 ) {
      twistBright();
    }
    else if ( state == 2) {
      colorChange();
    }
    else if (state == 3) {
      therapyy();
    }

  }
}


void readIncomingBytes() {
  while (Serial.available() > 0)
  {
    int incomingByte = Serial.read();
    if (incomingByte == (int)'<')
    {
      serialln = 0;

    }
    else if (incomingByte == (int)'>')
    {
      x = arr[0];
      y = arr[1];
      state = arr[2];
      return;
    }
    else
    {
      arr[serialln] = incomingByte;
      serialln++;
    }
  }
}


void twistBright() {
  x = x / 5;

  float floaty = (y / 5.0);
  if (x > nLEDs) {
    x = nLEDs;
  }
  for ( int i = 0; i < x; i++) {
    strip.setPixelColor(i, strip.Color(floaty * r, (floaty)*g, (floaty)*b)); // Set new pixel 'on'
  }
  for (int j = x; j < nLEDs; j++) {
    strip.setPixelColor(j, strip.Color(0, 0, 0)); // Set new pixel 'on'
  }
  strip.show();

}

void colorChange() {
  for ( int i = 0; i < nLEDs; i++) {
    strip.setPixelColor(i, Wheel(x)); // Set new pixel 'on'
  }
  strip.show();


}


uint32_t Wheel(uint16_t WheelPos)
{

  if (WheelPos > 0 && WheelPos < (190 / 3))
  {
    r = 0;
    g = 0;
    b = 10;
  }
  else if (WheelPos < (2 * 190 / 3))
  {
    r = 0;
    g = 10;
    b = 0;
  }
  else
  {
    r = 10;
    g = 0;
    b = 0;
  }
  return (strip.Color(r*5, g*5, b*5));
}

void therapyx()
{
  if (x > 38 && x < 180)
  {
    r = 0;
    g = 10;
    b = 0;
  }
  else
  {
    r = 10;
    g = 0;
    b = 0;
  }
    x = x / 5;
  if (x > nLEDs) {
    x = nLEDs;
  }
  for ( int i = 0; i < x; i++) {
    strip.setPixelColor(i, strip.Color(5*r, 5*g, 5*b)); // Set new pixel 'on'
  }
  for (int j = x; j < nLEDs; j++) {
    strip.setPixelColor(j, strip.Color(0, 0, 0)); // Set new pixel 'on'
  }
  strip.show();
}


void therapyy()
{
  if (y > 12 && y < 40)
  {
    r = 0;
    g = 10;
    b = 0;
  }
  else
  {
    r = 10;
    g = 0;
    b = 0;
  }

  if (y < 0) {
    y = 0;
  }
  for ( int i = 0; i < y; i++) {
    strip.setPixelColor(i, strip.Color(5*r, 5*g, 5*b)); // Set new pixel 'on'
  }
  for (int j = y; j < nLEDs; j++) {
    strip.setPixelColor(j, strip.Color(0, 0, 0)); // Set new pixel 'on'
  }
  strip.show();
}

