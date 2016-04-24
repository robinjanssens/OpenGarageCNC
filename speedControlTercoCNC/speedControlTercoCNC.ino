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
volatile int pulses = 0;
int ppr = 4;    //pulses per revolution
int startTime = 0;

void setup() {
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), counter, RISING);
  Serial.begin(9600);
}

void loop() {
  startTime = millis();
  pulses = 0;   // reset cycle counter
  while( millis()-startTime >= 100 ) {}
  int rps = (pulses/ppr)*10;      // revolutions per second
  int rpm = rps * 60;             // revolutions per minute
  Serial.println(rpm);
}

void counter() {
  pulses++;
}
