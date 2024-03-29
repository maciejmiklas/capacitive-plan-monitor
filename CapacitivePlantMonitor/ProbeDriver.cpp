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

#include "ProbeDriver.h"

ProbeDriver::ProbeDriver()
  : suspendMs(1), lastProbeMs(0) {
}

void ProbeDriver::onEvent(BusEvent event, va_list ap) {
  if (event == BusEvent::BTN_BRIGHTNESS || event == BusEvent::BTN_ADJ_SENSOR) {
    onButtonPress();

  } else if (event == BusEvent::CYCLE) {
    onCycle();
  }
}

void ProbeDriver::onButtonPress() {
  suspendMs = util_ms();
#if LOG && LOG_PD
  log(F("%s SUSPEND"), NAME);
#endif
}

void ProbeDriver::onCycle() {
  uint32_t ms  = util_ms();
  if (ms - lastProbeMs > PD_FREQ_MS) {
    lastProbeMs = ms;
    if (ms - suspendMs > PD_PROBE_SUSPEND_MS) {
      if (suspendMs > 0) {
        suspendMs = 0;
#if LOG && LOG_PD
        log(F("%s RESUME"), NAME);
#endif
      }
      eb_fire(BusEvent::PROBE);
    }
  }
}

const char* ProbeDriver::listenerName() {
  return NAME;
}
