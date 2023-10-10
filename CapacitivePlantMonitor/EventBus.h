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

enum class BusEvent {
  PROBE = 11,

  BTN_BRIGHTNESS = 21,
  BTN_ADJ_SENSOR = 22,

  VCC_LOW = 31,
  VCC_CRITICAL = 32,
  VCC_NOMINAL = 33,

  STANDBY_ON = 41,
  STANDBY_OFF = 42,

  /** Param: brightness as uint_16, value: BM_BRIGHTNESS_MIN <-> BM_BRIGHTNESS_MAX */
  BRIGHTNESS_CHANGE = 50,
  BRIGHTNESS_MAX = 51,

  /** Param: sensor read in mv in dependency of actual VCC level, see MI_LEVEL_MAP for details */
  MOISTURE_LEVEL_CHANGE = 60,

  /** Param: current aductment as value beetwen MI_ADJUST_LEV_MIN and MI_ADJUST_LEV_MAX */
  MOISTURE_ADJ_NEXT = 61,

  CYCLE = 255,
};

class BusListener {
public:
  virtual void onEvent(BusEvent event, va_list ap) = 0;
  virtual const char* listenerName() = 0;

protected:
  virtual ~BusListener();
  BusListener();
};

void eb_register(BusListener* listener);
void eb_fire(BusEvent event, ...);

#endif /* EVENTBUS_H_ */
