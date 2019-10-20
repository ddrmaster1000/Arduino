#include <CapacitiveSensor.h>
#include "LPD8806.h"
#include "SPI.h" // Comment out this line if using Trinket or Gemma


// Capacitance Setup
CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
long cap_value =  cs_4_2.capacitiveSensor(80);
int cap_threshold = 300;
int jump_count_total = 0;


// LED Strip Setup
// Number of RGB LEDs in strand:
int nLEDs = 23;
// Chose 2 pins for output; can be any valid output pins:
int dataPin  = 1;
int clockPin = 3;
LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);

// Function Check Array
//byte return_data[2];
//data[0] = 'f'; //Is there a Passing capacitance value
//data[1] = 'f';     //time elapsed during test

void setup()                    
{

   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
//   Serial.begin(115200);

  // Show LED Strip
  // Start up the LED strip
  strip.begin();
  // Update the strip, to start they are all 'off'
  strip.show();
}




void loop()                    
{
  bool cap_activates = check_sensor();
  if( cap_activates )
  {
    colorSpreadCenter(strip.Color(20,   0,   20), 100, 0); // Red
    cap_activates = false;
  }

}

bool check_sensor()
{
  //Check the sensor's value
  cap_value =  cs_4_2.capacitiveSensor(80);
  
  // Check one value to quickly check sensor
//  if(cap_value > cap_threshold)
//  {
    // Sensor is tripped
    // Collect an average of x readings to make sure they are real. 
    byte loop_num = 1;
    int running_value = 0;
    for(int i=0; i<loop_num; ++i)
    {
      running_value =  cs_4_2.capacitiveSensor(80);
    }

    // Is the value still above the threshold?
    if((running_value / loop_num) > cap_threshold)
    {
      //FOUND A REAL Positive
      return true;
    }
//  }

  else
  {
    return false;
  }
}





// Chase one dot down the full strip.
void colorSpreadCenter(uint32_t c, uint8_t wait, uint8_t starting_led) {
  ++jump_count_total;
  int i;
  int half_pixels = (strip.numPixels())/2;
  int total_time = 0;
  bool found_cap = false;

  // Rainbow it up every N jumps
  if(jump_count_total % 50 == 0)
  {
     rainbowCycle(0);  // make it go through the cycle fairly fast

     found_cap = check_sensor();
     while(found_cap)
     {
        found_cap = check_sensor();
        rainbowCycle(0);  // make it go through the cycle fairly fast
     }
     // Turn all the pixels off at the end of Rainbow mode
     for(i=0; i<=strip.numPixels(); i++){ strip.setPixelColor(i, 0);}
  }

  // NORMAL Increasing Operation
  // Then display one pixel at a time:
  for(i=starting_led; i<=half_pixels; i++) {
    strip.setPixelColor(half_pixels + i, c); // Set new pixel 'on'
    strip.setPixelColor(half_pixels - i, c); // Set new pixel 'on'
    strip.show();              // Refresh LED states

    // Double check the sensor while LEDs are Moving
    found_cap = check_sensor();
    if(!found_cap)
    {
      // Reverse Strip and Restart the Loop
      reverseTurnOffStrip(c, wait, i);
      return;
    }
  //  delay(25);
  }
  
  //Keep the led light on until the sensor is tripped 'off'
  found_cap = check_sensor();
  while(found_cap)
  {
//     rainbowCycle(0);  // make it go through the cycle fairly fast
     found_cap = check_sensor();
  }

  // We finally left the while loop because there was a negative number. 
  // Turn off the strip
  reverseTurnOffStrip(c, wait, i);

}



void reverseTurnOffStrip(uint32_t c, uint8_t wait, uint8_t currentLed)
{
  bool found_cap = false;
  
  // Turning all pixels off:
  int half_pixels = (strip.numPixels())/2;
  for(int i=currentLed; i>=0; i--) {
    strip.setPixelColor(half_pixels + i, 0); // Set new pixel 'on'
    strip.setPixelColor(half_pixels - i, 0); // Set new pixel 'on'
//
//      for(int i=currentLed; i>=-1; i=i-2) {
//    strip.setPixelColor(half_pixels + i, 0); // Set new pixel 'on'
//    strip.setPixelColor(half_pixels - i, 0); // Set new pixel 'on'
//    strip.setPixelColor(half_pixels + i+1, 0); // Set new pixel 'on'
//    strip.setPixelColor(half_pixels - i-1, 0); // Set new pixel 'on'
    
    strip.show();              // Refresh LED states
    // Double check the sensor while LEDs are Moving
    found_cap = check_sensor();
    if(found_cap)
    {
      // Reverse Strip and Restart the Loop
      colorSpreadCenter(c, wait, i);
      return;
    }
    
    delay(70);
  }
}


// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  
  for (j=0; j < 384 * 5; j++) {     // 5 cycles of all 384 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 384-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 384 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 384 / strip.numPixels()) + j) % 384) );
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
  for(i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, 0);
}

uint32_t Wheel(uint16_t WheelPos)
{
  byte r, g, b;
  switch(WheelPos / 128)
  {
    case 0:
      r = 127 - WheelPos % 128;   //Red down
      g = WheelPos % 128;      // Green up
      b = 0;                  //blue off
      break; 
    case 1:
      g = 127 - WheelPos % 128;  //green down
      b = WheelPos % 128;      //blue up
      r = 0;                  //red off
      break; 
    case 2:
      b = 127 - WheelPos % 128;  //blue down 
      r = WheelPos % 128;      //red up
      g = 0;                  //green off
      break; 
  }
  return(strip.Color(r,g,b));
}

 
