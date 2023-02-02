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
VCCMonitor* pm = new VCCMonitor(led);
BrightnessManager* brManager = new BrightnessManager(led);
MoistureDriver* md = new MoistureDriver(ms, mi, pm);
Buttons* buttons = new Buttons(brManager, md, led);

const static uint8_t DEVICES = 6;
Device* dev[DEVICES] = { ms, led, mi, buttons, pm, md };

const static uint8_t DEMOS = 2;
Demo* demos[DEMOS] = { led, mi };

StandbyManager* sm = new StandbyManager(led, dev, DEVICES);

/** ### SETUP ### */
void setup() {
#if LOG
  log_setup();
#endif

#if LOG && LOG_CPM
  log(F("\n\n### SETUP ###"));
#endif
  util_setup();

  brManager->registerListener(led);
  brManager->registerListener(mi);

  initDevices();
  playDemos();

  sm->setup();
}

/** ### LOOP ### */
void loop() {
#if LOG && LOG_CPM
  log(F("### LOOP ###"));
#endif

  util_cycle();

  exec_dev_asc(dev, DEVICES, [](Device* d) {
    d->cycle();
  });

  if (CP_LOOP_DELAY > 0) {
    delay(CP_LOOP_DELAY);
  }

   sm->cycle();
}

void initDevices() {
  exec_dev_asc(dev, DEVICES, [](Device* d) {
    d->setup();
    d->wakeup();
  });
}

void playDemos() {
  for (uint8_t i = 0; i < DEMOS; i++) {
    delay(CP_DEMO_DELAY_MS);
    demos[i]->demo();
  }
  delay(CP_DEMO_DELAY_MS);
}
