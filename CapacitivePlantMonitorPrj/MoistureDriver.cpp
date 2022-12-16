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
#include "MoistureDriver.h"


MoistureDriver::MoistureDriver(MoistureSensor* sensor, MoistureDisplay* display, PowerProvider* power)
  : sensor(sensor), display(display), power(power) {
}

void MoistureDriver::cycle() {
  display->show(getLevel());
}

uint8_t MoistureDriver::getLevel() {
  uint16_t sr = sensor->read();
  uint16_t smv = (long)sr * (long)power->mv() / 1023L;  // sensor read in mv

  uint16_t dry = MI_LEVEL_MAP[0][1];
  uint16_t wet = MI_LEVEL_MAP[0][2];
  uint16_t powerMv = power->mv();
  for (uint8_t idx = 0; idx < MI_LEVEL_MAP_SIZE - 1; idx++) {
    const uint16_t* el = MI_LEVEL_MAP[idx];
    const uint16_t* en = MI_LEVEL_MAP[idx + 1];
    if (el[0] >= powerMv && en[0] < powerMv) {
      if (el[0] - powerMv > powerMv - en[0]) {
        dry = en[1];
        wet = en[2];
      } else {
        dry = el[1];
        wet = el[2];
      }
    }
  }
  uint8_t level = map(smv, dry, wet, MI_LEVEL_MIN, MI_LEVEL_MAX);

#if LOG && LOG_MD
  log(F("%s MAP %d[%d,%d,%d]=%d"), NAME, sr, powerMv, dry, wet, level);
#endif

  return level;
}


void MoistureDriver::adjustyNextLevel() {
  display->blink(6);
}

void MoistureDriver::wakeup() {
}

void MoistureDriver::standby() {
}

void MoistureDriver::init() {
}

const char* MoistureDriver::name() {
  return NAME;
}