#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "LPD8806.h"
#include "SPI.h" // Comment out this line if using Trinket or Gemma
#ifdef __AVR_ATtiny85__
 #include <avr/power.h>
#endif


int drum = 2;         //Change this variable depending on the drum start at 0
int offset =20 * drum;
int nLEDs = 180;


RF24 radio(8, 9);

const byte rxAddr[6] = "00001";

int dataPin  = 7;
int clockPin = 6;
LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);
volatile int pattern = 0;
int num = 0;
volatile int quit = 0;
int flag = 0;
int parity = 0;


void setup(){
  
  attachInterrupt(0, interrupt, FALLING);
  strip.begin();
  strip.show();
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, rxAddr);
  radio.startListening();
  randomSeed(analogRead(0));
}

void interrupt(){
  char text[6] = {0};
  radio.read(&text, sizeof(text));
  String str(text);
  num = str.toInt();
  Serial.println(num);

  if(num != pattern){
    pattern = num;
    quit = 1;
    parity = 0;
  }
  
}

int led_array[] = {0,0,0,0,0,0};
int prev_led[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int j, i;
int count = 0;
int random_num= random(0,12);

int red = (0,255,0);
int blue = (255,0,0);
int green = (0,0,255);
int three_colors[] = {red,blue,green};

void loop(){
  switch(pattern){
    case 0:
     colorWipe(strip.Color(127, 0, 0), 30);
      break;
    case 1:
      rainbowCycle(0);  
      break;
    case 2:
      parity = 0;
      colorChase(strip.Color(127, 127, 0), 40);
      break;
    case 3:
      cycloneScroll();
      break;
    case 4:
      flashRandom();
      break;
    case 5:
      colorWipeRandom(30);
      break;
    case 6:
      theaterChase(strip.Color(127,   50,   50), 50);
      break;
    case 7:
      colorChaseThree(strip.Color(50,   70,   80), 35);
      break;
    case 8:
      colorWipe(strip.Color(100, 50, 0), 30);
      break;
    case 9:
      theaterChaseRainbow(50);
      break;
    case 10:
      colorWipe(strip.Color(random(128), random(128), random(128)), 30);
      break;
    case 11:
      random_leds();
      break;
    case 12:
      colorChaseThreeOneDrum(strip.Color(127,   0,   127), 45);
      break;
    default:
      stripClear;
      break;
  }
}

void random_leds(){
    quit = 0;
random_num = random(0,20);
int random_384 = random(50,384);

if(quit == 0){
if(1 == prev_led[random_num]){
  random_leds();

}
  else{
     prev_led[random_num] = 1;
     strip.setPixelColor(random_num, Wheel(random_384));
     strip.show(); 
     delay(100);
  
  for (i = 0; i < 20; i++){
    if (prev_led[i] == 1) {
      count++;
    }
   }
   if (count == 20){
        delay(100);
      for (i= 0; i < 20; i++){
       prev_led[i] = 0;
      strip.setPixelColor(i, 0);
  strip.show(); 
  delay(25);
      }
   }
   else{
  count = 0;
   }
  }
  }
    else if(quit == 1){
      stripClear();
      return;
    }
}
/*
void pixel_switch(){
  quit = 0;
  if(quit == 0){
    if(drum >= 0 && <= 3){
       for (i=0; i < (strip.numPixels() / 2) + 20; i++) {
          strip.setPixelColor(i - offset, 100, 150, 50);
          strip.show();
          delay(50);
        
       }
    else if(drum >= 5 && <= 8){
           for (i=strip.numPixels; i > (strip.numPixels()/2) + 20 ; i--) {
          strip.setPixelColor(i + offset, 200, 100, 200);
          strip.show();
          delay(50);
       }
       else if(drum == 4){
        for( i = offset
          strip.setPixelColor(i, 127, 80, 50);
          strip.show();
        
       }
      
    }
  }
  }
      else if(quit == 1){
      stripClear();
      return;
    }
  



  

}
*/



/*void cycloneScroll(){
  quit = 3;
  parity++; 
  parity = parity % 2;

  if(drum < 3){
    do{stripClear();}while(0);
    for (int i = 0; i < strip.numPixels(); i++) {
      if(quit == 0){
        if(parity == 0){strip.setPixelColor(i - offset, 127, 0, 0);}
        else      {strip.setPixelColor(i - offset, 100, 50, 0);}
        strip.show();
        delay(10);
      }
      else{
        stripClear();
        return;
      }
    }
  }
  else if(drum > 5){
     do{stripClear();}while(0);
     for (int i=0; i < strip.numPixels(); i++) {
      if(quit == 0){
        if(parity == 0){strip.setPixelColor(i - offset + 120, 127, 0, 0);}
        else      {strip.setPixelColor(i - offset + 120, 100, 50, 0);}
        strip.show();
        delay(10);
      }
      else{
        stripClear();
        return;
      }
    }
  }
  else if (drum > 2 && drum < 6){
    do{stripClear();}while(0);
    for (int i=0; i < strip.numPixels(); i++){
      if(quit == 0){
        if(parity == 0){strip.setPixelColor(i - offset + 60, 100, 50, 0);}
        else      {strip.setPixelColor(i - offset + 60, 127, 0, 0);}
        strip.show();
        delay(10);
      }
      else{
        stripClear();
        return;
      }
    }
  } 
}*/


void cycloneScroll(){
  quit = 0;
  parity++; 
  parity = parity % 2;

  if(drum < 3){
    do{stripClear();}while(0);
    for (int i = 0; i < strip.numPixels(); i++) {
      if(quit == 0){
        if(parity == 0){strip.setPixelColor(i - offset, 127, 0, 0);}
        else      {strip.setPixelColor(i - offset, 100, 50, 0);}
        strip.show();
        delay(10);
      }
      else{
        stripClear();
        return;
      }
    }
  }
  else if (drum == 3 || drum == 4 || drum == 5){
    do{stripClear();}while(0);
    for (int i=0; i < strip.numPixels(); i++) {
      if(quit == 0){
        if(parity == 0){strip.setPixelColor(i - offset + 60, 100, 50, 0);}
        else      {strip.setPixelColor(i - offset + 60, 127, 0, 0);}
        strip.show();
        delay(10);
      }
      else{
        stripClear();
        return;
      }
    }
  }
    else if(drum > 5){
     for (int i=0; i < strip.numPixels(); i++) {
      if(quit == 0){
        if(parity == 0){strip.setPixelColor(i - offset + 120, 127, 0, 0);}
        else      {strip.setPixelColor(i - offset + 120, 100, 50, 0);}
        strip.show();
        delay(10);
      }
      else{
        stripClear();
        return;
      }
    }
  } 
}



// Fill the dots progressively along the strip.
void colorWipe(uint32_t c, uint8_t wait) {
  int i;
  quit = 0;

  do{stripClear();} while(0);
  for (i=0; i < strip.numPixels() + 20; i++) {
    if(quit == 0){
    strip.setPixelColor(i-offset, c);
    strip.show();
    delay(wait);
    }
    else if(quit == 1){
      stripClear();
      return;
    }
  }
}


void colorWipeRandom(uint8_t wait) {
  int i;
  quit = 0;

  do{stripClear();} while(0);
  for (i=0; i < strip.numPixels() + 20; i++) {
    if(quit == 0){
    strip.setPixelColor(i-offset, strip.Color(random(128), random(128), random(128)));
    strip.show();
    delay(wait);
    }
    else if(quit == 1){
      stripClear();
      return;
    }
  }
}


void colorChase(uint32_t c, uint8_t wait) {
  int i;
  quit = 0;
  
  for(i=0; i<strip.numPixels(); i++) {
    if(quit == 0){
      strip.setPixelColor(i-offset, c); // Set new pixel 'on'
      strip.show();              // Refresh LED states
      strip.setPixelColor(i-offset, 0); // Erase pixel, but don't refresh!
      delay(wait);
    }
    else{
      stripClear();
    return;
    } 
  }

  strip.show(); // Refresh to turn off last pixel
}


void colorChaseThree(uint32_t c, uint8_t wait) {
  int i;
  quit = 0;
  
  for(i=0; i < strip.numPixels(); i++) {
    if(quit == 0){
      strip.setPixelColor(i - offset, c); // Set new pixel 'on'
      strip.setPixelColor(i - offset - 1, c);
      strip.setPixelColor(i - offset - 2, c);
      strip.setPixelColor(i - offset - 3, 0); // Erase pixel, but don't refresh!
      strip.show();              // Refresh LED states
      delay(wait);
    }
    else{
      stripClear();
    return;
    } 
  }

  strip.show(); // Refresh to turn off last pixel
}


void colorChaseThreeOneDrum(uint32_t c, uint8_t wait) {
  int i;
  quit = 0;
  
  for(i=0; i < 23; i++) {
    if(quit == 0){
      strip.setPixelColor(i, c); // Set new pixel 'on'
      strip.setPixelColor(i - 1, c);
      strip.setPixelColor(i - 2, c);
      strip.setPixelColor(i - 3, 0); // Erase pixel, but don't refresh!
      strip.show();              // Refresh LED states
      delay(wait);
    }
    else{
      stripClear();
    return;
    } 
  }

  strip.show(); // Refresh to turn off last pixel
}


//Flash random colors on the strip
void flashRandom(){
  int i;
  int r = 0;
  int g = 0;
  int b = 0;
  quit = 0;
  
  stripClear();

//  delay(random(80,120));
    
  switch(random(0,4)){
    case 0: // Red
      r = 127;
      g = 0;
      b = 0;
      break;
    case 1: // Green
      r = 0;
      g = 127;
      b = 0;
      break;
    case 2: // Blue
      r = 0;
      g = 0;
      b = 127;
      break;
    case 3: //White
      r = 127;
      g = 127;
      b = 127;
      break;
  }
  
  // set pixel colors
  for (i=0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, r, g, b); 
  }
  
  strip.show(); 
  delay(random(100, 170));

  if(quit){
    stripClear();
    return;
  }
}


void theaterChase(uint32_t c, uint8_t wait) {
  quit = 0;
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      if(quit == 0){
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, c);    //turn every third pixel on
        }
        strip.show();
      
        delay(wait);
      
        for (int i=0; i < strip.numPixels(); i += 3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
      }
      else{
        stripClear();
        return;
      }
    }
  }
}


void theaterChaseRainbow(uint8_t wait) {
  quit = 0;
  for (int j=0; j < 384; j+=5) {     // cycle all 384 colors in the wheel
    for (int q=0; q < 3; q++) {
      if(quit == 0){
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 384));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
      }
      else{
        stripClear();
        return;
      }
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

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  quit = 0;
  for (j=0; j < 384 * 5; j++) {     // 5 cycles of all 384 colors in the wheel
          if(quit == 0){
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 384-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 384 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i  * 384 / strip.numPixels()) + (j + offset)) % 384) );
    }  
    
    strip.show();   // write all the pixels out
    delay(wait);
          }
      else{
        stripClear();
        return;
      }
  }
}


void stripClear(){
  for(int i = 0; i < strip.numPixels(); i++){
    strip.setPixelColor(i, strip.Color(0,0,0));
  }
  strip.show();
}

