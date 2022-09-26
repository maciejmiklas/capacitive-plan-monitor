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

#include "BrightnessManager.h"

BrightnessManager::BrightnessManager()
  : registeredCount(0), brightness(BM_BRIGHTNESS_INITIAL) {
}

void BrightnessManager::registerListener(BrightnessListener* listener) {
  listeners[registeredCount++] = listener;
}

void BrightnessManager::nextLevel() {
  brightness += BM_BRIGHTNESS_CHANGE;
  if (brightness > BM_BRIGHTNESS_MAX) {
    brightness = BM_BRIGHTNESS_MIN;
  }

#if LOG && LOG_BM
  log(F("%s NX %d"), NAME, brightness);
#endif

  for (uint8_t i = 0; i < registeredCount; i++) {
    listeners[i]->changeBrightness(brightness);
  }
}