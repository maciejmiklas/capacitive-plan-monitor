#include "Arduino.h"
/*
   Licensed to the Apache Software Foundation (ASF) under one or more
   contributor license agreements.  See the NOTICE file distributed with
   this work for additional information regarding copyright ownership.
   The ASF licenses this file to You under the Apache License, Version 2.0
   (the "License"); you may not use this file except in compliance with
   the License.  You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#include "MoistureDriver.h"

MoistureDriver::MoistureDriver(MoistureSensor* sensor, VCCProvider* vcc)
  : sensor(sensor), vcc(vcc), adjust(MI_ADJUST_INIT), adjustLevel(MI_ADJUST_LEV_INIT), adjustUp(true), adjustPressMs(0), currentLevel(0) {
}

void MoistureDriver::onEvent(BusEvent event, va_list ap) {
  if (event == BusEvent::PROBE) {
    onProbe();

  } else if (event == BusEvent::BTN_ADJ_SENSOR) {
    onAdjustyNextLevel();

  } else if (event == BusEvent::STANDBY_OFF) {
    onStandbyOff();
  }
}

void MoistureDriver::onProbe() {
  probe(false);
}

void MoistureDriver::onStandbyOff() {
  adjustUp = true;
  probe(true);
}

void MoistureDriver::probe(boolean force) {
  uint8_t level = getLevel();
  if (force || sub_u16(level, currentLevel) >= MI_MIN_CHANGE_LEVEL) {
#if LOG && LOG_MD
    log(F("%s LEVEL %d->%d"), NAME, currentLevel, level);
#endif
    eb_fire(BusEvent::MOISTURE_LEVEL_CHANGE, level);
    currentLevel = level;
  }
}

uint8_t MoistureDriver::getLevel() {
  uint16_t sr = sensor->read();                       // 0-1023
  uint16_t smv = (long)sr * (long)vcc->mv() / 1023L;  // sensor read in mv
  smv *= adjust;

  uint16_t dry = MI_LEVEL_MAP[0][1];
  uint16_t wet = MI_LEVEL_MAP[0][2];
  uint16_t powerMv = vcc->mv();  // current baterry charge in mv
  for (uint8_t idx = 0; idx < MI_LEVEL_MAP_SIZE - 1; idx++) {
    const uint16_t* el = MI_LEVEL_MAP[idx];
    const uint16_t* en = MI_LEVEL_MAP[idx + 1];
    if (el[0] >= powerMv && en[0] < powerMv) {
      dry = en[1];
      wet = en[2];
    }
  }
  uint8_t level = MI_LEVEL_OFF;

  if (smv >= dry) {
    level = MI_LEVEL_MIN;

  } else if (smv <= wet) {
    level = MI_LEVEL_MAX;

  } else {
    level = map(smv, dry, wet, MI_LEVEL_MIN, MI_LEVEL_MAX);
  }

#if LOG && LOG_MD
  log(F("%s PWR:%d [%d,%d,%d]=>%d"), NAME, powerMv, dry, smv, wet, level);
#endif
  return level;
}

void MoistureDriver::onAdjustyNextLevel() {
  if (adjustPressMs == 0 || (util_ms() - adjustPressMs > MI_ADJUST_SHOW_MS)) {
    ;
  } else if (adjustLevel == MI_ADJUST_LEV_MAX) {
    adjustUp = false;
    adjustLevel = MI_ADJUST_LEV_INIT;
    adjust = MI_ADJUST_INIT;

  } else if (adjustLevel == MI_ADJUST_LEV_MIN) {
    adjustUp = true;
    adjustLevel = MI_ADJUST_LEV_INIT;
    adjust = MI_ADJUST_INIT;

  } else if (adjustUp) {
    adjustLevel++;
    adjust -= MI_ADJUST_STEP;

  } else {
    adjustLevel--;
    adjust += MI_ADJUST_STEP;
  }

  eb_fire(BusEvent::MOISTURE_ADJ_NEXT, adjustLevel);
  adjustPressMs = util_ms();

#if LOG && LOG_MD
  char sb[6];
  dtostrf(adjust, 2, 2, sb);
  log(F("%s ADJ %d->%s"), NAME, adjustLevel, sb);
#endif
}

const char* MoistureDriver::listenerName() {
  return NAME;
}
