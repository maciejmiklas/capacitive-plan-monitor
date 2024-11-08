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

#include "Arduino.h"
#include "ArdLog.h"
#include "Config.h"
#include "EventBus.h"
#include "Util.h"
#include "Device.h"

#ifndef LED_BLINK
#define LED_BLINK

class LEDBlink : public Device {

public:
  LEDBlink(uint8_t pin, uint16_t onDelay, uint16_t offDelay, uint8_t brightnessOn, uint8_t brightnessOff);
  void on();
  void off();

 void onCycle();

   // from Device.h
  void setup();

private:
  static constexpr const char* NAME = "LB";

  uint16_t onDelay;
  uint16_t offDelay;
  uint8_t pin;
  uint8_t brightnessOn;
  uint8_t brightnessOff;
  boolean ledOn;
  boolean enabled;
  uint32_t lastUpdateMs;
};

#endif  // edd LED_BLINK