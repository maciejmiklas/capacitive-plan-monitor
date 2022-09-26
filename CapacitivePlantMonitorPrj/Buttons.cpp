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

#include "Buttons.h"

const static uint8_t PRESS_MS = BT_PRESS_MS;
static volatile uint8_t brightnessPressed = false;
static volatile uint32_t pressMs = 0;

static inline boolean process() {
  uint32_t ms = millis();
  if (ms - pressMs < PRESS_MS) {
    return false;
  }
  pressMs = ms;
  return true;
}

static void onBrightnessPressed() {
  if (process()) {
    brightnessPressed = true;
  }
}

Buttons::Buttons(BrightnessManager* brightnessManager)
  : brightnessManager(brightnessManager) {
}

void Buttons::init() {
  setupButton(BT_PIN_BRIGHTNESS);
  attachInterrupt(digitalPinToInterrupt(BT_PIN_BRIGHTNESS), onBrightnessPressed, FALLING);
}

void Buttons::standby() {
}

void Buttons::wakeup() {
}

void Buttons::cycle() {
  if (brightnessPressed) {
    brightnessManager->nextLevel();
    brightnessPressed = false;
  }
}

const char* Buttons::name() {
  return NAME;
}

void Buttons::setupButton(uint8_t pin) {
  pinMode(pin, INPUT);
  digitalWrite(pin, HIGH);  // enable pull-up resistor
}
