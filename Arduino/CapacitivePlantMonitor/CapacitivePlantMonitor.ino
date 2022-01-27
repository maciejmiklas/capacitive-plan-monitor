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
#include "ArdLog.h"
#include "Util.h"
#include "MoistureSensor.h"
#include "MoistureDisplay.h"
#include "Arduino.h"
#include "EventBus.h"
#include "LED.h"

MoistureSensor* ms = new MoistureSensor();
MoistureDisplay* md = new MoistureDisplay();

LED* led = new LED();

void setup() {
  util_setup();

#if ENABLE_LOGGER
  log_setup();
#endif

  ms->setup();
  ms->start();

  md->setup();

  led->setup();
}

uint16_t loopIdex = 0;
void loop() {
  util_cycle();

#if ENABLE_LOGGER
  log_cycle();
#endif

  log(F("**** Loop %d ****"), loopIdex++);

  eb_fire(BusEvent::CYCLE);

  md->show(1);
  /*
  log(F("Moisture: %d"), ms->read());

  led->on(LED_PIN::PWR_ON);
  delay(1000);
  led->off(LED_PIN::PWR_ON);
  delay(1000);
  led->on(LED_PIN::PWR_LOW);
  delay(1000);
  led->off(LED_PIN::PWR_LOW);
  delay(1000);*/
}