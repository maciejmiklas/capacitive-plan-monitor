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

ProbeDriver* refPdriv;

void pdriv_onButtonPress(va_list ap) {
  refPdriv->onButtonPress();
}

void pdriv_onCycle(va_list ap) {
  refPdriv->onCycle();
}

void pdriv_onStandByOff(va_list ap) {
  refPdriv->onStandByOff();
}

ProbeDriver::ProbeDriver()
  : probeMs(PD_FREQ_MS), lastProbeMs(0) {
}

void ProbeDriver::setup() {
  refPdriv = this;   
  eb_reg(BusEvent::BTN_BRIGHTNESS, &pdriv_onButtonPress);
  eb_reg(BusEvent::BTN_ADJ_SENSOR, &pdriv_onButtonPress);
  eb_reg(BusEvent::CYCLE, &pdriv_onCycle);
  eb_reg(BusEvent::STANDBY_OFF, &pdriv_onStandByOff);
}

void ProbeDriver::onStandByOff() {
  lastProbeMs = util_ms();
  probeMs = PD_PROBE_SUSPEND_STANDBY_MS;
}

void ProbeDriver::onButtonPress() {
  lastProbeMs = util_ms();
  probeMs = PD_PROBE_SUSPEND_BUTTON_MS;
#if LOG && LOG_PD
  log(F("%s SUSPEND"), NAME);
#endif
}

void ProbeDriver::onCycle() {
  uint32_t ms  = util_ms();
  if (ms - lastProbeMs > probeMs) {
    probeMs = PD_FREQ_MS; // reset to default probe frequency
    lastProbeMs = ms;
      eb_fire(BusEvent::PROBE);
  }
}
