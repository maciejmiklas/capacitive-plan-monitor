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
const static uint8_t D2 = 2;      // BT_PIN_BRIGHTNESS
const static uint8_t D3_PWM = 3;  // MS_PIN_PWM_OUT
const static uint8_t D4 = 4;      // BT_PIN_ADJUST
const static uint8_t D5_PWM = 5;  // LE_PIN_SENSOR_ON
const static uint8_t D6_PWM = 6;  // LE_PIN_PWR_LOW
const static uint8_t D7 = 7;      // MI_PIN_CLOCK
const static uint8_t D8 = 8;      // MI_PIN_LATCH
const static uint8_t D9_PWM = 9;  // MI_PIN_ENABLE
const static uint8_t D10 = 10;    // MI_PIN_DATA
const static uint8_t D11 = 11;
const static uint8_t D12 = 12;

// ######## BUTTONS(BT) ########
const static uint8_t BT_PIN_BRIGHTNESS = D4;  //D2;
const static uint8_t BT_PIN_ADJUST = D2;      //D4;
const static uint8_t BT_PRESS_MS = 200;
const static uint8_t BT_PRESS_BLINK_REPEAT = 2;
const static uint8_t BT_PRESS_BLINK_ON_MS = 10;
const static uint8_t BT_PRESS_BLINK_OFF_MS = 100;

// ######## MOISTURE SENSOR(MS) ########
const static uint8_t MS_PIN_PWM_OUT = D3_PWM;
const static uint8_t MS_PIN_READ = A0;

/**
  * 30 = 515 KHz
  * 20 = 769 KHz
  * 15 = 1.00 MHz
  * 10 = 1.45 MHz
  * 9  = 1.60 MHz
  * 8  = 1.78 MHz
  * 7  = 2.00 MHz
*/
const static uint8_t MS_PWM_PERIOD = 15;
const static uint8_t MS_PWM_DUTY = 4;


// ######## MOISTURE DRIVER(MD) ########

const static uint16_t MI_LEVEL_MAP_SIZE = 9;

/**
  * Voltage levels read from the moisture sensor over input A0 depend on the VCC level, which changes with a battery charge. 
  * Different battery level reflects the amplitude of generated square wave for a sensor. It is hard to write a function 
  * that appropriately adjusts readings based on changes in the VCC level because it is not linear. For this reason, 
  * there is a mapping table consisting of three elements: VCC level, dry and wet level - all on mV.
  */
const static uint16_t MI_LEVEL_MAP[MI_LEVEL_MAP_SIZE][3] = {
  // {VCC, DRY, WET} - all in mV
  { 4000, 2600, 780 },
  { 3700, 2600, 780 },
  { 3600, 2580, 780 },
  { 3500, 2496, 791 },
  { 3400, 2362, 770 },
  { 3300, 2308, 717 },
  { 3200, 2216, 676 },
  { 3100, 2114, 643 },
  { 2000, 2100, 600 }
};

// ######## LED(LE) ########
const static uint8_t LE_PIN_AWAKE = D5_PWM;
const static uint8_t LE_PIN_PWR_LOW = D6_PWM;
const static uint16_t LE_DEMO_DELAY_MS = 200;
const static uint16_t LE_DEMO_BLNIKS = 3;

// ######## BrightnessManager(BM) ########
const static uint8_t BM_BRIGHTNESS_MIN = 5;
const static uint8_t BM_BRIGHTNESS_MAX = 255;
const static uint8_t BM_BRIGHTNESS_CHANGE = 50;
const static uint8_t BM_BRIGHTNESS_INITIAL = 5;

// ######## MoistureDisplay(MI) ########

/** PIN 11 (SRCLK) on 74HC595 */
const static uint8_t MI_PIN_CLOCK = D7;

/** PIN 12 (RCLK) on 74HC595 */
const static uint8_t MI_PIN_LATCH = D8;

/** PIN 13 (OE) on 74HC595 */
const static uint8_t MI_PIN_ENABLE = D9_PWM;

/** PIN 14 (SER) on 74HC595 */
const static uint8_t MI_PIN_DATA = D10;

const static uint8_t MI_DEMO_SPEED_MS = 50;
const static uint8_t MI_DEMO_WAIT_MIDDLE_MS = 200;

/** Level that will disable all LEDs. */
const static uint8_t MI_LEVEL_OFF = 0;

/** Min level inclusive. */
const static uint8_t MI_LEVEL_MIN = 1;

/** Max level inclusive. */
const static uint8_t MI_LEVEL_MAX = 7;

const static uint8_t MI_BLINK_REPEAT = 10;
const static uint8_t MI_BLINK_ON_MS = 30;
const static uint8_t MI_BLINK_OFF_MS = 15;

// ######## PowerMonitor(PM) ########

/** Low voltage level in mv */
static constexpr const uint16_t PM_PWR_LOW = 3200;
static constexpr const uint16_t PM_PWR_MAX = 3700;
static constexpr const uint16_t PM_VCC_READ_DELAY_MS = 5;

// ####### CapactitvePlantMonitorPrj(CP) ######
const static uint16_t CP_LOOP_DELAY = 0;
const static uint16_t CP_DEMO_DELAY_MS = 500;

// ####### Reader(RE) ######
const static uint8_t RE_PROBES = 3;
const static uint8_t RE_PROBE_AT = 1;

#endif  // CONFIG_H