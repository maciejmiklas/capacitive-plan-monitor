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
#include "MoistureSensor.h"

MoistureSensor* refMsen;

void msen_onStandby(va_list ap) {
  refMsen->onStandby();
}

void msen_onWakeup(va_list ap) {
  refMsen->onWakeup();
}

MoistureSensor::MoistureSensor() {
  reader = new Reader(new MoistureReader());
}

uint16_t MoistureSensor::read() {
  uint16_t val = reader->read();
  
#if LOG && LOG_MS
  log(F("%s RV:%d"), NAME, val);
#endif

  return val;
}

void MoistureSensor::setup() {
  pinMode(MS_PIN_PWM_OUT, OUTPUT);

  // setup for Timer 2 controlling PIN 3 and 11
  TCCR2B = 0;
  TCNT2 = 0;
  TCCR2A = _BV(COM2B1) | _BV(WGM20) | _BV(WGM21);
  TCCR2B = _BV(WGM22);
  OCR2A = MS_PWM_PERIOD;
  OCR2B = MS_PWM_PERIOD / MS_PWM_DUTY;
  onWakeup();

  refMsen = this;
  eb_reg(BusEvent::STANDBY_ON, &msen_onStandby);
  eb_reg(BusEvent::STANDBY_OFF, &msen_onWakeup);
}

void MoistureSensor::onWakeup() {
  TCCR2B |= _BV(CS20);
}

void MoistureSensor::onStandby() {
  TCCR2B &= ~_BV(CS20);
  TCNT2 = 0;
}

// ############## MoistureReader ################
MoistureReader::MoistureReader() {
}

uint16_t MoistureReader::read() {
  return analogRead(MS_PIN_READ);
}

const char* MoistureReader::name() {
  return NAME;
}
