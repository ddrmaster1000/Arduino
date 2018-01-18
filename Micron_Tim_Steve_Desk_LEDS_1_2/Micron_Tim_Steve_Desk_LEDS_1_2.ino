#include <SPI.h>
#include "RF24.h"



RF24 radio(7,8);
const uint64_t pipe = 0xE8E8F0F0E1LL; //channel to receive
byte addresses[][6] = {"1Node","2Node"};

typedef struct {
  int ID;
  byte Butt;
}MsgData;


//UNcomment if your name is Steve
MsgData MY_LED_DATA  = {420, 0};
MsgData HIS_LED_DATA = {69, 0};
int My_Name = 420;
int His_Name = 69;

//UNcomment if your name is Tim
//MsgData MY_LED_DATA  = {69, 0};
//MsgData HIS_LED_DATA = {420, 0};
//int My_Name = 69;
//int His_Name = 420;



int inPin = 3; // choose the pin for the button
int ledPin = 6;
int val=0;
bool tOff = 0;
bool rOff = 0;

void setup(void){
    Serial.begin(115200);
    radio.begin();
    radio.setAutoAck(false);
    radio.openReadingPipe(1,pipe);
    radio.startListening();
    pinMode(ledPin, OUTPUT);  // declare LED as output
    pinMode(inPin, INPUT);    // declare pushbutton as input
}



void loop(void){

  val = digitalRead(inPin);
  receive();
  //Serial.println();

//Recieved Data, Turn on LED
  while(HIS_LED_DATA.ID == His_Name && HIS_LED_DATA.Butt == 1){ //Turn on if is an expected signal
    rOff = 1;
    Serial.println("Received one!");
    digitalWrite(ledPin, HIGH);
    receive();
  }
  
  //Turn off LED after a long receive
  if(rOff == 1){
        digitalWrite(ledPin, LOW);
  }


//If Button Press, "ON" transmit
  while(val == HIGH){
    tOff = 1;
    MY_LED_DATA.Butt = 1;
    transmit(MY_LED_DATA);
    val = digitalRead(inPin);
    
  }
//after an "ON" Transmit, executre "OFF" Transmit
  if(tOff == 1){
    tOff = 0;
    MY_LED_DATA.Butt = 0;
    transmit(MY_LED_DATA);
  }  
}




        
void receive(){                                                             //Recieve Data from another node
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
    radio.startListening();  
       if(radio.available()){
        while(radio.available()){   
            radio.read(&HIS_LED_DATA, sizeof(MsgData));  //byte value
            delay(5);
         }
      }
    return;
}

void transmit(MsgData Transmit_Msg){                                        //Transmit Data to Another Node
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
    radio.stopListening();
    //unsigned long msg = value;
  for(byte i=0; i<15; i++){  
        radio.write(&Transmit_Msg, sizeof(MsgData));
        delay(5);
  }
  Serial.println("Transmitted Data");
  Serial.print("ID: ");
  Serial.println(Transmit_Msg.ID);
    Serial.print("Button: ");
    Serial.println(Transmit_Msg.Butt);
    Serial.println();
}

