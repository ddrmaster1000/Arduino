#include "LPD8806.h"


in nLEDs = 8;
int dataPin = 2;
int clockPin = 3;

LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);

void setup() {
  
  strip.begin();
  strip.show(); 
  
}

double red = 0;
double green = 0;
double blue = 0;
int count = 0;


void loop() {
  
  //CallRedEqualizer
  for(i=0;i=10;i++;){
    if((red + i)== green){
    	red = random(0,254);
    	CallRedEqualizer();
    }
    //CallGreenEqualizer
    for(i=0;i=10;i++;){
    if((green + i)== blue){
    	green = random(0,254);
    	CallRedEqualizer();
    }
    
    //CallBlueEqualizer
    for(i=0;i=10;i++;){
    if((blue + i)== red){
    	blue = random(0,254);
    	CallBlueEqualizer();
         }
       }
    RestartSequence();
  }


}

}




void RestartSequence() {/* once all of the lights are on, it restarts picking random lights to turn on
Have to decide if you want to have it turn on the lights randomly and sometimes the same one 2x or just once all of them are on to restart it. */
  RandomLightarray(0,24) = 0; // creates an array of 25.
  Pick = random(0,numlights); //pick one number random from max number of lights
  count = 0;
  
  if(RandomLightAray(Pick) == 1){ Pick = random(0,numlights)}
  //Call RandomlightArray again. 
  //if get same light, try again
  
    count=0;
  for(i=0;i=numlights;i++;){//count how many lights you have turned on
  	if(randomlightarray(i) ==1){
  		count++;
  }
    if(count == (numlights – 1)){ //if your count is 1 less than your total lights on
      Setlights(r,g,b,i) = <0,0,0>; //turn them all off 	
      for(i=0;i=numlights;i++){randomlightarray(i) = 0;}//restart the process
    }
  }
  Setlights(r,g,b,Pick);// turn on an individual light
  
  }
  
  


