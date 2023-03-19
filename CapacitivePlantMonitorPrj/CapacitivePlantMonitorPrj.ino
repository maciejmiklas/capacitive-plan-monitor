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
#include "MoistureDriver.h"
#include "Arduino.h"
#include "EventBus.h"
#include "LED.h"
#include "Buttons.h"
#include "BrightnessManager.h"
#include "VCCMonitor.h"
#include "Storage.h"
#include "StandbyManager.h"

Storage* st = new Storage();
MoistureSensor* ms = new MoistureSensor();
MoistureDisplay* mi = new MoistureDisplay();
LED* led = new LED();
VCCMonitor* pm = new VCCMonitor();
BrightnessManager* brManager = new BrightnessManager();
MoistureDriver* md = new MoistureDriver(ms, mi, pm);
Buttons* buttons = new Buttons();
StandbyManager* sm = new StandbyManager();

const static uint8_t DEMOS = 2;
Demo* demos[DEMOS] = { led, mi };

/** ### SETUP ### */
void setup() {
#if LOG
  log_setup();
#endif

#if LOG && LOG_CPM
  log(F("\n\n### SETUP ###"));
#endif
  util_setup();

  eb_fire(BusEvent::SYSTEM_INIT);

  playDemos();

  // change clock speed after Demos, otherwise timing is wrogn
  clock_prescale_set(CP_CLOCK_DIV);
}

/** ### LOOP ### */
void loop() {
#if LOG && LOG_CPM
  log(F("### LOOP ### %d"));
#endif

  util_cycle();

  eb_fire(BusEvent::CYCLE);

  if (CP_LOOP_DELAY > 0) {
    delay(CP_LOOP_DELAY);
  }
}

void playDemos() {
  for (uint8_t i = 0; i < DEMOS; i++) {
    delay(CP_DEMO_DELAY_MS);
    demos[i]->demo();
  }
  delay(CP_DEMO_DELAY_MS);
}
