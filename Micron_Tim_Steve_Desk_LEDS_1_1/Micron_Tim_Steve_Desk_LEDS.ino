#include <SPI.h>
#include "RF24.h"



RF24 radio(7,8);
const uint64_t pipe = 0xE8E8F0F0E1LL; //channel to receive
byte addresses[][6] = {"1Node","2Node"};





typedef struct {
  char ID[10];
  byte Butt;
}MsgData;


//UNcomment if your name is Steve
MsgData MY_LED_DATA  = {"Steve", 0};
MsgData HIS_LED_DATA = {"Tim", 0};


//UNcomment if your name is Tim
//MsgData MY_LED_DATA  = {"Tim", 0};
//MsgData HIS_LED_DATA = {"Steve", 0};

//UNcomment if your name is Steve
char My_Name[] = "Steve"; 
char His_Name[] = "Tim";

//UNcomment if your name is Tim
//My_Name[] = "Tim";
//His_Name[] = "Steve";

int ledPin = 13; // choose the pin for the LED


void setup(void){
    attachInterrupt(0, interrupt, RISING);
    Serial.begin(9600);
    radio.begin();
    radio.setAutoAck(false);
    radio.openReadingPipe(1,pipe);
    radio.startListening();
}


void interrupt(){
  MY_LED_DATA.Butt = 1;
  transmit(MY_LED_DATA);
  Serial.println("Transmitted!!!!!!!!!!!!!!!!!!");
  
}

void loop(void){

  receive();
  MY_LED_DATA.Butt = 0;

  if(HIS_LED_DATA.ID == His_Name && HIS_LED_DATA.Butt == 1){ //Turn on if is an expected signal
    Serial.println("Recieved one!");
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    HIS_LED_DATA.Butt = 0;
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
  for(byte i=0; i<5; i++){  
        radio.write(&Transmit_Msg, sizeof(MsgData));
        delay(5);
  }
}

