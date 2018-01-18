
 int val; // Data received from the serial port
 int int_val = 0;
 int ledPin = 9; // Set the pin to digital I/O 13

 void setup() {
   pinMode(ledPin, OUTPUT); // Set pin as OUTPUT
   Serial.begin(9600); // Start serial communication at 9600 bps
 }

 
void loop() {
   if (Serial.available()) 
   { // If data is available to read,
     val = Serial.read(); // read it and store it in val

   // int_val = '0';
   
   if (val > 100)
   { // If 1 was received
     analogWrite(ledPin, 254); // turn the LED on
     val=0;
   } else {
     digitalWrite(ledPin, 0); // otherwise turn it off
   }
   delay(10); // Wait 10 milliseconds for next reading
   }

}
