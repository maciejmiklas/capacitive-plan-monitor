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
  for (int8_t lev = MI_LEVEL_OFF; lev <= MI_LEVEL_MAX; lev++) {
    show(lev);
    delay(MI_DEMO_SPEED_MS);
  }
  delay(MI_DEMO_WAIT_MIDDLE_MS);
  for (int8_t lev = MI_LEVEL_MAX; lev >= MI_LEVEL_OFF; lev--) {
    show(lev);
    delay(MI_DEMO_SPEED_MS);
  }
}

void MoistureDisplay::setup() {
  pinMode(MI_PIN_LATCH, OUTPUT);
  pinMode(MI_PIN_DATA, OUTPUT);
  pinMode(MI_PIN_CLOCK, OUTPUT);
  pinMode(MI_PIN_ENABLE, OUTPUT);

  changeBrightness(BM_BRIGHTNESS_INITIAL);
  show(MI_LEVEL_OFF);
}

void MoistureDisplay::blink(uint8_t level) {
  for (uint8_t i = 0; i < MI_BLINK_REPEAT; i++) {
    show(level);
    delay(MI_BLINK_ON_MS);
    show(MI_LEVEL_OFF);
    delay(MI_BLINK_OFF_MS);
  }
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

void MoistureDisplay::onEvent(BusEvent event, va_list ap) {
  if (event == BusEvent::BRIGHTNESS_CHANGE) {
    changeBrightness(va_arg(ap, uint16_t));

  } else if (event == BusEvent::SYSTEM_INIT) {
    setup();
  }
}

const char* MoistureDisplay::listenerName() {
  return NAME;
}
