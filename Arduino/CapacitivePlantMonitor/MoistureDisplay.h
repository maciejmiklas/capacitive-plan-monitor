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

#include "Config.h"
#include "ArdLog.h"
#include "Device.h"
#include "Brightness.h"

/** Moisture level LED display base on 74HC595 */
class MoistureDisplay : public Device{
public:
  /** Min level inclusive. */
  const static uint8_t MOISTURE_MIN = 1;

  /** Max level inclusive. */
  const static uint8_t MOISTURE_MAX = 7;

  MoistureDisplay();

  /** #level goes from #MOISTURE_MIN to #MOISTURE_MAX inclusive -> from dry to wet. */
  void show(uint8_t level);
  
  void setBrightness(Brightness brightness);

  // from Device.h
  virtual void init();
  virtual void demo();
  virtual void standby();
  virtual void wakeup();
  virtual void cycle();
  virtual const char* name();

private:
  /** SRCLK (Shift Register Clock) - PIN 11 on 74HC595 */
  const uint8_t SR_CLOCK = PIN_MD_CLOCK;

  /** RCLK (Register Clock / Latch) - PIN 12 on 74HC595 */
  const uint8_t SR_LATCH = PIN_MD_LATCH;

  /** SER (Serial Input) - PIN 14 on 74HC595 */
  const uint8_t SR_DATA = PIN_MD_DATA;

  /** OE (Output Enable) - PIN 13 on 74HC595 */
  const uint8_t SR_ENABLE = PIN_MD_ENABLE;

  const static uint16_t DEMO_LED_ON_MS = 100;

  static constexpr const char* NAME = "MD";
  uint8_t brightness;
};

#endif  // MOISTURE_DISPLAY_H