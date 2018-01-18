#include "LPD8806.h"

int nLEDs = 18;

int analogPin = 3;
float val_hall = 0;
byte north = '0';

//int r_dataPin = 3;
//int r_clockPin = 4;
//int l_dataPin = 5;
//int l_clockPin = 6;


int r_dataPin = 2;
int r_clockPin = 3;
int l_dataPin = 4;
int l_clockPin = 5;

int k = 0;
int i = 0;
long time_1;
long time_2;
long time_final = 70.179;
float velocity = 0;
long led_count = 0;
bool flag = 0;

LPD8806 r_strip = LPD8806(nLEDs, r_dataPin, r_clockPin);
LPD8806 l_strip = LPD8806(nLEDs, l_dataPin, l_clockPin);


void setup() {
  attachInterrupt(0, interrupt, RISING);
  r_strip.begin();
  r_strip.show();
  l_strip.begin();
  l_strip.show();
  Serial.begin(9600);
}

void interrupt(){
  
  
}

void loop() {
  val_hall = analogRead(analogPin) * (5.0 / 1024.0);
  Serial.print(velocity);

  if (val_hall >= .3 && north == '0') {
    north = '1';
    k++;
    time_1 = millis();
    led_count++;
  } else if (val_hall < .3 && north == '1') {
    north = '0';
    k++;
    time_2 = millis();
    time_final = abs(time_1 - time_2);

    velocity = 70.179 / time_final;
    led_count++;

  }
  Serial.println(velocity);
  
  if (k >= nLEDs) { //restart the count of LEDs
    k = 0;
  }

  if (velocity <= 7) { // testing values: 3, 5. Riding values 5, 10
   // next_pixel();
   rainbow_next_pixel();
   //zigzag();

  }
  else if(velocity > 7.5 && velocity < 15){
    light_speed(velocity);
  }
  else{
    rainbow_speed(velocity);
  }
}


void leap_frog(){
    r_strip.setPixelColor(k-1, 0);                                         //set pixel color to the next pixel.
    l_strip.setPixelColor(k-1, 0);
    
    if(k%2){
    l_strip.setPixelColor(k, 0,255,0);  
    l_strip.setPixelColor(k+1, 255,255,0); 
    r_strip.setPixelColor(k, 255,40,0);
  }

  if(k%2 == 0){
    l_strip.setPixelColor(k+1, 0,255,0);  
    l_strip.setPixelColor(k, 255,255,0);
    r_strip.setPixelColor(k+1, 0,255,0);                                         //set pixel color to the next pixel.
  }
  if(k == 0){
     r_strip.setPixelColor(nLEDs-1, 0);                                         //set pixel color to the next pixel.
     l_strip.setPixelColor(nLEDs-1, 0);
  }
  r_strip.show();
  l_strip.show();
}


void zigzag(){
  if(k%2){
    l_strip.setPixelColor(k+1, 0,255,0);                                         //set pixel color to the next pixel.
    r_strip.setPixelColor(k, 255,40,0);
  }

  if(k%2 == 0){
    r_strip.setPixelColor(k+1, 0,255,0);                                         //set pixel color to the next pixel.
    l_strip.setPixelColor(k, 255,40,0);
  }
    r_strip.setPixelColor(k-1, 0);                                         //set pixel color to the next pixel.
    l_strip.setPixelColor(k-1, 0);
  if(k == 0){
     r_strip.setPixelColor(nLEDs-1, 0);                                         //set pixel color to the next pixel.
     l_strip.setPixelColor(nLEDs-1, 0);
  }
  r_strip.show();
  l_strip.show();
}

void rainbow_next_pixel(){
    r_strip.setPixelColor(k, Wheel(((k * 384 / l_strip.numPixels()) + (led_count%384)%2) % 384, l_strip));                                         //set pixel color to the next pixel.
    l_strip.setPixelColor(k, Wheel(((k * 384 / r_strip.numPixels()) + (led_count%384)%2) % 384, r_strip));
    r_strip.setPixelColor(k-1, 0);                                         //set pixel color to the next pixel.
    l_strip.setPixelColor(k-1, 0);
  if(k == 0){
     r_strip.setPixelColor(nLEDs-1, 0);                                         //set pixel color to the next pixel.
     l_strip.setPixelColor(nLEDs-1, 0);

//     //the following makes a led jump to the front of the led strip
//     if(flag == 0){
//             for(i = nLEDs; i>0; i--){
//      r_strip.setPixelColor(i, Wheel(((i * 384 / l_strip.numPixels()) + (led_count%384)%2) % 384, l_strip));                                         //set pixel color to the next pixel.
//      l_strip.setPixelColor(i, Wheel(((i * 384 / r_strip.numPixels()) + (led_count%384)%2) % 384, r_strip));
//      delay(3);
//        r_strip.setPixelColor(i+1, 0);                                         //set pixel color to the next pixel.
//        l_strip.setPixelColor(i+1, 0);
//        r_strip.show();
//        l_strip.show();
//     }
//       for(i=0;i<nLEDs;i++){
//        r_strip.setPixelColor(i, 0);                                         //set pixel color to the next pixel.
//        l_strip.setPixelColor(i, 0);
//       }
//       flag = 1;
//     }
//  }
//  else(flag = 0);

  }
  r_strip.show();
  l_strip.show();

}


