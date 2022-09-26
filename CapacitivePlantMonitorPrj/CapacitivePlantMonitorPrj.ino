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
#include "LED.h"
#include "Buttons.h"
#include "BrightnessManager.h"
#include "PowerMonitor.h"
#include "Storage.h"

Storage* st = new Storage();
MoistureSensor* ms = new MoistureSensor();
MoistureDisplay* md = new MoistureDisplay();
LED* led = new LED();
PowerMonitor* pm = new PowerMonitor(led);
BrightnessManager* brManager = new BrightnessManager();
Buttons* buttons = new Buttons(brManager);

const static uint8_t DEVICES = 5;
Device* dev[DEVICES] = { led, ms, md, buttons, pm };


const static uint8_t DEMOS = 2;
Demo* demos[DEMOS] = { led, md };

/** ### SETUP ### */
void setup() {
#if LOG
  log_setup();
#endif

#if LOG && LOG_CPM
  log(F("\n\n### SETUP ###"));
#endif

  brManager->registerListener(led);
  brManager->registerListener(md);

  util_setup();
  initDevices();
  playDemos();

  led->on(LedPin::SENSOR_ON);
  // led->on(LedPin::PWR_LOW);
  md->show(7);


  led->on(LedPin::PWR_LOW);
   led->on(LedPin::SENSOR_ON);
}

void initDevices() {
  execAsc([](Device* d) {
    d->init();
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

/** ### LOOP ### */
void loop() {
#if LOG && LOG_CPM
  log(F("### LOOP ###"));
#endif

  execAsc([](Device* d) {
    d->cycle();
  });

  if (CP_LOOP_DELAY > 0) {
    delay(CP_LOOP_DELAY);
  }
}

/** ### STANDBY ### */
void standby() {
#if LOG && LOG_CPM
  log(F("\n\n### STAND-BY ###"));
#endif

  execDesc([](Device* d) {
    d->standby();
  });
}

/** ### WAKEUP ### */
void wakeup() {
#if LOG && LOG_CPM
  log(F("\n\n### WAKE-UP ###"));
#endif
  execAsc([](Device* d) {
    d->wakeup();
  });
}

/** ### EXEC ASC ### */
void execAsc(void (*func)(Device*)) {
  for (uint8_t i = 0; i < DEVICES; i++) {
    func(dev[i]);
  }
}

/** ### EXEC DESC ### */
void execDesc(void (*func)(Device*)) {
  for (uint8_t i = DEVICES; i > 0; i--) {
    func(dev[i - 1]);
  }
}