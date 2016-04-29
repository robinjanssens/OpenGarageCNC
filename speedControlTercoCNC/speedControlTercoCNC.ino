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

const byte interruptPin = 2;
const float ppr = 4.0;                          // pulses per revolution
const int sampleTime = 100;                     // count for this amount of ms
volatile int pulses = 0;

void counter() {
  pulses++;
}

void setup() {
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), counter, RISING);
  Serial.begin(9600);
}

void loop() {
  unsigned long startTime;
  unsigned long testTime;
  float rpm;
  
  startTime = millis();
  pulses = 0;                                   // reset pulse counter
  while(1) {
    testTime = millis();
    if(testTime - startTime >= sampleTime) {
      rpm = (pulses / ppr) * (1000 / sampleTime) * 60; // revolutions per minute
      Serial.println(rpm);
      Serial.println(pulses);
      break;
    }
  }
}
