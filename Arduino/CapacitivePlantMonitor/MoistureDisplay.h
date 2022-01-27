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
#ifndef MOISTURE_DISPLAY_H
#define MOISTURE_DISPLAY_H

#include <Arduino.h>
#include <Servo.h>
#include "PIN.h"
#include "ArdLog.h"

class MoistureDisplay {
public:
  MoistureDisplay();
  void setup();
  void reset();

  /** #level goes from 0 to 180. */
  void show(uint8_t level);
 
private:
  const static uint8_t SERVO_PIN = P_D9;
  Servo servo;
};

#endif  // MOISTURE_DISPLAY_H