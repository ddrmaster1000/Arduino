#include "LPD8806.h"
#include "SPI.h" 

int nLEDs = 240;

int dataPin  = 2;
int clockPin = 3;
LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);


void setup(){
  
strip.begin();
strip.show();


}

void loop(){

 // rainbow(.001);
  odd(100,0,0);
  even(0,0,200);
  odd(150,100,50);
  even(100,0,0);
  foward(200,0,0);
  reverse(200,50,0);
  foward(150,100,50);
  reverse(100,150,100);
  foward(50,100,150);
  reverse(0,0,50);
   
  // Send a simple pixel chase in...
  colorChase(strip.Color(127, 127, 127), 10); // White
  colorChase(strip.Color(127,   0,   0), 10); // Red
  colorChase(strip.Color(127, 127,   0), 10); // Yellow
  colorChase(strip.Color(  0, 127,   0), 10); // Green
  colorChase(strip.Color(  0, 127, 127), 10); // Cyan
  colorChase(strip.Color(  0,   0, 127), 10); // Blue
  colorChase(strip.Color(127,   0, 127), 10); // Violet

  // Send a theater pixel chase in...
  theaterChase(strip.Color(127, 127, 127), 100); // White
  theaterChase(strip.Color(127,   0,   0), 100); // Red
  theaterChase(strip.Color(127, 127,   0), 100); // Yellow
  theaterChase(strip.Color(  0, 127,   0), 100); // Green
  theaterChase(strip.Color(  0, 127, 127), 100); // Cyan
  theaterChase(strip.Color(  0,   0, 127), 100); // Blue
  theaterChase(strip.Color(127,   0, 127), 100); // Violet

  // Fill the entire strip with...
  colorWipe(strip.Color(127,   0,   0), 20);  // Red
  colorWipe(strip.Color(  0, 127,   0), 20);  // Green
  colorWipe(strip.Color(  0,   0, 127), 20);  // Blue

  rainbow(10);
 // rainbowCycle(0);  // make it go through the cycle fairly fast
  theaterChaseRainbow(100);

}


void foward(int r, int g, int b){
 int i;
  for(i = 0; i<strip.numPixels(); i++){
   strip.setPixelColor(i,r,g,b); 
   strip.show();
  }

 
  
  
}

void reverse(int r, int g, int b){  
 int j;
   for(j = strip.numPixels(); j>=0; j--){
    strip.setPixelColor(j,r,g,b); 
    strip.show();
   }
}

void odd(int r, int g, int b){
  int i;
   for(i = 0; i<strip.numPixels(); i++){
     if(i%2 == 1){
       strip.setPixelColor(i,r,g,b);
       strip.show();
       delay(20);
      }
   }
 }

void even(int r, int g, int b){
  int i;
   for(i = 0; i<strip.numPixels(); i++){ 
      if(i%2 == 0){
       strip.setPixelColor(i,r,g,b);
       strip.show();
       delay(20);
  }
 }
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



void rainbow(uint8_t wait) {
  int i, j;
   
  for (j=0; j < 384; j++) {     // 3 cycles of all 384 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 384));
    }  
    strip.show();   // write all the pixels out
    delay(wait);
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
}

// Fill the dots progressively along the strip.
void colorWipe(uint32_t c, uint8_t wait) {
  int i;

  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

// Chase one dot down the full strip.
void colorChase(uint32_t c, uint8_t wait) {
  int i,j;

  // Start by turning all pixels off:
  for(i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, 0);
    
  // Then display one pixel at a time:
  for(i=0; i<strip.numPixels(); i++) {
    // for(j=0; j<strip.numpixels(); j++)
    strip.setPixelColor(i, c); // Set new pixel 'on'
    //strip.settPixelColor(j,c);
    strip.show();              // Refresh LED states
   // strip.setPixelColor(j,0);
    strip.setPixelColor(i, 0); // Erase pixel, but don't refresh!
    delay(wait);
  }

  strip.show(); // Refresh to turn off last pixel
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
       
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 384; j++) {     // cycle all 384 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 384));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}
/* Helper functions */

//Input a value 0 to 384 to get a color value.
//The colours are a transition r - g -b - back to r

