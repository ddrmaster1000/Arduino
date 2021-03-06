/*
 Fade

 This example shows how to fade an LED on pin 9
 using the analogWrite() function.

 The analogWrite() function uses PWM, so if
 you want to change the pin you're using, be
 sure to use another PWM capable pin. On most
 Arduino, the PWM pins are identified with 
 a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

 This example code is in the public domain.
 */
signed int val = 0;

int led = 9;           // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
int unfilt_num = 0;
int output = 0;

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // set the brightness of pin 9:

  if (Serial.available()) 
   { // If data is available to read,
     val = Serial.read()*10; // read it and store it in val


 
     output = 250 * (val / 1800.0);
     if(val < 0){
      output = 0;
     }
     analogWrite(led, output);
     

   delay(10);


   /*
    if(val<600)
      val=20;
    else if(val<1200)
      val=100;
    else 
      val=255;
     analogWrite(led, val);
   delay(10);
   */
     
   }
  /*
  analogWrite(led, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
*/
  
}
