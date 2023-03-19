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

static volatile uint8_t brightnessPressed = false;
static volatile uint32_t processMs = 0;

static inline boolean process() {
  uint32_t ms = millis();
  if (ms - processMs < BT_PRESS_MS) {
    return false;
  }
  processMs = ms;
  return true;
}

static void onBrightnessPressed() {
  brightnessPressed = true;
}

Buttons::Buttons() {
}

void Buttons::setup() {
  setupButton(BT_PIN_BRIGHTNESS);
  setupButton(BT_PIN_MI_ADJUST);

  // there is only one PIN left with interupt support
  attachInterrupt(digitalPinToInterrupt(BT_PIN_BRIGHTNESS), onBrightnessPressed, FALLING);
}

void Buttons::cycle() {
  if (!process()) {
    return;
  }
  if (brightnessPressed) {  // set by interput
#if LOG && LOG_BT
    log(F("%s BR"), NAME);
#endif
    eb_fire(BusEvent::BTN_BRIGHTNESS);
    brightnessPressed = false;

  } else if (digitalRead(BT_PIN_MI_ADJUST) == LOW) {  // non-interupt pin
#if LOG && LOG_BT
    log(F("%s AD"), NAME);
#endif
    eb_fire(BusEvent::BTN_BRIGHTNESS);
  }
}

void Buttons::setupButton(uint8_t pin) {
  pinMode(pin, INPUT);
  digitalWrite(pin, HIGH);  // enable pull-up resistor
}

const char* Buttons::listenerName() {
  return NAME;
}

void Buttons::onEvent(BusEvent event, va_list ap) {
  if (event == BusEvent::SYSTEM_INIT) {
    setup();

  } else if (event == BusEvent::CYCLE) {
    cycle();
  }
}
