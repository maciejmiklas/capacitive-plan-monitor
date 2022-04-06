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

MoistureSensor* ms = new MoistureSensor();
MoistureDisplay* md = new MoistureDisplay();
LED* led = new LED();
Buttons* buttons = new Buttons(led, ms);

const static uint8_t DEVICES = 4;
Device* dev[DEVICES] = { led, ms, md, buttons};

void setup() {
#if ENABLE_LOGGER
  log_setup();
#endif

#if LOG
  log(F("\n\n## SETUP ##"));
#endif

  util_setup();
  execAsc([](Device* d) {
    d->init();
    d->wakeup();
    d->demo();
  });
}

void loop() {
  execAsc([](Device* d) {
    d->cycle();
  });
}

void standby() {
#if LOG
  log(F("\n\n## STAND-BY ##"));
#endif

  execDesc([](Device* d) {
    d->standby();
  });
}

void wakeup() {
#if LOG
  log(F("\n\n## WAKE-UP ##"));
#endif
  execAsc([](Device* d) {
    d->wakeup();
  });
}

void execAsc(void (*func)(Device*)) {
  for (uint8_t i = 0; i < DEVICES; i++) {
    func(dev[i]);
  }
}

void execDesc(void (*func)(Device*)) {
  for (uint8_t i = DEVICES; i > 0; i--) {
    func(dev[i - 1]);
  }
}
