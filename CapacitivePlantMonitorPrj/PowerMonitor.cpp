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
#include "PowerMonitor.h"

PowerMonitor::PowerMonitor(LED* led)
  : led(led), last(PM_PWR_MAX) {
  reader = new Reader(new PowerMonitorReader());
}


void PowerMonitor::init() {
}

void PowerMonitor::standby() {}
void PowerMonitor::wakeup() {}

void PowerMonitor::cycle() {
  last = reader->read();
  if (last <= PM_PWR_LOW) {
    led->on(LedPin::PWR_LOW);
  } else {
    led->off(LedPin::PWR_LOW);
  }
}

const char* PowerMonitor::name() {
  return NAME;
}

uint16_t PowerMonitor::mv() {
  return last;
}

// ############## PowerMonitorReader ################
PowerMonitorReader::PowerMonitorReader() {
}


uint16_t PowerMonitorReader::read() {
  // https://github.com/cygig/MCUVoltage
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(PM_VCC_READ_DELAY_MS);
  ADCSRA |= _BV(ADSC);
  while (bit_is_set(ADCSRA, ADSC))
    ;
    
  uint32_t result = ADCL;
  result |= ADCH << 8;
  result = 1110L * 1023L / result;
  return result;
}

const char* PowerMonitorReader::name() {
  return NAME;
}