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
  : led(led) {
  reader = new Reader(new PowerMonitorReader());
}

float PowerMonitor::readVoltage() {
  return (float)reader->read() * PM_SYSTEM_VOLTS / 1023.0;
}

void PowerMonitor::init() {}
void PowerMonitor::demo() {}
void PowerMonitor::standby() {}
void PowerMonitor::wakeup() {}

void PowerMonitor::cycle() {
  if (readVoltage() <= PM_PWR_LOW) {
    led->on(LedPin::PWR_LOW);
  } else {
    led->off(LedPin::PWR_LOW);
  }
}

const char* PowerMonitor::name() {
  return NAME;
}

// ############## PowerMonitorReader ################
PowerMonitorReader::PowerMonitorReader() {
}

uint16_t PowerMonitorReader::read() {
  return analogRead(PM_PIN_READ);
}

const char* PowerMonitorReader::name() {
  return NAME;
}