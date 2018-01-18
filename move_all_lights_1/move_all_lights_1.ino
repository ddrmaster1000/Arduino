#include "LPD8806.h"
#include "SPI.h" // Comment out this line if using Trinket or Gemma
#ifdef __AVR_ATtiny85__
 #include <avr/power.h>
#endif




int nLED = 124;

int dataPin = 2;
int clockPin = 3;

LPD8806 strip = LPD8806(nLED, dataPin, clockPin);
//byte red = random(1,256); //randomizes the initial color for red
//    byte green = random(1,256); //green, etc.
//    byte blue = random(1,256);

void setup(){
  strip.begin(); //start running the strip
  strip.show(); //show strip
}

void loop(){
  int i;
  int k;
//  red+=random(1,25);red%=127;
//  green+=random(1,25);green%=127;
//  blue=127-red;
  
  byte rand = 1;
  byte red = random(1,90); //randomizes the initial color for red
    byte green = random(1,25); //green, etc.
    byte blue = 127-red;
  //wipe();
 
  for(i=0;i<strip.numPixels()/2;i+=2){    
    strip.setPixelColor(124/2-i-1,red,green,blue);
    strip.setPixelColor(124/2+i,red,green,blue);
    strip.show();
    
    }
//    red = random(1,90); //randomizes the initial color for red
//     green = 127-red; //green, etc.
//     blue = random(1,127);
    for(i=0;i<strip.numPixels()/2;i+=2){    
    strip.setPixelColor(i,127-red,green,127-blue);
    strip.setPixelColor(123-i,127-red,green,127-blue);
    strip.show();
    
    }
  
//  for(i=0; i<strip.numPixels(); i++){ //for loop turns on the LED's one by one
//  
//    byte randomnum = random(1,4); //chooses between the switches 1-3
//   /* if(rand == randomnum){ //if rand == randonum change randomnum by 1 so we don't go into the same switch case 2x.
//     randomnum++;
//    }
//    */
//  switch (randomnum){
//    case 1:
//      red = red + random(30,150);
//      red = red % 255;
//    break;
//    
//    case 2:
//      green = green + random(30,150);
//      green = green % 255; 
//    break;
//    
//    case 3:
//      blue = blue + random(30,150);
//      blue = blue % 255;  
//    break; 
//  }  
//  
//  //byte rand = randomnum;
//  
//    strip.setPixelColor(i,red,green,blue); // Sets the color of the pixels;
//    strip.show();
//    delay(1); //how long to wait to go onto the next led
//    
//    for(int j=0; j<strip.numPixels(); j++){ // for loop turns off all the LED's except the one turned on
//      strip.setPixelColor(j,0); //turns off LED
//      strip.show();
//    }
//    
//    
//      if(i==strip.numPixels()-1){
//       for(k=0; k<strip.numPixels(); k++){ // (turns off all of the LED's so pattern can continue on. once it reaches the end LED
//         strip.setPixelColor(k,0);
//         strip.show();
//      }
//    
//    }
//
//  }
  
}

void wipe(){
 for(int i=0;i<nLED ;i++){
   strip.setPixelColor(i,0);
 }
}

  
  


