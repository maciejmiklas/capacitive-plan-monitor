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

  if (event == BusEvent::CYCLE) {
    onCycle();

  } else if (event == BusEvent::BTN_ADJ_SENSOR || event == BusEvent::BTN_BRIGHTNESS) {
    onButtonPress();
  } 
}

void PowerSaver::onCycle() {
  if (util_ms() >= nextStandbyMs) {
#if LOG && LOG_PS
    log(F("%s STANDBY ON"), NAME);
#endif
    eb_fire(BusEvent::STANDBY_ON);
    delay(10);
    sleep(PS_SLEEP);
    delay(10);
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
  MCUSR = 0;                      // clear various "reset" flags
  WDTCSR = bit(WDCE) | bit(WDE);  // allow changes, disable reset

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
  noInterrupts();  // timed sequence follows
  sleep_enable();
  MCUCR = bit(BODS) | bit(BODSE);  // turn off brown-out enable in software
  MCUCR = bit(BODS);
  interrupts();  // guarantees next instruction executed
  sleep_cpu();
  sleep_disable();
}

void PowerSaver::onButtonPress() {
  nextStandby(PS_STANDBY_INIT_MS);
}

void PowerSaver::nextStandby(uint32_t delayMs) {
  nextStandbyMs = util_ms() + delayMs;
}

void PowerSaver::nextStandby() {
  nextStandby(PS_STANDBY_DELAY_MS);
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
