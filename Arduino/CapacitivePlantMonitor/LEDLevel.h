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
#ifndef LED_LEVEL_H
#define LED_LEVEL_H

#include "Arduino.h"
#include "ArdLog.h"

class LEDLevel {
public:
  LEDLevel();

  void setup();

  /** #level is between 1 and 6 */
  void show(uint8_t level);

private:
  void ledOff(uint8_t ixd);
  void ledOn(uint8_t ixd);
  boolean supportsPWM(uint8_t pin);

  // LEDs are connected to Digital PWM out in order to controll brightness
  static const uint8_t LED_OUT_6 = 12;
  static const uint8_t LED_OUT_5 = 11;
  static const uint8_t LED_OUT_4 = 10;
  static const uint8_t LED_OUT_3 = 9;
  static const uint8_t LED_OUT_2 = 6;
  static const uint8_t LED_OUT_1 = 5;
  static uint8_t LED_MAP[6];
};


#endif  // LED_LEVEL_H