#include "LPD8806.h"
#include "SPI.h" 

int dataPin  = 2;
int clockPin = 3;

int nLEDs = 66;
int bluetooth = 0;
#define leftb  0
#define leftt  29
#define backb  30
#define backt  34
#define rightb  66
#define rightt  35

int velocity = 0;
short color=120;
short red, green, blue, led;
  
LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);


void setup() {
  strip.begin();
  strip.show();
 // Serial.begin(9600);

}



void loop() {

colorChase(strip.Color(127, 0, 0), 50, leftb, leftt, rightb, rightt); // Red   Light Rail
colorChase(strip.Color(127, 127, 0), 50, leftb, leftt, rightb, rightt); // Yellow

switch(bluetooth)
  case 0:
    for(int i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, 0); // Set new pixel 'on'
    strip.show();              // Refresh LED states
    } break;
    

    
  case 2: 
    leftturn(leftb, leftt, 100);
    break;
    
  case 3:
     rightturn(rightb, rightt, 100);
     break;
     
  case 4: 
    brake(backb, backt, 100); 
    break;
    
  case 5:
    caution(100);
    break;
    
  case 6:
    off();
    break;
    
  case 7:
    singleled(led, red, green, blue);
    break;

  case 8:
    setall(red, green, blue);
    break;
    
    
    
    
    
    
//     colorspeed(velocity, leftb, leftt, rightb, rightt, backb, backt, color);
 

    
    
    
    
    
     
}





/*
void colorspeed(short v,short bottoml,short topl,short bottomr,short topr,short bottomb,short bottomt,c){
  int count = 0;
  float tdistance;
  float instd = v*(.03/9600);
  distance = instd + distance;
  if(distance % .03){
    count = count +1;
    strip.setPixelColor(count-1, 0); // Erase pixel, but don't refresh!
    strip.setPixelColor(66-count+1, 0); // Erase pixel, but don't refresh!
    strip.setPixelColor(count, c); // Set new pixel 'on'
    strip.setPixelColor(66-count,c);
    strip.show();              // Refresh LED states
    
  }

}
*/


void colorChase(uint32_t c, uint8_t wait, short bottoml, short topl, short bottomr, short topr) {
  int i;

  // Start by turning all pixels off:
  for(i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, 0);

  // Then display one pixel at a time:
    for(i=bottoml; i<=topl; i++) {
    strip.setPixelColor(i, c); // Set new pixel 'on'
    strip.setPixelColor(66-i,c);
    strip.show();              // Refresh LED states
    strip.setPixelColor(i, 0); // Erase pixel, but don't refresh!
    strip.setPixelColor(66-i, 0); // Erase pixel, but don't refresh!
    delay(wait);
   }
}



void leftturn(short bottom,short top, short wait){
    int i;
  for(i=bottom; i<=top; i++) {
    strip.setPixelColor(i, 127,0,0); // Set new pixel 'on'
    strip.show();              // Refresh LED states
  }
delay(wait+200);
  for(i=bottom; i<=top; i++) {
    strip.setPixelColor(i, 0); // Set new pixel 'on'
    strip.show();              // Refresh LED states
  }
delay(wait);
}
  
  
void rightturn(short bottom,short top, short wait){
    int i;
  for(i=bottom; i>=top; i--) {
    strip.setPixelColor(i, 127,0,0); // Set new pixel 'on'
    strip.show();              // Refresh LED states
  }
delay(wait+200);
  for(i=bottom; i>=top; i--) {
    strip.setPixelColor(i, 0); // Set new pixel 'on'
    strip.show();              // Refresh LED states
  }
delay(wait);
}


void brake(short bottom,short top, short wait){
  int i;
  for(i=bottom; i<=top; i++) {
    strip.setPixelColor(i, 127,0,0); // Set new pixel 'on'
    strip.show();              // Refresh LED states
  }
delay(wait+200);
  for(i=bottom; i<=top; i++) {
    strip.setPixelColor(i, 0); // Set new pixel 'on'
    strip.show();              // Refresh LED states
  }
delay(wait);
}


void caution(short wait){
  int i;
  for(i=0; i<=strip.numPixels(); i++) {
    if(i%2){
    strip.setPixelColor(i, 127,0,0); // Set new pixel 'on'
             // Refresh LED states
    }
  }
      strip.show(); 
delay(wait+200);
  for(i=0; i<=strip.numPixels(); i++) {
    strip.setPixelColor(i, 0); // Set new pixel 'on'
             // Refresh LED states
  }
      strip.show(); 
delay(wait);
}

void off(){
    int i;
  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, 0); // Set new pixel 'on'
  }
  strip.show();
}

void singleled(short num, short r, short g, short b){
  strip.setPixelColor(num,r,g,b);
  
}

void setall(short r, short g, short b){
      int i;
  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i,r,g,b); // Set new pixel 'on'
  }
  strip.show();
}

