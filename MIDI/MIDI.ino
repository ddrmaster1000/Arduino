#include "Tlc5940.h"
#include <MIDI.h>


MIDI_CREATE_DEFAULT_INSTANCE();

int inte=0, clean=0, contador=1;
byte velocidad=0;
byte max_velocidad=127;

int vel=0;


int ledon[12];
int led=1;
int nota=0;
int nota_tocada=0;
int nota_soltada=0;
int note=0;
bool esta=false;

volatile int cambio_modo=1;


// -----------------------------------------------------------------------------

// This function will be automatically called when a NoteOn is received.
// It must be a void-returning function with the correct parameters,
// see documentation here:
// http://arduinomidilib.fortyseveneffects.com/a00022.html

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  nota =(int) pitch;
  velocidad=velocity;
  inte=1;
  if(cambio_modo==1){
    nota_tocada =(int) pitch;
    ledon[led]=nota_tocada; 
  }
}


void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  clean=1;
  nota =(int) pitch;
  if(cambio_modo==1){
    nota_soltada=nota;
      for(int i=1; i< 12 || !esta;i++){
        if(ledon[i]==nota_soltada){
          ledon[i]=-1;
          Tlc.set(i,0);
          Tlc.update();
          esta=true;        
       }else esta=false;
     }
   }
}

// -----------------------------------------------------------------------------

void setup()
{
  Serial.begin(31250);
  pinMode(2, INPUT);
   
   attachInterrupt( 0, change_mode, CHANGE);
  // Connect the handleNoteOn function to the library,
    // so it is called upon reception of a NoteOn.
    MIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function

    // Do the same for NoteOffs
    MIDI.setHandleNoteOff(handleNoteOff);

    // Initiate MIDI communications, listen to all channels
    MIDI.begin(MIDI_CHANNEL_OMNI);
  /* Call Tlc.init() to setup the tlc.
     You can optionally pass an initial PWM value (0 - 4095) for all channels.*/
  Tlc.init();
  
  for (int i=0; i<12;i++){
    ledon[i]=-1;
  }
}

/* This loop will create a Knight Rider-like effect if you have LEDs plugged
   into all the TLC outputs.  NUM_TLCS is defined in "tlc_config.h" in the
   library folder.  After editing tlc_config.h for your setup, delete the
   Tlc5940.o file to save the changes. */

void loop()
{
  // Call MIDI.read the fastest you can for real-time performance.
    MIDI.read();

    // There is no need to check if there are messages incoming
    // if they are bound to a Callback function.
    // The attached method will be called automatically
    // when the corresponding message has been received.
    switch(cambio_modo){
      case 1://ejecutamos modo 1
       if (inte){
          enciende_led(led);
          if (led==12){
            led=1;
          }else
            led ++;
      
          inte=0;
       }
       if (clean){
        clean=0;
        Tlc.update(); 
        }
        break;
      
      case 2: //ejecutamos modo 2
      
        if (inte){
            //Tlc.clear();
            calcula_contador(nota);
            enciende_led(contador);
            inte=0;
         }
        if (clean){
          calcula_contador(nota);
          Tlc.set(contador,0);
          Tlc.update();
          clean=0;
        }
        
       break;
      
      default: //ejecutamos modo 2
      //cambio_modo=1;
      
      if (inte){
            
            calcula_contador(nota);
            enciende_led(contador);
            inte=0;
         }
        if (clean){
          calcula_contador(nota);
          Tlc.set(contador,0);
          Tlc.update();
          clean=0;
        }
        
        break;
    }
}



void enciende_led(int contador){
  Tlc.set(contador,4095);
  Tlc.update();
}

int calcula_nota (int nota_a){
  while (nota_a > 11){
    nota_a=nota_a-12;
  }
  return nota_a;
}

void calcula_contador (int nota){
  while (nota > 11){
    nota=nota-12;
  }
  contador=nota+1;
  }

  
void change_mode() 
   {   
    if (cambio_modo==1)
     cambio_modo=2;
    
     else cambio_modo=1;
     Tlc.clear();
   }
