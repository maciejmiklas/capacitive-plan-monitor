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

MoistureDisplay::MoistureDisplay() {
}

void MoistureDisplay::demo() {
  for (int8_t lev = MOISTURE_OFF; lev <= MOISTURE_MAX; lev++) {
    show(lev);
    delay(MD_DEMO_SPEED_MS);
  }
  delay(200);
  for (int8_t lev = MOISTURE_MAX; lev >= MOISTURE_OFF; lev--) {
    show(lev);
    delay(MD_DEMO_SPEED_MS);
  }
}

void MoistureDisplay::init() {
  pinMode(MD_PIN_LATCH, OUTPUT);
  pinMode(MD_PIN_DATA, OUTPUT);
  pinMode(MD_PIN_CLOCK, OUTPUT);
  pinMode(MD_PIN_ENABLE, OUTPUT);

  changeBrightness(currentBrightness());

  show(MOISTURE_OFF);
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
#if LOG && LOG_MD
  log(F("%s SHOW %d"), NAME, level);
#endif
  uint8_t leds = 0;
  for (uint8_t i = 0; i < level; i++) {
    bitSet(leds, i);
  }

  digitalWrite(MD_PIN_LATCH, LOW);
  shiftOut(MD_PIN_DATA, MD_PIN_CLOCK, LSBFIRST, leds);
  digitalWrite(MD_PIN_LATCH, HIGH);
}

void MoistureDisplay::changeBrightness(uint8_t level) {
  BrightnessListener::changeBrightness(level);

  log(F(">>>> %d"), level);
  analogWrite(MD_PIN_ENABLE, BM_BRIGHTNESS_MAX - level);
}