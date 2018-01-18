
signed int val = 0;

int led = 9;           // the PWM pin the LED is attached to
byte red_p = 3;
byte green_p = 5;
byte blue_p = 6;

unsigned int red = 0;
unsigned int green = 0;
unsigned int blue = 0;

int unfilt_num = 0;
int output = 0;
byte once = 0;

int switch_val = 2;

int mavg[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // set the brightness of pin 9:
  int var=45; //changes with person
  if (Serial.available()) 
   { // If data is available to read,
  //   // read it and store it in val

 switch (switch_val){
  case 0:
   for(int i=0; i<19; i++)
   {
      mavg[i]=mavg[i+1];
   }
    mavg[19]=Serial.read();
  
    for(int j=0; j<20; j++)
    {
      val+=mavg[j];
    }
    val/=20;

    if(val < (var/2)){
      red = 255*((var/2)-val+5)/(var/2);
      green = 255*(val-5)/(var/2);
      blue = 0;
    }
    else{
      red = 0;
      blue = 255* (val-(var/2))/(var/2);
      green = 255* (var-val)/(var/2);
    }


   analogWrite(blue_p, blue);
   analogWrite(green_p, green);
   analogWrite(red_p, red);
   delay(3);
   break;

   case 1:
    //Steve's Values
    val = Serial.read(); 
    if(val>= 35){
      val=255;
     analogWrite(led, val);
     //delay(500);
    }
    else{
      val=0;
      analogWrite(led, val);
    }
    delay(3);
   break;

   case 2:
       //Steve's Values
    val = Serial.read(); 
    if(once == 0){
      if(val>= 48){
        once = 1;
        val=255;
       analogWrite(led, val);
       delay(800);
       analogWrite(led, 0);
      }
      else{
        val=0;
        analogWrite(led, val);
      }
      delay(3);
    }
    if (val < 17){
      once = 0;
    }

   break;
   
 }

  
     
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
