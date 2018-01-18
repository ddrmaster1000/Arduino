/* To be used to make a Puppet Chicken Head in Spooky Attics turn around when flashlights are pointed at them
 *  
 *  
 */

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

int current_pos = 0;
int pos = 0;
int OnValue = 22;
int OffValue = OnValue - 1;

void setup() {
  // declare the ledPin as an OUTPUT:
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  if(sensorValue >= OnValue){
    LightOn_RotateFoward();
  }
  else{
    LightOff_RotateBackward();
  }
}

void LightOff_RotateBackward(){
  for (pos = current_pos; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
    if(sensorValue <= OffValue){
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      current_pos = pos;
      delay(10);                       // waits 15ms for the servo to reach the position
      sensorValue = analogRead(sensorPin);
      Serial.println(sensorValue);
    }
  }
  while(current_pos == 0 && sensorValue <= OffValue){
    delay(10);
    sensorValue = analogRead(sensorPin);
    Serial.println(sensorValue);
  }
}

void LightOn_RotateFoward(){
  for (pos = current_pos; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    if(sensorValue >= OnValue){
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      current_pos = pos;
      delay(25);                       // waits 15ms for the servo to reach the position
      sensorValue = analogRead(sensorPin);
      Serial.println(sensorValue);
    }
  }
  while(current_pos == 180 && sensorValue >= OnValue){
    delay(10);
    sensorValue = analogRead(sensorPin);
    Serial.println(sensorValue);
  }
}

