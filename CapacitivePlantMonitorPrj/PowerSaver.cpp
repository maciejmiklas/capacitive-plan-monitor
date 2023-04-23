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
uint32_t vv = 0;
uint32_t va = 0;
PowerSaver::PowerSaver()
  : nextStandbyMs(PS_STANDBY_INIT_MS) {
}

void PowerSaver::onEvent(BusEvent event, va_list ap) {

  if (event == BusEvent::PROBE) {
    onProbe();

  } else if (event == BusEvent::BTN_ADJ_SENSOR || event == BusEvent::BTN_BRIGHTNESS) {
    onButtonPress();

  } else if (event == BusEvent::VCC_LOW) {
    onPowerLow();

  } else if (event == BusEvent::VCC_CRITICAL) {
    onPowerCritical();
  }
}

void PowerSaver::onProbe() {
  if (util_ms() >= nextStandbyMs) {
#if LOG && LOG_PS
    log(F("%s STANDBY ON"), NAME);
#endif
    eb_fire(BusEvent::STANDBY_ON);

    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();
    sleep_cpu();
    
    delay(1000);

#if LOG && LOG_PS
    log(F("%s STANDBY OFF"), NAME);
#endif
    util_cycle();
    eb_fire(BusEvent::STANDBY_OFF);
    nextStandby();
  }
}

void PowerSaver::powerDown() {
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
