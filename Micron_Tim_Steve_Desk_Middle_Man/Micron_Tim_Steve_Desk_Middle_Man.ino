#include <SPI.h>
#include "RF24.h"



RF24 radio(7,8);
const uint64_t pipe = 0xE8E8F0F0E1LL; //channel to receive
byte addresses[][6] = {"1Node","2Node"};

typedef struct {
  int ID;
  byte Butt;
}MsgData;

MsgData DataIn;
MsgData DataOut;

void setup(void){
    Serial.begin(115200);
    radio.begin();
    radio.setAutoAck(false);
    radio.openReadingPipe(1,pipe);
    radio.startListening();
}



void loop(void){
  
receive();

if((DataIn.Butt != DataOut.Butt) || (DataIn.ID != DataOut.ID)){
  transmit(DataIn);
  DataOut = DataIn;
}

}




        
void receive(){                                                             //Recieve Data from another node
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
    radio.startListening();  
       if(radio.available()){
        while(radio.available()){   
            radio.read(&DataIn, sizeof(MsgData));  //byte value
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

