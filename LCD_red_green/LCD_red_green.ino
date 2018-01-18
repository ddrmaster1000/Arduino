/*
  setColor.ino
  2013 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author:Loovee
  2013-10-15

  Grove - Serial LCD RGB Backlight demo.
  you can set color by serial input, input "rrr ggg bbb"

  rrr means red, 0-255, eg: 005, 015, 135
  ggg means green
  bbb means blue
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;


void setup() 
{
    Serial.begin(115200);
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.print("");
}

void loop() 
{

Drink_Tampered_LCD();

Drink_Good_LCD();




}

void Drink_Tampered_LCD()
{

  lcd.setRGB(254, 0, 0);
  lcd.clear();
  lcd.print("  Mug Tampered");
  delay(2000);

}

void Drink_Locked_LCD()
{

  lcd.setRGB(0, 0, 254);
  lcd.clear();
  lcd.print("  Mug Lock");
  delay(2000);

}

void Drink_Good_LCD()
{
  lcd.setRGB(0, 254, 0);
  lcd.clear();
  lcd.print("    Cheers!");
  delay(2000);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
