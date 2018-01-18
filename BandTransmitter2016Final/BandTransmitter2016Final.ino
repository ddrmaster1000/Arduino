#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(8, 9);

const byte rxAddr[6] = "00001"; //array size being sent
char text[6]; //'text' array is name of array being sent. Must match rxAddr
String stringOne = ""; //define a blank string for later use
byte index = 0; //variable of size byte that will be used 
volatile int counter = 129; //multiple of numpattern - 1 to initilize to blank
const int numPattern = 13; //total number of patterns you have to be sent

void setup()
{
  Serial.begin(9600); 
  attachInterrupt(1, changePattern, RISING); //interrupt. xx(interuppt pin, function being called, interuppt on rising edge
  radio.begin(); //start NRF radio
  //radio.setRetries(15, 15); //if no data sent/recieved, retry 15 times before stopping
  radio.openWritingPipe(rxAddr); //start writing to byte rxAddr
  
  radio.stopListening(); //stop NRF from listening for anything
}

void changePattern(){ //change pattern function
  counter++; //increase pattern by 1
  counter %= numPattern; 
}

void loop()
{
  stringOne = counter; //set string to counter
  stringOne.toCharArray(text,6); //set string one into 'text' array of size 6
  Serial.println(text); //print out on serial what is being sent through NRF
  radio.write(&text, sizeof(text)); //write to be sent. text array pointer, send actual text array 
  delay(125); //need some delay for NRF to actually transmit
}
