#include <SoftwareSerial.h>

static long timeUntilTurnOff = 5000; // max value: 2147483647;

long millisAtLastRead = 0;
long timeSinceLastRead = 0;
long recieve = 0;
int out_pin = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(out_pin, OUTPUT);
  analogWrite(out_pin, 0);
  Serial.begin(600);//115200);
}

void loop() {
  if (Serial.available() > 0) {
    recieve = (log(Serial.read()) / log(1.05)) + 155;   // becomes log[base 1.05](Serial.read())
    if (recieve >= 255) {
      recieve = 255;
    }
    
    analogWrite(out_pin, recieve);
    millisAtLastRead = millis();
  } else if (timeSinceLastRead < timeUntilTurnOff) {
    timeSinceLastRead = millis() - millisAtLastRead;
  }

  if (timeSinceLastRead >= timeUntilTurnOff) {
    analogWrite(out_pin, 0);
  }
}

// exp(0.075 * Serial.read()) seems to produce best results
// 1.75 * Serial.read() // 4 spectrumGroups

//void loop() {
//  analogWrite(out_pin, 255);
//}
