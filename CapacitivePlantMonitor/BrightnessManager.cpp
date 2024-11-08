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
#include "EventBus.h"

BrightnessManager* refBrem;

void brem_onNextLevel(va_list ap) {   
  refBrem->onNextLevel();
}

BrightnessManager::BrightnessManager()
  : brightness(BM_BRIGHTNESS_INITIAL) {
}

void BrightnessManager::setup() {
  refBrem = this;

  eb_reg(BusEvent::BTN_BRIGHTNESS, &brem_onNextLevel);
}

void BrightnessManager::onNextLevel() {
  brightness += BM_BRIGHTNESS_CHANGE;

  if (brightness > BM_BRIGHTNESS_MAX) {
    brightness = BM_BRIGHTNESS_MIN;

  } else if (brightness + BM_BRIGHTNESS_CHANGE > BM_BRIGHTNESS_MAX) {
    eb_fire(BusEvent::BRIGHTNESS_MAX);
  }

#if LOG && LOG_BM
  log(F("%s NX %d"), NAME, brightness);
#endif

  eb_fire(BusEvent::BRIGHTNESS_CHANGE, brightness);
}