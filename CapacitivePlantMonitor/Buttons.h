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
#ifndef BUTTONS_H
#define BUTTONS_H

#include "BrightnessManager.h"
#include "ArdLog.h"
#include "MoistureDriver.h"
#include "LED.h"
#include "EventBus.h"
#include "Device.h"

class Buttons : public Device {
public:
  Buttons();

  void onCycle();

  // from Device.h
  void setup();

private:
  static constexpr const char* NAME = "BT";
  uint32_t processMs;

  void setupButton(uint8_t pin);
  void readButtons();
};

#endif  // BUTTONS_H