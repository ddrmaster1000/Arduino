#include "LPD8806.h"
#include "SPI.h" // Comment out this line if using Trinket or Gemma
#ifdef __AVR_ATtiny85__
 #include <avr/power.h>
#endif




int nLED = 124;

int dataPin = 2;
int clockPin = 3;

LPD8806 strip = LPD8806(nLED, dataPin, clockPin);

void setup(){
  strip.begin(); //start running the strip
  strip.show(); //show strip
}

void loop(){
  int i;
  int k;
  byte red = random(1,256); 
  byte green = random(1,256); 
  byte blue = random(1,256);
  byte rand = 1;

  
  for(i=0; i<strip.numPixels(); i++){ //for loop turns on the LED's one by one
  
  byte randomnum = random(1,4);  //randomizes the colors of the LED's
  switch (randomnum){
    case 1:
      red = red + random(30,150);
      red = red % 255;
    break;
    
    case 2:
      green = green + random(30,150);
      green = green % 255; 
    break;
    
    case 3:
      blue = blue + random(30,150);
      blue = blue % 255;  
    break; 
  }  
  /*
  //Create an Array that stores a random number, checks to see if that number has been chosen, if so it will create another number, check itself and if it is good, it will give the value to make an led change color. 
  for(i = 0; i<99; i++){
    int arraycheck[100];//numbers 0-99
    arraycheck[i] = 100;
  
  
  }
  for(int makenum = 0; makenum < 99; makenum++){
    
    arraycheck[makenum] = random(0,strip.numPixels());
    for(int check = 0; check < 99; check++){
        for(int doublecheck = 1; doublecheck < 99; doublecheck++){
          if(arraycheck[doublecheck] == arraycheck[check]){
            makenum--;       
            
          }
     
        }
      
    }
  */
  
  }
  
  
  
    strip.setPixelColor(random(0,strip.numPixels()),red,green,blue); // Sets the color of the pixels; choose random(0,strip.numPixels()) OR i depending on how you want the leds to light up. random(0,strip.numPixels()) = random, i= 1 by one;
    strip.show();
    delay(10); //how long to wait to go onto the next led
    

    /*
      if(i==strip.numPixels()-1){
       for(k=0; k<strip.numPixels(); k++){ // (turns off all of the LED's 
         strip.setPixelColor(k,0);
      } 
    }

  }
  */
}




    
    
    
    
    
    
  


