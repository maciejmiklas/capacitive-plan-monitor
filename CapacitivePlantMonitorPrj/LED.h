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
#ifndef LED_H
#define LED_H

#include "ArdLog.h"
#include "Config.h"
#include "Device.h"
#include "BrightnessListener.h"

// Enum values are out PINs
enum LedPin { MESURE = LE_PIN_MESURE,
              PWR_LOW = LE_PIN_PWR_LOW };

class LED: public Device, public BrightnessListener {
public:
  LED();

  void on(LedPin led);
  void off(LedPin led);
   
  // from BrightnessListener.h
  void changeBrightness(uint8_t level);

  // from Device.h
  void init();
  void demo();
  void standby();
  void wakeup();
  void cycle();
  const char* name();

private:
  const static uint8_t FIRST_PIN = LedPin::MESURE;
  const static uint8_t LAST_PIN = LedPin::PWR_LOW;
  static constexpr const char* NAME = "LE";
};

#endif  // LED_H