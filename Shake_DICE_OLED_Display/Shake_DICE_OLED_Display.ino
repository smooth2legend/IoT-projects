
 //The sketch use an oled display 128x64 pixel I2C interface to display one or two dices.
  //The display are connected
 // SCL Analog5  Use Pullup Resistor:
 // SDA Analog4  Use Pullup Resistor:
 // Vcc +5V
  //GND Ground
 // the sketch uses U8g2lib as displaydriver
 // see below copyrigt and download info

  /*
  /*

  U8g2lib.h

  C++ Arduino wrapper for the u8g2 struct and c functions for the u8g2 library
  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)
  Copyright (c) 2016, olikraus@gmail.com
  All rights reserved.
  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:
    Redistributions of source code must retain the above copyright notice, this list
    of conditions and the following disclaimer.

    Redistributions in binary form must reproduce the above copyright notice, this
    list of conditions and the following disclaimer in the documentation and/or other
    materials provided with the distribution.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  Note:
  U8x8lib.h is included for the declaration of the helper functions in U8x8lib.cpp.
  U8g2 class is based on the u8g2 struct from u8g2.h, the U8x8 class from U8x8lib.h is not used.
*/

#include<U8g2lib.h>
#include <Wire.h>
#include<SPI.h>
#include <EEPROM.h>


U8G2_SSD1306_128X64_NONAME_2_HW_I2C oled(U8G2_R0, /*reset=*/ U8X8_PIN_NONE);
const byte BUTTON_PIN = 7;
const byte SELECT_PIN = 10;
const byte SHUTOFFPIN = 8;
const byte SOUND_PIN = 6;

unsigned long int time = millis();
const long int warningTime = 60000; //AutoShutoff time

byte startadress = 0; //EEPROM Startadress
const byte EEPROM_ID = 0x97;//to track valid data in EEPROM

byte rollMode = 1;
int dicenr1 = 1; // Dice random number 1
int dicenr2 = 1; //Dice random number 2
int dicenumber = 1; //Dice variable One or Two
boolean BUZZ = true;//Sound on


