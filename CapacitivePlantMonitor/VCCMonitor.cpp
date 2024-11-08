#include "HardwareSerial.h"
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
#include "VCCMonitor.h"

VCCMonitor* vccmRef;

void vccm_onProbe(va_list ap) {
  vccmRef->onProbe();
}

void vccm_onStandbyOff(va_list ap) {
  vccmRef->onStandbyOff();
}

VCCMonitor::VCCMonitor()
  : lastVcc(0) {
  reader = new Reader(new VCCMonitorReader());
}

void VCCMonitor::setup() {
  vccmRef = this;
  eb_reg(BusEvent::PROBE, &vccm_onProbe);
  eb_reg(BusEvent::STANDBY_OFF, &vccm_onStandbyOff);
}

void VCCMonitor::onStandbyOff() {
  probe(true);
}

void VCCMonitor::onProbe() {
  probe(false);
}

void VCCMonitor::probe(boolean force) {
  uint16_t vcc = reader->read();
  if (force || sub_u16(vcc, lastVcc) >= MI_MIN_VCC_CHANGE_MV) {
    lastVcc = vcc;
    if (vcc <= VC_PWR_CRITICAL) {
      eb_fire(BusEvent::VCC_CRITICAL);

    } else if (vcc <= VC_PWR_LOW) {
      eb_fire(BusEvent::VCC_LOW);

    } else {
      eb_fire(BusEvent::VCC_NOMINAL);
    }
  }
}

uint16_t VCCMonitor::mv() {
  return lastVcc == 0 ? reader->read() : lastVcc;
}

// ############## VCCMonitorReader ################
VCCMonitorReader::VCCMonitorReader() {
}

uint16_t VCCMonitorReader::read() {
  // https://github.com/cygig/MCUVoltage
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(VC_VCC_READ_DELAY);
  ADCSRA |= _BV(ADSC);
  while (bit_is_set(ADCSRA, ADSC))
    ;
  uint32_t result = ADCL;
  result |= ADCH << 8;
  result = VC_VCC_REF * 1024L / result;

#if LOG && LOG_VC
  log(F("%s PW %d"), NAME, result);
#endif

  return result;
}

const char* VCCMonitorReader::name() {
  return NAME;
}
