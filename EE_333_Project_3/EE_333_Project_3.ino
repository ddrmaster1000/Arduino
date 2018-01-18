#include "DHT.h"
#include "LiquidCrystal.h"

LiquidCrystal lcd(0,1,7,8,9,10);

#define DHTPIN 2
#define DHTTYPE DHT22
#define outputA 3
#define outputB 4

DHT dht(DHTPIN, DHTTYPE);

int counter = 0;
int aState;
int aLastState;
float f_temp;
byte actuator_state;

int desired_temp = 69;//The desired Temperature defined by the rotary encoder. 
int temp_range=2;     //temperature can be 2 below or above desired value before the thermostat changes.


void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  pinMode(outputA,INPUT);
  pinMode(outputB,INPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  Serial.begin(9600);
  dht.begin();
  aLastState = digitalRead(outputA);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  
}

void loop() {
  delay(10);  //pause for a moment before each run-through.
  Check_Rotary_Encoder();//Checks position of encoder
  Check_Temp();         //checks the temp and adjusts the actuator accordingly
  LCD_resfresh();       //Refreshes LCD screen with the newest info
  

  

}

//Checks temperature and moves actuator
void Check_Temp(){
  f_temp=dht.readTemperature(true);
  if (f_temp+temp_range > desired_temp){
    AC_cool();
  }
  else if (f_temp-temp_range < desired_temp){
    AC_heat();
  }
  else{
    //do nothing if we are in the correct Temperature. 
  }
  
}

//Turns on the AC
void AC_cool(){
  if(actuator_state == 1){ //if statement prevents from toggling the actuator constantly. if in the state, don't change it unless the actuator is in the wrong state. 
    digitalWrite(5,HIGH);
    digitalWrite(6,LOW);
    delay(50);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
  }
  actuator_state = 0;
}

//Turns off the AC (heating because room heats up on its own)
void AC_heat(){
  if(actuator_state == 0){
    digitalWrite(5,LOW);
    digitalWrite(6,HIGH);
    delay(50);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
  }
  actuator_state = 1;
}

void LCD_resfresh(){
  lcd.clear();
  lcd.print("Temp: ");
  lcd.print(f_temp);
  lcd.print("F");

  lcd.setCursor(0,1);
  lcd.print("Desired: ");
  lcd.print(desired_temp);
  lcd.print("F");
  
}

//Calculates the position of the rotary encoder
void Check_Rotary_Encoder(){
  aState=digitalRead(outputA); //Read current state at A
  if (aState != aLastState){
    if (digitalRead(outputB) != aState){
      counter++;
    }
    else{
      counter--;
    }
  }
  desired_temp = desired_temp + counter;  //Calculate the temp with the offset so we don't have to scroll the wheel 69 times before it starts working. 
  Serial.print("Temperature: ");
  Serial.println(desired_temp);
  aLastState = aState;  //update the state
  
}

