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
#include "LED.h"

LED::LED() {
}

void LED::setup() {
  for (uint8_t pin = LED_PIN::PWR_ON; pin <= LED_PIN::PWR_LOW; pin++) {
    pinMode(pin, OUTPUT);
    analogWrite(pin, LOW);
  }
}

void LED::off(LED_PIN led) {
  uint8_t pin = led;
#if TRACE
  log(F("LED OFF %d"), pin);
#endif
  analogWrite(pin, LOW);
}

void LED::on(LED_PIN led) {
  uint8_t pin = led;
#if TRACE
  log(F("LED ON %d"), pin);
#endif
  analogWrite(pin, BRIGHTNESS);
}
