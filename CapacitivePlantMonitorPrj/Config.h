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

// ######## DIGITAL PINs ########
// PWM PINs: 3, 5, 6, 9, 10, 11
const static uint8_t D1 = 1;
const static uint8_t D2 = 2; // BT_PIN_BRIGHTNESS
const static uint8_t D3_PWM = 3; // MS_PIN_PWM_OUT
const static uint8_t D4 = 4;
const static uint8_t D5_PWM = 5; // LE_PIN_SENSOR_ON
const static uint8_t D6_PWM = 6; // LE_PIN_PWR_LOW
const static uint8_t D7 = 7; // MD_PIN_CLOCK
const static uint8_t D8 = 8; // MD_PIN_LATCH
const static uint8_t D9_PWM = 9; // MD_PIN_ENABLE
const static uint8_t D10 = 10; // MD_PIN_DATA
const static uint8_t D11 = 11;
const static uint8_t D12 = 12;

// ######## BUTTONS(BT) ########
const static uint8_t BT_PIN_BRIGHTNESS = D2;
const static uint8_t BT_PRESS_MS = 200;

// ######## MOISTURE SEBSOR(MS) ########
const static uint8_t MS_PIN_PWM_OUT = D3_PWM;
const static uint8_t MS_PIN_READ = A0;
const static uint8_t MS_READS = 4;

// ######## LED(LE) ########
const static uint8_t LE_PIN_SENSOR_ON = D5_PWM;
const static uint8_t LE_PIN_PWR_LOW = D6_PWM;
const static uint16_t LE_DEMO_SPEED_MS = 200;

// ######## BrightnessManager(BM) ########
const static uint8_t BM_BRIGHTNESS_MIN = 5;
const static uint8_t BM_BRIGHTNESS_MAX = 255;
const static uint8_t BM_BRIGHTNESS_CHANGE = 50;
const static uint8_t BM_BRIGHTNESS_INITIAL = 150;

// ######## MoistureDisplay(MD) ########

/** PIN 11 (SRCLK) on 74HC595 */
const static uint8_t MD_PIN_CLOCK = D7; 

/** PIN 12 (RCLK) on 74HC595 */
const static uint8_t MD_PIN_LATCH = D8;

/** PIN 13 (OE) on 74HC595 */
const static uint8_t MD_PIN_ENABLE = D9_PWM;

/** PIN 14 (SER) on 74HC595 */
const static uint8_t MD_PIN_DATA = D10; 

const static uint8_t MD_DEMO_SPEED_MS = 50;

// ######## PowerMonitor(PM) ########
const static uint8_t PM_PIN_READ = A1;
static constexpr const float PM_SYSTEM_VOLTS = 3.7;
static constexpr const float PM_PWR_LOW = 3.2;

// ####### CapactitvePlantMonitorPrj(CP) ######
const static uint16_t CP_LOOP_DELAY = 0;
const static uint16_t CP_DEMO_DELAY_MS = 1000;

// ####### Reader(RE) ######
const static uint8_t RE_PROBES = 4;
const static uint8_t RE_PROBE_AT = 2;

#endif  // CONFIG_H