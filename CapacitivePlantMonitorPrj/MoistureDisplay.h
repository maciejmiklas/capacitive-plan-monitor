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
#include "Demo.h"
#include "EventBus.h"

/** Moisture level LED display base on 74HC595 */
class MoistureDisplay : public Demo, public BusListener {
public:

  MoistureDisplay();

  /** #level goes from #MOISTURE_MIN to #MOISTURE_MAX inclusive -> from dry to wet. */
  void show(uint8_t level);

  /** #level goes from #MOISTURE_MIN to #MOISTURE_MAX inclusive -> from dry to wet. */
  void blink(uint8_t level);

  // from EventBus.h
  void onEvent(BusEvent event, va_list ap);
  const char* listenerName();

  // from Demo.h
  void demo();

private:
  static constexpr const char* NAME = "MI";
  void changeBrightness(uint8_t level);
  void setup();
};

#endif  // MOISTURE_DISPLAY_H