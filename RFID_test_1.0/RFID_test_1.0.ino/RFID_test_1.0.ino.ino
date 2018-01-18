#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>
#include <Wire.h>
#include "rgb_lcd.h"


#include <SparkFun_ADXL345.h>         // SparkFun ADXL345 Library

/*********** COMMUNICATION SELECTION ***********/
/*    Comment Out The One You Are Not Using    */
ADXL345 adxl = ADXL345(10);           // USE FOR SPI COMMUNICATION, ADXL345(CS_PIN);
//ADXL345 adxl = ADXL345();             // USE FOR I2C COMMUNICATION

int xglobal, yglobal, zglobal;

String connectConfirm;
int count = 0;
bool state_on_off = 1;
bool spiked = 0;

int ledPin4 = 4;                 // LED connected to digital pin 13
int ledPin5 = 5;

rgb_lcd lcd;
// If using the breakout with SPI, define the pins for SPI communication.
#define PN532_SCK  (2)
#define PN532_MOSI (3)
#define PN532_SS   (4)
#define PN532_MISO (5)

// If using the breakout or shield with I2C, define just the pins connected
// to the IRQ and reset lines.  Use the values below (2, 3) for the shield!
#define PN532_IRQ   (2)
#define PN532_RESET (3)  // Not connected by default on the NFC Shield

// Uncomment just _one_ line below depending on how your breakout or shield
// is connected to the Arduino:

// Use this line for a breakout with a software SPI connection (recommended):
//Adafruit_PN532 nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);

// Use this line for a breakout with a hardware SPI connection.  Note that
// the PN532 SCK, MOSI, and MISO pins need to be connected to the Arduino's
// hardware SPI SCK, MOSI, and MISO pins.  On an Arduino Uno these are
// SCK = 13, MOSI = 11, MISO = 12.  The SS line can be any digital IO pin.
//Adafruit_PN532 nfc(PN532_SS);

// Or use this line for a breakout or shield with an I2C connection:
Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
// also change #define in Adafruit_PN532.cpp library file
   #define Serial SerialUSB
#endif

void setup(void) {

      
     
     // Serial.begin(9600);
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.print("");
     lcd.clear();
     Drink_Locked_LCD();
  #ifndef ESP8266
    while (!Serial); // for Leonardo/Micro/Zero
  #endif
  Serial.begin(9600);
      pinMode(ledPin4,OUTPUT);
    pinMode(ledPin5,OUTPUT);
  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
   // Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  // Got ok data, print it out!
 // Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
//  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
//  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
  
  // configure board to read RFID tags
  nfc.SAMConfig();
  
 // Serial.println("Waiting for an ISO14443A Card ...");
  adxl.powerOn();                     // Power on the ADXL345

  adxl.setRangeSetting(2);           // Give the range settings
                                      // Accepted values are 2g, 4g, 8g or 16g
                                      // Higher Values = Wider Measurement Range
                                      // Lower Values = Greater Sensitivity

  adxl.setSpiBit(0);                  // Configure the device to be in 4 wire SPI mode when set to '0' or 3 wire SPI mode when set to 1
                                      // Default: Set to 1
                                      // SPI pins on the ATMega328: 11, 12 and 13 as reference in SPI Library 
   
  adxl.setActivityXYZ(1, 1, 1);       // Set to activate movement detection in the axes "adxl.setActivityXYZ(X, Y, Z);" (1 == ON, 0 == OFF)
  adxl.setActivityThreshold(70);      // 62.5mg per increment   // Set activity   // Inactivity thresholds (0-255)


  
}


void loop(void) {

  int x,y,z;
  int initialX, initialY, initialZ;
  int actX, actY, actZ;  


  
  static uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  bool good;
//Serial.println("A");

success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength,20);

 while(!success){
  digitalWrite(ledPin4, HIGH); //Push Out
  digitalWrite(ledPin5, HIGH);// sets the LED on

  delay(100);                  // waits for a second
  digitalWrite(ledPin4, LOW);  //Holds
  digitalWrite(ledPin5, HIGH);// sets the LED on

  delay(2000);
  //Serial.println("B");
  if(spiked == 0){
  Drink_Locked_LCD();
  }
    adxl.readAccel(&x, &y, &z);         // Read the accelerometer values and store them in variables declared above x,y,z
 
    while(Serial.available())
      {

      }
 if(state_on_off == 0){
    if(abs(xglobal - x) > 40){
            Serial.println("Activity X");
        //Serial.println(x); //debug code
        Drink_Tampered_LCD();
        spiked = 1;
    }
  
      if(abs(yglobal - y) > 40){
            Serial.println("Activity Y");
        //Serial.println(x); //debug code
        Drink_Tampered_LCD();
        spiked = 1;
    }
  
      if(abs(zglobal - z) > 40){
            Serial.println("Activity Z");
        //Serial.println(x); //debug code
        Drink_Tampered_LCD();
        spiked = 1;
    }
 }

  xglobal = x;
  yglobal = y;
  zglobal = z;

  state_on_off = 0;
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength,20);



  
 }
  //Serial.println("C");

  while(success){
  digitalWrite(ledPin4, LOW);  //Pulls in
  digitalWrite(ledPin5, LOW);  // sets the LED off
  
  delay(100);                  // waits for a second
  digitalWrite(ledPin4, LOW); //Holds
  digitalWrite(ledPin5, HIGH);// sets the LED on
    success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength,20);
      Drink_Good_LCD();
    // Display some basic information about the card
   // Serial.println("Found an ISO14443A card");
   // Serial.print("  UID Length: ");Serial.print(success, DEC);Serial.println(" bytes");
   // Serial.print("  UID Value: ");
    //nfc.PrintHex(uid, uidLength);
   // Serial.println("");
    delay(50);
    state_on_off = 1;
    spiked = 0;
  }
    
  
}

void Drink_Good_LCD()
{
  lcd.setRGB(0, 200, 0);
  lcd.clear();
  lcd.print("    Cheers!");
  delay(2000);
}

void Drink_Tampered_LCD()
{

  lcd.setRGB(254, 0, 0);
  lcd.clear();
  lcd.print("  Mug Tampered");
  delay(2000);

}

void Drink_Locked_LCD()
{

  lcd.setRGB(0, 0, 254);
  lcd.clear();
  lcd.print("  Mug Locked");
  delay(2000);

}