void next_pixel() {
  for (i = 0; i < r_strip.numPixels(); i++) {
    r_strip.setPixelColor(i, 0); //clear strips to start
  }
  for (i = 0; i < l_strip.numPixels(); i++) {
    l_strip.setPixelColor(i, 0);
  }
  r_strip.setPixelColor(k, 240);                                         //set pixel color to the next pixel.
  l_strip.setPixelColor(k, 240);
  l_strip.show();
  r_strip.show();
}

void light_speed(float velocity) {
  
  for (int i = 0; i < l_strip.numPixels() && i < r_strip.numPixels(); ++i) {
    if (velocity -4 > i) {
      l_strip.setPixelColor(i, 250, i * 2, 0);
      r_strip.setPixelColor(i, 250, i * 2, 0);
    } else {
      l_strip.setPixelColor(i, 0);
      r_strip.setPixelColor(i, 0);
    }
  }

  r_strip.show();
  l_strip.show();
}

void rainbow_speed(float velocity) {
   for (i = 0; i < r_strip.numPixels(); i++) {
    r_strip.setPixelColor(i, 0); //clear strips to start
  }
  for (i = 0; i < l_strip.numPixels(); i++) {
    l_strip.setPixelColor(i, 0);
  }
  if(i%10==0){
    r_strip.setPixelColor(k, Wheel(((k * 384 / l_strip.numPixels()) + (led_count%384)) % 384, l_strip));                                         //set pixel color to the next pixel.
  l_strip.setPixelColor(k, Wheel(((k * 384 / r_strip.numPixels()) + (led_count%384)) % 384, r_strip));
     r_strip.setPixelColor(k+1, Wheel(((k+1 * 384 / l_strip.numPixels()) + (led_count%384)) % 384, l_strip));                                         //set pixel color to the next pixel.
  l_strip.setPixelColor(k+1, Wheel(((k+1 * 384 / r_strip.numPixels()) + (led_count%384)) % 384, r_strip));
    r_strip.setPixelColor(k+2, Wheel(((k+2 * 384 / l_strip.numPixels()) + (led_count%384)) % 384, l_strip));                                         //set pixel color to the next pixel.
  l_strip.setPixelColor(k+2, Wheel(((k+2 * 384 / r_strip.numPixels()) + (led_count%384)) % 384, r_strip));
    r_strip.setPixelColor(k+3, Wheel(((k+3 * 384 / l_strip.numPixels()) + (led_count%384)) % 384, l_strip));                                         //set pixel color to the next pixel.
  l_strip.setPixelColor(k+3, Wheel(((k+3 * 384 / r_strip.numPixels()) + (led_count%384)) % 384, r_strip));
      r_strip.setPixelColor(k+4, Wheel(((k+4 * 384 / l_strip.numPixels()) + (led_count%384)) % 384, l_strip));                                         //set pixel color to the next pixel.
  l_strip.setPixelColor(k+4, Wheel(((k+4 * 384 / r_strip.numPixels()) + (led_count%384)) % 384, r_strip));
  l_strip.show();
  r_strip.show();
  }
}
void rainbow(uint8_t wait) {
  int i, j;

  for (j = 0; j < 384; j++) {   // 3 cycles of all 384 colors in the wheel
    for (i = 0; i < l_strip.numPixels() && i < r_strip.numPixels(); i++) {
      l_strip.setPixelColor(i, Wheel((i + j) % 384, l_strip));
      r_strip.setPixelColor(i, Wheel((i + j) % 384, r_strip));
    }
    l_strip.show();   // write all the pixels out
    r_strip.show();   // write all the pixels out
    delay(wait);
  }
}

// Slightly different, this one makes the rainbow wheel equally distributed
// along the chain
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 384 * 5; j++) {   // 5 cycles of all 384 colors in the wheel
    for (i = 0; i < l_strip.numPixels() && i < r_strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 384-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 384 is to make the wheel cycle around
      l_strip.setPixelColor(i, Wheel(((i * 384 / l_strip.numPixels()) + j) % 384, l_strip));
      r_strip.setPixelColor(i, Wheel(((i * 384 / r_strip.numPixels()) + j) % 384, r_strip));
    }
    l_strip.show();   // write all the pixels out
    r_strip.show();   // write all the pixels out
    delay(wait);
  }
}

uint32_t Wheel(uint16_t WheelPos, LPD8806 strip) {
  byte r, g, b;
  switch (WheelPos / 128) {
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
  return (strip.Color(r, g, b));
}
