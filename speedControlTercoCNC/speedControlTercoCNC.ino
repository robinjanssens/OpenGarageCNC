//========================================
//
//   Speed Control Terco CNC
//   Copyright (C) 2016  Open Garage
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 3 of the License, or
//   (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software Foundation,
//   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
//
//========================================

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Missing in version 1.0.5
#ifndef NOT_AN_INTERRUPT
#define NOT_AN_INTERRUPT -1
#endif
#ifndef digitalPinToInterrupt
#define digitalPinToInterrupt(p)  ((p) == 2 ? 0 : ((p) == 3 ? 1 : NOT_AN_INTERRUPT))
#endif

const byte interruptPin = 2;
const unsigned int ppr = 24;                     // pulses per revolution
const unsigned int sampleTime = 100;            // count for this amount of ms
volatile unsigned int pulses = 0;

LiquidCrystal_I2C lcd(0x20, 16, 2);

void counter() {
  pulses++;
}

void setup() {
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), counter, CHANGE);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  unsigned long startTime;
  unsigned long testTime;
  unsigned int rpm;
  char buffer[16];
  
  startTime = millis();
  pulses = 0;                                   // reset pulse counter
  while(1) {
    testTime = millis();
    if(testTime - startTime >= sampleTime) {
      rpm = pulses * ((1000 / sampleTime) * 60 / ppr); // revolutions per minute
      Serial.println(rpm);
      Serial.println(pulses);
      lcd.home();
      sprintf(buffer, "%4d RPM", rpm);
      lcd.print(buffer);
      lcd.setCursor(0, 1);
      sprintf(buffer, "%4d PULSES", pulses);
      lcd.print(buffer);
      break;
    }
  }
}
