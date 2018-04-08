#include <Servo.h> 
// Declare the Servo pin 
int pin0 = 3; //rotation of the bottom
int pin1 = 5; //bottom servo
int pin2 = 6; //middle
int pin3 = 9; //top
int pin4 = 10; //claw
// Create a servo object 
Servo Servo0; //rotation at the bottom
Servo Servo1; //bottom servo
Servo Servo2; //middle
Servo Servo3; //top
Servo Servo4; //claw

int Max0 = 179;
int Min0 = 0;
int Max1 = 90;
int Min1 = 40;
int Max2 = 45;
int Min2 = 0;
int Max3 = 90;
int Min3 = 15;
int Max4 = 180;
int Min4 = 0;

int pos0 = 90;
int pos1 = 90;
int pos2 = 0;
int pos3 = 90;
int pos4 = 0;

//reading information
int arr[3];
int x; //reading rotation
int y;  //reading height
int state; //reading open or close
int serialln = 0;

int xLast;
int yLast;
int stateLast;

double yAverage;

int TOL = 1; //tolorance
int TOLX = 5; //tolorance

int movingarr[4];

void setup() { 

   Serial.begin(9600);
  
   // We need to attach the servo to the used pin number 
   Servo0.attach(pin0); // 0 - 180 
   Servo1.attach(pin1);// 40 - 90  //low is down
   Servo2.attach(pin2);// 0 - 45   //high is down
   Servo3.attach(pin3);// 15 -90   //low is down
   Servo4.attach(pin4); //0-180    //low is open

   //set in starting up position 
   Servo0.write(pos0);
   Servo1.write(pos1); 
   Servo2.write(pos2);
   Servo3.write(pos3);
   Servo4.write(pos4);

   delay(1000);
}


void loop(){ 

 if(Serial.available())
 {
   readIncomingBytes();
 }

  switch(state){
    case 0: //REST
        if( (y > (yLast + TOL)) || (y < (yLast - TOL)) ){
           MoveArm();
        }
      break;
    
    case 1: //Fingers Spread, Moves Y axis
      pos4 = 0;
      Servo4.write(pos4);
      break;

    
    case 2: //Closed Fist, Moves Y axis
      pos4 = 180;
      Servo4.write(pos4);
      break;
    
    case 3:  //Wave out moves X axis
          if(x >=75)
          {
            pos0 +=5;
            if(pos0 >= 180)
            {
              pos0 = 180;
            }
          }
          if(x <= 3)
          {
            pos0 -=5;
            if(pos0 <= 0)
            {
              pos0 = 0;
            }
          }
          Servo0.write(pos0);

       break;
  }
   
   
   delay(40);
   xLast = x;
   yLast = y;
   stateLast = state;
  

  //MoveDOWN();
 
}


void MoveArm()
{
    
   double moveAmount1 = Max1+Min1-((y * (Max1 - Min1)/180.0) + Min1);
   double moveAmount2 = ((y * (Max2 - Min2)/180.0) + Min2);
   double moveAmount3 = Max3+Min3-((y * (Max3 - Min3)/180.0) + Min3);
  // Servo0.write(moveAmount0);   
   Servo1.write(moveAmount1);
   Servo2.write(moveAmount2);
   Servo3.write(moveAmount3);

//double moveAmount1 = y*(Max1-Min1)/180;





}

void MoveDOWN(){

  if(pos1 > Min1){
    pos1 = pos1 - 2;
    Servo1.write(pos1); 
  }
  if(pos2 < Max2){
    pos2 = pos2 + 2;
    Servo2.write(pos2);
  }
  if(pos3 > Min3){
    pos3 = pos3 - 3;
    Servo3.write(pos3);
  }

  delay(70);
}

void MoveUP(){

  if(pos1 < Max1){
    pos1 = pos1 + 2;
    Servo1.write(pos1); 
  }
  if(pos2 > Min2){
    pos2 = pos2 - 2;
    Servo2.write(pos2);
  }
  if(pos3 < Max3){
    pos3 = pos3 + 3;
    Servo3.write(pos3);
  }

  delay(70);
}

void readIncomingBytes() {
  while (Serial.available() > 0)
  {
    int incomingByte = Serial.read();
    if (incomingByte == (int)'<')
    {
      serialln = 0;

    }
    else if (incomingByte == (int)'>')
    {
      x = arr[0];
      y = arr[1];
      state = arr[2];
      return;
    }
    else
    {
      arr[serialln] = incomingByte;
      serialln++;
    }
  }
  /*
  //moving average
  int total = 0;
  int arrNew[4]; 
  for(int i = 0; i< 4-1; i++)
  {
    arrNew[i+1] = movingarr[i];
  }
  arrNew[0] = y; 
  for(int i = 0 ; i< 4-1; i++)
  {
    total = total + arrNew[i]; 
  }
  y = total/4;
  */
  
}
