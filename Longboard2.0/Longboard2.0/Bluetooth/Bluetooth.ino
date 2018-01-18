#include "LPD8806.h"
#include "SPI.h"
#include "SoftwareSerial.h"

SoftwareSerial mySerial(0, 1); // RX, TX
int nLEDs = 20;

//int dataPinRight  = 4;
//int clockPinRight = 5;

void setup() {
  // put your setup code here, to run once:  // Open serial communications and wait for port to open:
   Serial.begin(9600);
   while(!Serial){;}
   mySerial.begin(9600);
   mySerial.println("JUST DO IT");
}

void loop() {

if(mySerial.available()) {
    Serial.write(mySerial.read());
}
/*if (Serial.available()){
    mySerial.write(Serial.read());
}
*/

}
