#include "Arduino.h"
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

MoistureSensor::MoistureSensor()
  : eventListener(this), moistureLevel(0), running(false) {
}

uint8_t MoistureSensor::read() {
  return analogRead(READ_PIN);
}

void MoistureSensor::setup() {
  pinMode(PWM_OUT_PIN, OUTPUT);
  TCCR2B = 0;
  TCNT2 = 0;
  TCCR2A = _BV(COM2B1) | _BV(WGM20) | _BV(WGM21);
  TCCR2B = _BV(WGM22);
  OCR2A = PWM_PERIOD;
  OCR2B = PWM_PERIOD / 2;
}

void MoistureSensor::pwmStart() {
  TCCR2B |= _BV(CS20);
  running = true;
}

void MoistureSensor::pwmStop() {
  TCCR2B &= ~_BV(CS20);
  TCNT2 = 0;
  running = false;
}

// ############ EventListener #############
MoistureSensor::EventListener::EventListener(MoistureSensor* sensor)
  : sensor(sensor) {
}

void MoistureSensor::EventListener::onEvent(BusEvent event, va_list ap) {
  if (event == BusEvent::WAKE_UP) {
    sensor->pwmStart();

  } else if (event == BusEvent::GOTO_SLEEP) {
    sensor->pwmStop();
  }
}

uint8_t MoistureSensor::EventListener::listenerId() {
  return LISTENER_MS;
}