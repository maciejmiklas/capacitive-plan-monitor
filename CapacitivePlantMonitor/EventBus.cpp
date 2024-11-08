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
#include "EventBus.h"

static constexpr const char* NAME = "EB";

static const uint8_t FN_NO_IDX = 250;
static const uint8_t LISTNERS_MAX = 10;

static BusEvent BUS_LIS_TYPES[EVENTS_SIZE]{
  BusEvent::PROBE,
  BusEvent::BTN_BRIGHTNESS,
  BusEvent::BTN_ADJ_SENSOR,
  BusEvent::VCC_LOW,
  BusEvent::VCC_CRITICAL,
  BusEvent::VCC_NOMINAL,
  BusEvent::STANDBY_ON,
  BusEvent::STANDBY_OFF,
  BusEvent::BRIGHTNESS_CHANGE,
  BusEvent::BRIGHTNESS_MAX,
  BusEvent::MOISTURE_LEVEL_CHANGE,
  BusEvent::MOISTURE_ADJ_NEXT,
  BusEvent::CYCLE
};
static void((*BUS_LIST_FN[EVENTS_SIZE][LISTNERS_MAX])(va_list));
static uint8_t BUS_LIST_FN_SIZE[EVENTS_SIZE] = { 0 };

uint8_t eb_getFnIdx(BusEvent event) {
  uint8_t enentIdx = 0;
  boolean found = false;
  for (; enentIdx < EVENTS_SIZE; enentIdx++) {
    if (event == BUS_LIS_TYPES[enentIdx]) {
      found = true;
      break;
    }
  }
  if (!found) {
    enentIdx = FN_NO_IDX;
  }
  return enentIdx;
}

void eb_reg(BusEvent event, void((*fn)(va_list))) {
  uint8_t enentIdx = eb_getFnIdx(event);
  if (enentIdx == FN_NO_IDX) {
#if LOG
    log(F("%s NO EVENT %d"), NAME, event);
#endif
    return;
  }

  uint8_t fnIdx = BUS_LIST_FN_SIZE[enentIdx]++;
  if (fnIdx >= LISTNERS_MAX) {
#if LOG
    log(F("%s LN OVERFLOW"), NAME);
#endif
    return;
  }
  BUS_LIST_FN[enentIdx][fnIdx] = fn;
#if LOG && LOG_EB
  log(F("%s REG %d=%d"), NAME, event, fnIdx);
#endif
}

void eb_fire(BusEvent event, ...) {

  va_list ap;
  va_start(ap, event);

  uint8_t enentIdx = eb_getFnIdx(event);
  uint8_t eventsSize = BUS_LIST_FN_SIZE[enentIdx];

#if LOG && LOG_EB
  if (event != BusEvent::CYCLE && event != BusEvent::PROBE) {
    log(F("%s EVENT %d->%d"), NAME, event, eventsSize);
  }
#endif

  for (uint8_t fnIdx = 0; fnIdx < eventsSize; fnIdx++) {
    BUS_LIST_FN[enentIdx][fnIdx](ap);
  }
  va_end(ap);
}
