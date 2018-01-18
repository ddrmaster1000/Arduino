int analogPin = 3;     // potentiometer wiper (middle terminal) connected to analog pin 3

                       // outside leads to ground and +5V





void setup()

{

  Serial.begin(9600);          //  setup serial

}



void loop()

{

 float val = analogRead(analogPin)*(5/1024.0);    // read the input pin

  Serial.println(val);             // debug value

}

  

