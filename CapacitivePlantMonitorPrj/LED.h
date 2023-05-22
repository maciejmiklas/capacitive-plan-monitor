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
#include "Demo.h"
#include "EventBus.h"
#include "Device.h"
#include "LEDBlink.h"

// Enum values are out PINs
enum LedPin { AWAKE = LE_PIN_AWAKE,
              PWR_LOW = LE_PIN_PWR_LOW };

class LED : public Demo, public BusListener, public Device {

public:
  LED();

  void on(LedPin led);
  void on(LedPin led, uint8_t brightness);
  void off(LedPin led);

  // from Demo.h
  void demo();

  // from EventBus.h
  void onEvent(BusEvent event, va_list ap);
  const char* listenerName();

  // from Device.h
  void setup();

private:
  const static uint8_t FIRST_PIN = LedPin::AWAKE;
  const static uint8_t LAST_PIN = LedPin::PWR_LOW;
  static constexpr const char* NAME = "LE";
  uint16_t brightness;
  LEDBlink* powerLow;

  void onBrightnessChange(uint8_t level);
  void onButtonPress();
  void onMaxBrightness();
  void onPowerLow();
  void onPowerNominal();
  void onStandByOn();
  void onStandByOff();
  void onCycle();
};

#endif  // LED_H
