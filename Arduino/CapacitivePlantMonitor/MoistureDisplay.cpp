/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "MoistureDisplay.h"

MoistureDisplay::MoistureDisplay()
  : servo() {
}

void MoistureDisplay::setup() {
  servo.attach(SERVO_PIN);
}

void MoistureDisplay::reset() {
}

void MoistureDisplay::show(uint8_t level) {
  uint8_t pos = 0;

  log(F("POS %d"), pos);
  servo.write(pos);
  delay(2000);

  pos = 90;
  log(F("POS %d"), pos);
  servo.write(90);
  delay(2000);

  /*
    for (uint8_t pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo.write(pos);              
    delay(20);                       
  }
  for (uint8_t pos = 180; pos >= 0; pos -= 1) { 
    servo.write(pos);             
    delay(20);                      
  }*/
}