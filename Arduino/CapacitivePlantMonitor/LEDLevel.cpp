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
#include "LEDLevel.h"

uint8_t LEDLevel::LED_MAP[6] = { LED_OUT_1, LED_OUT_2, LED_OUT_3, LED_OUT_4, LED_OUT_5, LED_OUT_6 };

LEDLevel::LEDLevel() {
}

void LEDLevel::show(uint8_t level) {
#if LOG
  log(F("LL SHOW %d"), level);
#endif

  for (uint8_t i = 0; i < level; i++) {
    ledOn(i);
  }

  for (uint8_t i = level; i < (sizeof(LED_MAP)); i++) {
    ledOff(i);
  }
}

void LEDLevel::setup() {
  for (uint8_t i = 0; i < sizeof(LED_MAP); i++) {
    pinMode(LED_MAP[i], OUTPUT);
    ledOff(i);
  }
}

void LEDLevel::ledOff(uint8_t idx) {
  uint8_t pin = LED_MAP[idx];
#if TRACE
  log(F("LL OFF %d"), pin);
#endif

  analogWrite(pin, LOW);
  // digitalWrite(pin, LOW);
}

void LEDLevel::ledOn(uint8_t idx) {
  uint8_t pin = LED_MAP[idx];
#if TRACE
  log(F("LL ON %d"), pin);
#endif

  uint8_t brightness = 20;
  if (supportsPWM(pin)) {
    analogWrite(pin, brightness);
  } else {
    digitalWrite(pin, HIGH);
  }
}

boolean LEDLevel::supportsPWM(uint8_t pin) {
  return pin == 3 || pin == 5 || pin == 6 || pin == 9 || pin == 10 || pin == 11;
}
