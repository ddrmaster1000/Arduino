#include "LPD8806.h"


int nLEDs = 12;
int dataPin = 2;
int clockPin = 3;

LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);



void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show(); 
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

void loop() {
  // put your main code here, to run repeatedly:

  //rainbow(10);
//rainbowCycle(10);


random_leds();
//up_one();

}



void up_one() {
int counter_1 = 0;
int i = 0;
int random_384 = random(50,384);

for(i=12;i>0;i--){
   strip.setPixelColor(i, Wheel(random_384));
   strip.show(); 
   delay(300);
   counter_1++;
}
if( counter_1 == 11){
for(i=0;i<12;i++){
   strip.setPixelColor(i, 0);
   strip.show();
}
  counter_1 = 0;
}
  
}



void random_leds(){
  
random_num = random(0,20);
int random_384 = random(50,384);


if(1 == prev_led[random_num]){
  random_leds();

}

else{
   prev_led[random_num] = 1;
   strip.setPixelColor(random_num, Wheel(random_384));
   strip.show(); 
   delay(300);

for (i = 0; i < 12; i++){
  if (prev_led[i] == 1) {
    count++;
  }
 }
 if (count == 12){
      delay(275);
    for (i= 0; i < 12; i++){
     prev_led[i] = 0;
    strip.setPixelColor(i, 0);
strip.show(); 
delay(75);
    }
 }
 else{
count = 0;
 }
}
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



