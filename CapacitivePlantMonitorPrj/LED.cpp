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
#include "LED.h"

LED::LED() {
}

void LED::setup() {
  for (uint8_t pin = FIRST_PIN; pin <= LAST_PIN; pin++) {
    pinMode(pin, OUTPUT);
    analogWrite(pin, LOW);
  }
}

void LED::demo() {
  for (uint8_t bl = 0; bl < LE_DEMO_BLNIKS; bl++) {
    for (uint8_t pin = FIRST_PIN; pin <= LAST_PIN; pin++) {
      LedPin pinEn = static_cast<LedPin>(pin);
      on(pinEn);
      delay(LE_DEMO_DELAY_MS);
      off(pinEn);
      delay(LE_DEMO_DELAY_MS);
    }
  }
}

void LED::changeBrightness(uint8_t level) {
  BrightnessListener::changeBrightness(level);
}

const char* LED::name() {
  return NAME;
}

void LED::off(LedPin led) {
  uint8_t pin = led;
#if LOG && LOG_LE
  log(F("%s OFF %d"), NAME, pin);
#endif
  analogWrite(pin, LOW);
}

void LED::on(LedPin led) {
  uint8_t pin = led;
#if LOG && LOG_LE
  log(F("%s ON %d %d"), NAME, pin, currentBrightness());
#endif
  analogWrite(pin, currentBrightness());
}

void LED::standby() {
}

void LED::wakeup() {
}

void LED::cycle() {
}