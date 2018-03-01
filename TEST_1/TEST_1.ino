#include <SoftwareSerial.h>
  #define RFID_START  0x00  // RFID Reader Start and Stop bytes

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

Serial.println("TEST_1");
        for(int i=0x00; i<0xFF; i++){
        Serial.println(i, HEX);
        }

}
