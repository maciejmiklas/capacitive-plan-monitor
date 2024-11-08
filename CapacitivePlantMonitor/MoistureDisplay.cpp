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

MoistureDisplay* refMdisp;

void mdisp_onChangeBrightness(va_list ap) {
  refMdisp->onChangeBrightness(va_arg(ap, uint16_t));
}

void mdisp_onMoistureAdjust(va_list ap) {
  refMdisp->onMoistureAdjust(va_arg(ap, uint16_t));
}

void mdisp_onMoistureLevelChange(va_list ap) {
  refMdisp->onMoistureLevelChange(va_arg(ap, uint16_t));
}

void mdisp_onPowerLow(va_list ap) {
  refMdisp->onPowerLow();
}

void mdisp_onPowerCritical(va_list ap) {
  refMdisp->onPowerCritical();
}

void mdisp_onStandByOn(va_list ap) {
  refMdisp->onStandByOn();
}

void mdisp_onStandByOff(va_list ap) {
  refMdisp->onStandByOff();
}

MoistureDisplay::MoistureDisplay()
  : moistureLevel(MI_LEVEL_OFF) {
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

  refMdisp = this;

  eb_reg(BusEvent::BRIGHTNESS_CHANGE, &mdisp_onChangeBrightness);
  eb_reg(BusEvent::MOISTURE_ADJ_NEXT, &mdisp_onMoistureAdjust);
  eb_reg(BusEvent::MOISTURE_LEVEL_CHANGE, &mdisp_onMoistureLevelChange);
  eb_reg(BusEvent::VCC_LOW, &mdisp_onPowerLow);
  eb_reg(BusEvent::VCC_CRITICAL, &mdisp_onPowerCritical);
  eb_reg(BusEvent::STANDBY_ON, &mdisp_onStandByOn);
  eb_reg(BusEvent::STANDBY_OFF, &mdisp_onStandByOff);
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