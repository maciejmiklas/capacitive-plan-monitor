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
#ifndef BRIGHTNESS_MANAGER_H
#define BRIGHTNESS_MANAGER_H

#include "BrightnessListener.h"
#include "ArdLog.h"
#include "LED.h"

class BrightnessManager {
public:
  BrightnessManager(LED* led);
  void registerListener(BrightnessListener* listener);
  void nextLevel();

private:
  const static uint8_t MAX_LISTENERS = 2;
  static constexpr const char* NAME = "BM";

  BrightnessListener* listeners[MAX_LISTENERS];
  uint8_t registeredCount;
  uint16_t brightness;
  LED* led;

  void blink();
};

#endif  // BRIGHTNESS_MANAGER_H