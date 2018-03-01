#include <CapacitiveSensor.h>
#include "LPD8806.h"

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */
int nLEDs = 12;
int dataPin = 5;
int clockPin = 6;
LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);
int low= 15;
int med =30;
int high =200;

CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_4_6 = CapacitiveSensor(4,6);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
CapacitiveSensor   cs_4_8 = CapacitiveSensor(4,8);        // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil

void setup()                    
{
   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);
   strip.begin();
   strip.show(); 
}

void loop()                    
{
  String state;
    long cap =  cs_4_2.capacitiveSensor(10);
   
    if(cap < low){
      state = "low";
      for(int i=0;i<nLEDs;i++){
      strip.setPixelColor(i,strip.Color(0,0,155));
      }
      strip.show();
    }
    if(cap > low+1 && cap < med){
            state = "med";
      for(int i=0;i<nLEDs;i++){
      strip.setPixelColor(i,strip.Color(0,155,0));
      }
      strip.show();
    }
    if(cap > high){
            state = "high";
      for(int i=0;i<nLEDs;i++){
      strip.setPixelColor(i,strip.Color(255,0,0));
      }
      strip.show();
      
    }


  Serial.println(state);


    
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


