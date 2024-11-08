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
#include "Demo.h"
#include "EventBus.h"
#include "Device.h"

/** Moisture level LED display base on 74HC595 */
class MoistureDisplay : public Demo, public Device {
public:

  MoistureDisplay();

  /** #level goes from #MI_LEVEL_MIN to #MI_LEVEL_MAX inclusive -> from dry to wet. */
  void show(uint8_t level);

  /** #level goes from #MI_LEVEL_MIN to #MI_LEVEL_MAX inclusive -> from dry to wet. */
  void blink(uint8_t level);

  // from Demo.h
  void demo();
  void demosDone();

  // from Device.h
  void setup();

  void onChangeBrightness(uint8_t level);
  void onMoistureAdjust(uint8_t level);
  void onMoistureLevelChange(uint8_t level);

  void onPowerLow();
  void onStandByOn();
  void onStandByOff();
  void onPowerCritical();

private:
  uint8_t moistureLevel;
  static constexpr const char* NAME = "MI";

  void changeBrightness(uint8_t level);
  void showCurrentMoistureLevel();
  void ledsOff();


};

#endif  // MOISTURE_DISPLAY_H