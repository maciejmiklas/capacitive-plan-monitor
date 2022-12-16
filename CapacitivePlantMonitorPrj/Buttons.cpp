#include "Arduino.h"

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

static volatile uint8_t brightnessPressed = false;
static volatile uint8_t adjustPressed = false;
static volatile uint32_t pressMs = 0;

static inline boolean process() {
  uint32_t ms = millis();
  if (ms - pressMs < BT_PRESS_MS) {
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

static void onAdjustPressed() {
  if (process()) {
    adjustPressed = true;
  }
}

Buttons::Buttons(BrightnessManager* brightnessManager, MoistureDriver* moistureDriver, LED* led)
  : brightnessManager(brightnessManager), moistureDriver(moistureDriver), led(led) {
}

void Buttons::init() {
  setupButton(BT_PIN_BRIGHTNESS);
  attachInterrupt(digitalPinToInterrupt(BT_PIN_BRIGHTNESS), onBrightnessPressed, FALLING);

  setupButton(BT_PIN_ADJUST);
  attachInterrupt(digitalPinToInterrupt(BT_PIN_ADJUST), onAdjustPressed, FALLING);
}

void Buttons::cycle() {
  if (brightnessPressed) {
    blinkOnPress();
    brightnessManager->nextLevel();
    brightnessPressed = false;
  }
  if (adjustPressed) {
    blinkOnPress();
    moistureDriver->adjustyNextLevel();
    adjustPressed = false;
  }
}

void Buttons::blinkOnPress() {
  for (uint8_t i = 0; i < BT_PRESS_BLINK_REPEAT; i++) {
    led->off(LedPin::AWAKE);
    delay(BT_PRESS_BLINK_OFF_MS);
    led->on(LedPin::AWAKE);
    delay(BT_PRESS_BLINK_ON_MS);
  }
  led->on(LedPin::AWAKE);
}

void Buttons::setupButton(uint8_t pin) {
  pinMode(pin, INPUT);
  digitalWrite(pin, HIGH);  // enable pull-up resistor
}

const char* Buttons::name() {
  return NAME;
}

void Buttons::standby() {
}

void Buttons::wakeup() {
}
