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
#include "MoistureDisplay.h"

MoistureDisplay::MoistureDisplay()
  : moistureLevel(MI_LEVEL_OFF) {
}

void MoistureDisplay::onEvent(BusEvent event, va_list ap) {
  if (event == BusEvent::BRIGHTNESS_CHANGE) {
    onChangeBrightness(va_arg(ap, uint16_t));

  } else if (event == BusEvent::MOISTURE_ADJ_NEXT) {
    onMoistureAdjust(va_arg(ap, uint16_t));

  } else if (event == BusEvent::MOISTURE_LEVEL_CHANGE) {
    onMoistureLevelChange(va_arg(ap, uint16_t));

  } else if (event == BusEvent::VCC_LOW) {
    onPowerLow();

  } else if (event == BusEvent::VCC_CRITICAL) {
    onPowerCritical();

  } else if (event == BusEvent::STANDBY_ON) {
    onStandByOn();

  } else if (event == BusEvent::STANDBY_OFF) {
    onStandByOff();
  }
}

void MoistureDisplay::onMoistureLevelChange(uint8_t level) {
  show(level);
  moistureLevel = level;
}

void MoistureDisplay::onMoistureAdjust(uint8_t level) {
  blink(level);
}

void MoistureDisplay::onPowerLow() {
  changeBrightness(BM_BRIGHTNESS_MIN);
}

void MoistureDisplay::onPowerCritical() {
  changeBrightness(BM_BRIGHTNESS_OFF);
}

void MoistureDisplay::onStandByOn() {
  ledsOff();
}

void MoistureDisplay::onStandByOff() {
  showCurrentMoistureLevel();
}

void MoistureDisplay::onChangeBrightness(uint8_t level) {
  changeBrightness(level);
  show(MI_LEVEL_MAX);
  delay(MI_BRIGHTNES_ON_DELAY);
  showCurrentMoistureLevel();
}

void MoistureDisplay::demo() {
  for (int8_t lev = MI_LEVEL_OFF; lev <= MI_LEVEL_MAX; lev++) {
    show(lev);
    delay(MI_DEMO_DELAY);
  }
  delay(MI_DEMO_MIDDLE_DELAY);
  for (int8_t lev = MI_LEVEL_MAX; lev >= MI_LEVEL_OFF; lev--) {
    show(lev);
    delay(MI_DEMO_DELAY);
  }
}

void MoistureDisplay::demosDone() {
  showCurrentMoistureLevel();
}

void MoistureDisplay::showCurrentMoistureLevel() {
  show(moistureLevel);
};

void MoistureDisplay::setup() {
  pinMode(MI_PIN_LATCH, OUTPUT);
  pinMode(MI_PIN_DATA, OUTPUT);
  pinMode(MI_PIN_CLOCK, OUTPUT);
  pinMode(MI_PIN_ENABLE, OUTPUT);

  changeBrightness(BM_BRIGHTNESS_INITIAL);
  ledsOff();
}

void MoistureDisplay::blink(uint8_t level) {
  for (uint8_t i = 0; i < MI_BLINK_REPEAT; i++) {
    show(level);
    delay(MI_BLINK_ON_DELAY);
    ledsOff();
    delay(MI_BLINK_OFF_DELAY);
  }
  showCurrentMoistureLevel();
}

void MoistureDisplay::ledsOff() {
  show(MI_LEVEL_OFF);
}

void MoistureDisplay::show(uint8_t level) {
#if LOG && LOG_MI
  log(F("%s SH %d"), NAME, level);
#endif

  uint8_t leds = 0;
  for (uint8_t i = 0; i < level; i++) {
    bitSet(leds, i);
  }

  digitalWrite(MI_PIN_LATCH, LOW);
  shiftOut(MI_PIN_DATA, MI_PIN_CLOCK, LSBFIRST, leds);
  digitalWrite(MI_PIN_LATCH, HIGH);
}

void MoistureDisplay::changeBrightness(uint8_t level) {
  analogWrite(MI_PIN_ENABLE, BM_BRIGHTNESS_MAX - level);
}

const char* MoistureDisplay::listenerName() {
  return NAME;
}
