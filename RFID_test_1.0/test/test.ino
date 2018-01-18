int ledPin4 = 4;                 // LED connected to digital pin 13
int ledPin5 = 5;
void setup()
{
  Serial.begin(9600);
  pinMode(ledPin4, OUTPUT);
    pinMode(ledPin5, OUTPUT);// sets the digital pin as output
}

void loop()
{
  digitalWrite(ledPin4, HIGH); //Push Out
  digitalWrite(ledPin5, HIGH);// sets the LED on
Serial.println("A");
  delay(100);                  // waits for a second
  digitalWrite(ledPin4, LOW);  //Holds
  digitalWrite(ledPin5, HIGH);// sets the LED on
Serial.println("B");


  
  delay(2500);                  // waits for a second
  digitalWrite(ledPin4, LOW);  //Pulls in
  digitalWrite(ledPin5, LOW);  // sets the LED off
  Serial.println("C");
  delay(100);                  // waits for a second
  digitalWrite(ledPin4, LOW); //Holds
  digitalWrite(ledPin5, HIGH);// sets the LED on
  delay(2500);                  // waits for a second
Serial.println("D");
}
