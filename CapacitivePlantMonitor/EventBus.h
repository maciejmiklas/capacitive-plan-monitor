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
#ifndef EVENTBUS_H_
#define EVENTBUS_H_

#include "Arduino.h"
#include "ArdLog.h"

enum class BusEvent: uint8_t {

  CYCLE = 0,
  PROBE,

  BTN_BRIGHTNESS,
  BTN_ADJ_SENSOR,

  VCC_LOW,
  VCC_CRITICAL,
  VCC_NOMINAL,

  STANDBY_ON,
  STANDBY_OFF ,

  /** Param: brightness as uint_16, value: BM_BRIGHTNESS_MIN <-> BM_BRIGHTNESS_MAX */
  BRIGHTNESS_CHANGE,
  BRIGHTNESS_MAX,

  /** Param: sensor read in mv in dependency of actual VCC level, see MI_LEVEL_MAP for details */
  MOISTURE_LEVEL_CHANGE,

  /** Param: current aductment as value beetwen MI_ADJUST_LEV_MIN and MI_ADJUST_LEV_MAX */
  MOISTURE_ADJ_NEXT,

  /* Number of elements in this enum. */
  COUNT
};

void eb_fire(BusEvent event, ...);
void eb_reg(BusEvent event, void (*func)(va_list));

#endif /* EVENTBUS_H_ */
