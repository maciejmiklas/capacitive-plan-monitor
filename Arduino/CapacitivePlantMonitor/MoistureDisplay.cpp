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
#include "MoistureDisplay.h"

MoistureDisplay::MoistureDisplay()
  : brightness(INITIAL_BRIGHTNESS) {
}

void MoistureDisplay::demo() {
  for (uint8_t lev = MOISTURE_MIN; lev <= MOISTURE_MAX; lev++) {
    show(lev);
    delay(DEMO_LED_ON_MS);
  }

    for (uint8_t lev = MOISTURE_MAX; lev >= MOISTURE_MIN; lev--) {
    show(lev);
    delay(DEMO_LED_ON_MS);
  }
}

void MoistureDisplay::init() {
  pinMode(SR_LATCH, OUTPUT);
  pinMode(SR_DATA, OUTPUT);
  pinMode(SR_CLOCK, OUTPUT);

  pinMode(SR_ENABLE, OUTPUT);
}

const char* MoistureDisplay::name() {
  return NAME;
}

void MoistureDisplay::standby() {
}

void MoistureDisplay::wakeup() {
}

void MoistureDisplay::cycle() {
}

void MoistureDisplay::show(uint8_t level) {
#if LOG
  log(F("%s SHOW %d"), NAME, level);
#endif
  uint8_t leds = 0;
  for (uint8_t i = 0; i < level; i++) {
    bitSet(leds, i);
  }

  digitalWrite(SR_LATCH, LOW);
  shiftOut(SR_DATA, SR_CLOCK, LSBFIRST, leds);
  digitalWrite(SR_LATCH, HIGH);
}

void MoistureDisplay::setBrightness(Brightness brightness) {
  analogWrite(SR_ENABLE, 255 - brightness);
}