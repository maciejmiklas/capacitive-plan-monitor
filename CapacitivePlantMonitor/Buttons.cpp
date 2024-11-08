/*
   Licensed to the Apache Software Foundation (ASF) under one or more
   contributor license agreements.  See the NOTICE file distributed with
   this work for additional information regarding copyright ownership.
   The ASF licenses this file to You under the Apache License, Version 2.0
   (the "License"); you may not use this file except in compliance with
   the License.  You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "Buttons.h"

Buttons* refButtons;

void buttons_onCycle(va_list ap) {
  refButtons->onCycle();
}

Buttons::Buttons()
  : processMs(0) {
}

void Buttons::setup() {
  setupButton(BT_PIN_BRIGHTNESS);
  setupButton(BT_PIN_MI_ADJUST);

  refButtons = this;
  eb_reg(BusEvent::CYCLE, &buttons_onCycle);
}

void Buttons::onCycle() {
  if (util_ms() - processMs < BT_PRESS_MS) {
    return;
  }
  readButtons();
  processMs = util_ms();
}

void Buttons::readButtons() {
  if (digitalRead(BT_PIN_BRIGHTNESS) == LOW) {
#if LOG && LOG_BT
    log(F("%s BRIGHTNESS"), NAME);
#endif
    eb_fire(BusEvent::BTN_BRIGHTNESS);

  } else if (digitalRead(BT_PIN_MI_ADJUST) == LOW) {
#if LOG && LOG_BT
    log(F("%s ADJUST"), NAME);
#endif
    eb_fire(BusEvent::BTN_ADJ_SENSOR);
  }
}

void Buttons::setupButton(uint8_t pin) {
  pinMode(pin, INPUT);
  digitalWrite(pin, HIGH);  // enable pull-up resistor
}
