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

#include "PowerSaver.h"

PowerSaver::PowerSaver()
  : nextStandbyMs(PS_STANDBY_DELAY_MS) {
}

void PowerSaver::onEvent(BusEvent event, va_list ap) {

  if (event == BusEvent::CYCLE) {
    onCycle();

  } else if (event == BusEvent::BTN_ADJ_SENSOR || event == BusEvent::BTN_BRIGHTNESS) {
    onButtonPress();

  } else if (event == BusEvent::VCC_LOW) {
    onPowerLow();

  } else if (event == BusEvent::VCC_CRITICAL) {
    onPowerCritical();
  }
}

void PowerSaver::onCycle() {
  if (util_ms() >= nextStandbyMs) {
#if LOG && LOG_PS
    log(F("%s STANDBY"), NAME);
#endif
    eb_fire(BusEvent::STANDBY_ON);

    LowPower.powerDown(PS_SLEEP, ADC_OFF, BOD_OFF);

    util_cycle();
    eb_fire(BusEvent::STANDBY_OFF);
    nextStandby();
  }
}

void PowerSaver::onButtonPress() {
  nextStandby();
}

void PowerSaver::nextStandby() {
  nextStandbyMs = util_ms() + PS_STANDBY_DELAY_MS;
}

void PowerSaver::onPowerLow() {
  eb_fire(BusEvent::BRIGHTNESS_CHANGE, MI_LEVEL_MIN);
}

void PowerSaver::onPowerCritical() {
  eb_fire(BusEvent::BRIGHTNESS_CHANGE, MI_LEVEL_OFF);
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
}

const char* PowerSaver::listenerName() {
  return NAME;
}

void PowerSaver::setup() {

#if !LOG
  power_usart0_disable();
#endif

  power_spi_disable();
  power_twi_disable();
}
