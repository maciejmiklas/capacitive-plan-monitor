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

#include "StandbyManager.h"

StandbyManager::StandbyManager(LED* led, Device** devices, uint8_t devicesSize)
  : led(led), devices(devices), devicesSize(devicesSize) {
}

void StandbyManager::cycle() {
}

void StandbyManager::setup() {

#if !LOG
  power_usart0_disable();
#endif

  power_spi_disable();
  power_twi_disable();
}


void StandbyManager::standby() {
#if LOG && LOG_SM
  log(F("\n\n### STAND-BY ###"));
#endif
  led->off(LedPin::AWAKE);

  exec_dev_desc(devices, devicesSize, [](Device * d) {
    d->standby();
  });
}

void StandbyManager::wakeup() {
#if LOG && LOG_SM
  log(F("\n\n### WAKE-UP ###"));
#endif
  led->on(LedPin::AWAKE);
  exec_dev_asc(devices, devicesSize, [](Device * d) {
    d->wakeup();
  });
}
