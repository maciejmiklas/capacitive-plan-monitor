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
#include "CapacitiveSensor.h"

CapacitiveSensor::CapacitiveSensor() {
}

void CapacitiveSensor::setup() {
  pinMode(PWM_OUT_PIN, OUTPUT);
  TCCR2B = 0;
  TCNT2 = 0;
  TCCR2A = _BV(COM2B1) | _BV(WGM20) | _BV(WGM21);
  TCCR2B = _BV(WGM22);
  OCR2A = PWM_PERIOD;
  OCR2B = PWM_PERIOD / 2;
}

void CapacitiveSensor::start() {
  TCCR2B |= _BV(CS20);
}

void CapacitiveSensor::stop() {
  TCCR2B &= ~_BV(CS20);
  TCNT2 = 0;
}