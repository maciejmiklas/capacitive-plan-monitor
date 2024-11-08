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

PowerSaver* refPsav;

void psav_onCycle(va_list ap) {
  refPsav->onCycle();
}

void psav_onButtonPress(va_list ap) {
  refPsav->onButtonPress();
}

uint32_t vv = 0;
uint32_t va = 0;
PowerSaver::PowerSaver()
  : nextStandbyMs(PS_STANDBY_INIT_MS) {
}

void PowerSaver::setup() {
#if !LOG
  power_usart0_disable();
#endif

  refPsav = this;
  eb_reg(BusEvent::CYCLE, &psav_onCycle);
  eb_reg(BusEvent::BTN_ADJ_SENSOR, &psav_onButtonPress);
  eb_reg(BusEvent::BTN_BRIGHTNESS, &psav_onButtonPress);

  power_spi_disable();
  power_twi_disable();
}

void PowerSaver::onCycle() {
  if (util_ms() >= nextStandbyMs) {
#if LOG && LOG_PS
    log(F("%s STANDBY ON"), NAME);
#endif
    eb_fire(BusEvent::STANDBY_ON);
    delay(PS_SLEEP_DELAY_MI);
    sleep(PS_SLEEP);
    delay(PS_WAKEUP_DELAY_MI);
#if LOG && LOG_PS
    log(F("%s STANDBY OFF"), NAME);
#endif
    util_cycle();
    eb_fire(BusEvent::STANDBY_OFF);
    nextStandby();
  }
}

// watchdog interrupt
ISR(WDT_vect) {
  wdt_disable();
}

void PowerSaver::sleep(SleepPeriod period) {
  MCUSR = 0;  // clear "reset" flags

  // allow changes, disable reset, clear existing interrupt
  WDTCSR = bit(WDCE) | bit(WDE) | bit(WDIF);

  noInterrupts();

  // set interrupt mode and an interval
  switch (period) {
    case SleepPeriod::S1:
      WDTCSR = bit(WDIE) | bit(WDP2) | bit(WDP1);
      break;

    case SleepPeriod::S2:
      WDTCSR = bit(WDIE) | bit(WDP2) | bit(WDP1) | bit(WDP0);
      break;

    case SleepPeriod::S4:
      WDTCSR = bit(WDIE) | bit(WDP3);
      break;

    default:
    case SleepPeriod::S8:
      WDTCSR = bit(WDIE) | bit(WDP3) | bit(WDP0);
      break;
  }

  wdt_reset();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  power_all_disable();
  sleep_enable();

  interrupts();  // guarantees next instruction executed
  sleep_cpu();   // power down

  sleep_disable();
  power_all_enable();
}

void PowerSaver::onButtonPress() {
  nextStandby(PS_STANDBY_BUTTON_MS);
}

void PowerSaver::nextStandby(uint32_t delayMs) {
  nextStandbyMs = util_ms() + delayMs;
}

void PowerSaver::nextStandby() {
  nextStandby(PS_STANDBY_DELAY_MS);
}