void setup(void) {
  //oled.setI2CAddress(0x3C * 2); //set display adress if needed (default 0x3C)
  oled.begin();
  
  ////////////////////Set POWER On Control////////////////
  pinMode(SHUTOFFPIN, OUTPUT);
  digitalWrite(SHUTOFFPIN, HIGH);
  ////////////////////////////////////////////////////////
  pinMode(SELECT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(SOUND_PIN, OUTPUT);
  //Serial.begin(9600);


  randomSeed(analogRead(A0));
  ///////////////////////Check for valid data//////////////////
  byte id = EEPROM.read(startadress);
  if (id == EEPROM_ID) {
    dicenr1 = EEPROM.read(startadress + 1);
    dicenr2 = EEPROM.read(startadress + 2);
    dicenumber = EEPROM.read(startadress + 3);
    BUZZ = EEPROM.read(startadress + 4);
  } else {
    EEPROM.write(startadress, EEPROM_ID);
    EEPROM.write(startadress + 1, dicenr1);
    EEPROM.write(startadress + 2, dicenr2);
    EEPROM.write(startadress + 3, dicenumber);
    EEPROM.write(startadress + 4, BUZZ);
  }
  /////////////////////////////////////////////////////////////////
  Roll(); //Show last Dice before shutoff
  delay(1000);
}
void loop(void) {
  ///////////////Select one or Two Dice////////////
  
  if (digitalRead(SELECT_PIN) == LOW) {
    long SELECT_time = millis();
    while (digitalRead(SELECT_PIN) == LOW) {};
    if (millis() - SELECT_time < 1000) {
      dicenumber = (dicenumber % 2) + 1;
      if (BUZZ) {
        tone(SOUND_PIN, 500, 80);
        delay(200);
      }
    } else {
      tone(SOUND_PIN, 500, 80);
      BUZZ = ! BUZZ;
    }
  }

  /////////////check rollbutton//////////////////

  if (digitalRead(BUTTON_PIN) == LOW) {

    rollMode = 0;
    do {
      randomGenerator();
      Roll();
    }
    while (digitalRead(BUTTON_PIN) == LOW);
    slow();
    time = millis();
    rollMode = 2;
  }
  ///////////////////////////////////////////////

  Roll(); // Show Result

  Check_On_Time();
}

//////////////Check On Time and save data//////////////////
void Check_On_Time() {
  if (millis() - time > warningTime) {
    CleanScreen();
    Roll();
  }
  if (millis() - time > warningTime + 5000) {

    EEPROM.write(startadress + 1, dicenr1);
    EEPROM.write(startadress + 2, dicenr2);
    EEPROM.write(startadress + 3, dicenumber);
    EEPROM.write(startadress + 4, BUZZ);
    delay(50);
    digitalWrite(SHUTOFFPIN, LOW);
  }
}
///////////////////////////////////////////////////////////////

///////////////////Roll dice draw and display///////////////////
void Roll() {
  String number[25] = {"One", "Two", "Three", "Four", "Five", "Six"};

  int x;
  int x1;
  const int y = 2;
  oled.setFont(u8g_font_helvB10);

  oled.firstPage();
  do {
    if (rollMode == 1) {
      oled.drawStr(36, 64, "Last Roll");
    } else if (rollMode == 0) {
      oled.drawStr(36, 64, "Roll Dice");
    }

    switch (dicenumber) {

      case (1): //Two dice
        x = 76;

        oled.drawFrame(2 + x, y, 48, 48);
        if (dicenr1 == 1) {
          oled.drawDisc(26 + x, 24 + y, 4); //Center
          x1 = 13;
        } else if (dicenr1 == 2) {
          oled.drawDisc(12 + x, 10 + y, 4); //upper L
          oled.drawDisc(40 + x, 38 + y, 4); //lower R
          x1 = 14;

        } else if (dicenr1 == 3) {
          oled.drawDisc(26 + x, 24 + y, 4); //Center
          oled.drawDisc(12 + x, 10 + y, 4); //upper L
          oled.drawDisc(40 + x, 38 + y, 4); //lower R
          x1 = 7;

        } else if (dicenr1 == 4) {
          oled.drawDisc(12 + x, 10 + y, 4); //upper L
          oled.drawDisc(40 + x, 10 + y, 4); //upper R
          oled.drawDisc(12 + x, 38 + y, 4); //lower L
          oled.drawDisc(40 + x, 38 + y, 4); //lower R
          x1 = 11;

        } else if (dicenr1 == 5) {
          oled.drawDisc(12 + x, 10 + y, 4); //upper L
          oled.drawDisc(40 + x, 10 + y, 4); //upper R
          oled.drawDisc(12 + x, 38 + y, 4); //lower L
          oled.drawDisc(40 + x, 38 + y, 4); //lower R
          oled.drawDisc(26 + x, 24 + y, 4); //Center
          x1 = 13;

        } else if (dicenr1 == 6) {
          oled.drawDisc(12 + x, 10 + y, 4); //upper L
          oled.drawDisc(40 + x, 10 + y, 4); //upper R
          oled.drawDisc(12 + x, 38 + y, 4); //lower L
          oled.drawDisc(40 + x, 38 + y, 4); //lower R
          oled.drawDisc(12 + x, 24 + y, 4); //center L
          oled.drawDisc(40 + x, 24 + y, 4); //center R
          x1 = 16;
        }
        if (rollMode == 2) {

          oled.setCursor(x1 + x, 62 + y);
          oled.print(number[dicenr1 - 1]);

        }
      case (2)://one Dice

        if (dicenumber == 2) {
          x = 40;
        } else {
          x = 5;
        }
        oled.drawFrame(2 + x, y, 48, 48);

        if (dicenr2 == 1) {
          oled.drawDisc(26 + x, 24 + y, 4); //Center
          x1 = 13;

        } else if (dicenr2 == 2) {
          oled.drawDisc(12 + x, 10 + y, 4); //upper L
          oled.drawDisc(40 + x, 38 + y, 4); //lower R
          x1 = 14;

        } else if (dicenr2 == 3) {
          oled.drawDisc(26 + x, 24 + y, 4); //Center
          oled.drawDisc(12 + x, 10 + y, 4); //upper L
          oled.drawDisc(40 + x, 38 + y, 4); //lower R
          x1 = 7;

        } else if (dicenr2 == 4) {
          oled.drawDisc(12 + x, 10 + y, 4); //upper L
          oled.drawDisc(40 + x, 10 + y, 4); //upper R
          oled.drawDisc(12 + x, 38 + y, 4); //lower L
          oled.drawDisc(40 + x, 38 + y, 4); //lower R
          x1 = 11;

        } else if (dicenr2 == 5) {
          oled.drawDisc(12 + x, 10 + y, 4); //upper L
          oled.drawDisc(40 + x, 10 + y, 4); //upper R
          oled.drawDisc(12 + x, 38 + y, 4); //lower L
          oled.drawDisc(40 + x, 38 + y, 4); //lower R
          oled.drawDisc(26 + x, 24 + y, 4); //Center
          x1 = 13;

        } else if (dicenr2 == 6) {
          oled.drawDisc(12 + x, 10 + y, 4); //upper L
          oled.drawDisc(40 + x, 10 + y, 4); //upper R
          oled.drawDisc(12 + x, 38 + y, 4); //lower L
          oled.drawDisc(40 + x, 38 + y, 4); //lower R
          oled.drawDisc(12 + x, 24 + y, 4); //center L
          oled.drawDisc(40 + x, 24 + y, 4); //center R
          x1 = 16;
        }
        if (rollMode == 2) {
          oled.setCursor(x1 + x, 62 + y);
          oled.print(number[dicenr2 - 1]);
        }
        break;
    }
  } while (oled.nextPage());
  delay(100);
}
////////////////////////////////////////////////////////////////////////////

//////////////////////Slow down rolling dice///////////////////////////////

void slow() {
  int d = 0;
  for (int i = 0; i < (random(7, 30)); i++) {

    randomGenerator();
    Roll();
    delay(d);
    d = d + 50;
  }

  if (BUZZ) {
    tone(SOUND_PIN, 800, 500);
  }
}
////////////////////////////////////////////////////////////////////////

//////////////////////////Create Random Numbers////////////////////////

void randomGenerator () {

  dicenr1 = random(1, 7);
  dicenr2 = random(1, 7);

  if (BUZZ) {
    tone(SOUND_PIN, 700, 80);
  }

}

//////////////////////////////////////////////////////////////////////

/////////////////////////Clear Display////////////////////////////////
void CleanScreen() {
  if (BUZZ) {
    tone(SOUND_PIN, 1000, 20);
  }
  oled.firstPage();
  do {
  } while (oled.nextPage());
  delay(10);
}
