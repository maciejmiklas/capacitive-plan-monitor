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
#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ######## BUTTONS(BT) ########
const static uint8_t BT_PIN_BRIGHTNESS = 2;
const static uint8_t BT_PRESS_MS = 200;

// ######## MOISTURE SEBSOR(MS) ########
const static uint8_t MS_PIN_PWM_OUT = 3;
const static uint8_t MS_PIN_READ = A0;
const static uint8_t MS_READS = 4;
const static uint8_t MS_READ_VAL = 3;

// ######## LED(LE) ########
const static uint8_t LE_PIN_MESURE = 5;
const static uint8_t LE_PIN_PWR_LOW = 6;
const static uint8_t LE_DEMO_SPEED_MS = 200;

// ######## BrightnessManager(BM) ########
const static uint8_t BM_BRIGHTNESS_MIN = 5;
const static uint8_t BM_BRIGHTNESS_MAX = 255;
const static uint8_t BM_BRIGHTNESS_CHANGE = 50;
const static uint8_t BM_BRIGHTNESS_INITIAL = 150;

// ######## MoistureDisplay(MD) ########

/** PIN 11 (OE) on 74HC595 */
const static uint8_t MD_PIN_ENABLE = 10;

/** PIN 11 (SRCLK) on 74HC595 */
const static uint8_t MD_PIN_CLOCK = 7;

/** PIN 12 (RCLK) on 74HC595 */
const static uint8_t MD_PIN_LATCH = 8;

/** PIN 14 on 74HC595 */
const static uint8_t MD_PIN_DATA = 9;

const static uint8_t MD_DEMO_SPEED_MS = 50;

// ######## PowerMonitor(PM) ########
const static uint8_t PM_PIN_READ = A1;
static constexpr const float PM_SYSTEM_VOLTS = 4.33; //3.7
static constexpr const float PM_PWR_LOW = 3.2; 

// ####### CapactitvePlantMonitorPrj(CP) ######
const static uint16_t CP_LOOP_DELAY = 2000;

// ####### Reader(RE) ######
const static uint8_t RE_PROBES = 4;
const static uint8_t RE_PROBE_AT = 2;

#endif  // CONFIG_H