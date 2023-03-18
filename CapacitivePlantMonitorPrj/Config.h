/*
   Licensed to the Apache Software Foundation (ASF) under one or more
   contributor license agreements.  See the NOTICE file distributed with
   this work for additional information regarding copyright ownership.
   The ASF licenses this file to You under the Apache License, Version 2.0
   (the "License"); you may not use this file except in compliance with
   the License.  You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <avr/power.h>

// ####### CapactitvePlantMonitorPrj(CP) ######
const static uint16_t CP_LOOP_DELAY = 0;
const static uint16_t CP_DEMO_DELAY_MS = 500;
const static clock_div_t CP_CLOCL_DIV = clock_div_8;

// ######## DIGITAL PINs ########
// PWM PINs: 3, 5, 6, 9, 10, 11
const static uint8_t D1 = 1;
const static uint8_t D2 = 2;      // BT_PIN_BRIGHTNESS
const static uint8_t D3_PWM = 3;  // MS_PIN_PWM_OUT, MoistureSensor sets Timer 2 for 200MHz on PIN 3 and 11
const static uint8_t D4 = 4;      // BT_PIN_MI_ADJUST
const static uint8_t D5_PWM = 5;  // LE_PIN_SENSOR_ON
const static uint8_t D6_PWM = 6;  // LE_PIN_PWR_LOW
const static uint8_t D7 = 7;      // MI_PIN_CLOCK
const static uint8_t D8 = 8;      // MI_PIN_LATCH
const static uint8_t D9_PWM = 9;  // MI_PIN_ENABLE
const static uint8_t D10 = 10;    // MI_PIN_DATA
const static uint8_t D11 = 11;
const static uint8_t D12 = 12;

// ######## ArdLog(AL) ########
/**
   The clock is set to 2MHz (CP_CLOCL_DIV = clock_div_8) using a divider of 8.
   The serial is set to 19200, but due to the divider, it gives an actual speed of 4800 because 38400/8=2400.
*/
// ### Serial works at 4800 due to clock prescaler! ###
const static uint32_t AL_SERIAL_SPEED = 38400;

/** Buffer size for sprintf-template passed as first argument to log method. */
const static uint8_t AL_PGBUF_SIZE = 64;

/** Buffer size for created message. */
const static uint8_t AL_SBUF_SIZE = 96;
 
// ######## BUTTONS(BT) ########
const static uint8_t BT_PIN_BRIGHTNESS = D2;
const static uint8_t BT_PIN_MI_ADJUST = D4;
const static uint8_t BT_PRESS_MS = 20;
const static uint8_t BT_PRESS_BLINK_REPEAT = 2;
const static uint8_t BT_PRESS_BLINK_ON_MS = 10;
const static uint8_t BT_PRESS_BLINK_OFF_MS = 20;

// ######## MOISTURE SENSOR(MS) ########
const static uint8_t MS_PIN_PWM_OUT = D3_PWM;
const static uint8_t MS_PIN_READ = A0;

/** Clock 2MHz (16/8=2) -> PWM at 200kHz, 30% duty */
const static uint8_t MS_PWM_PERIOD = 9;
const static uint8_t MS_PWM_DUTY = 4;
// 

// ######## LED(LE) ########
const static uint8_t LE_PIN_AWAKE = D5_PWM;
const static uint8_t LE_PIN_PWR_LOW = D6_PWM;
const static uint16_t LE_DEMO_DELAY_MS = 100;
const static uint16_t LE_DEMO_BLNIKS = 3;
const static uint16_t LE_PWM_HZ = 100;

// ######## BrightnessManager(BM) ########
const static uint8_t BM_BRIGHTNESS_MIN = 1;
const static uint8_t BM_BRIGHTNESS_MAX = 255;
const static uint8_t BM_BRIGHTNESS_CHANGE = 30;
const static uint8_t BM_BRIGHTNESS_INITIAL = 1;
const static uint8_t BM_BLINK_REPEAT = 6;
const static uint8_t BM_BLINK_ON_MS = 200;
const static uint8_t BM_BLINK_OFF_MS = 100;

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

// ######## MOISTURE DRIVER(MD) ########

const static uint8_t MI_LEVEL_MAP_SIZE = 12;

/**
    Voltage levels read from the moisture sensor over input A0 depend on the VCC level, which changes with a battery charge.
    Different battery level reflects the amplitude of generated square wave for a sensor. It is hard to write a function
    that appropriately adjusts readings based on changes in the VCC level because it is not linear. For this reason,
    we are using mapping table for different VCC levels.
*/
const static uint16_t MI_LEVEL_MAP[MI_LEVEL_MAP_SIZE][3] = {
  //{VCC , DRY , WET} (mV)
  {5000, 3632 , 2300},
  {4000, 2759 , 1745},
  {3900, 2750 , 1707},
  {3800, 2679 , 1652},
  {3700, 2599 , 1602},
  {3600, 2512 , 1544},
  {3500, 2441 , 1495},
  {3400, 2356 , 1442},
  {3300, 2279 , 1390},
  {3200, 2206 , 1336},
  {3100, 2129 , 1283},
  {2000, 1957 , 1117}
};

const static float MI_ADJUST_MUL = 0.05;
const static float MI_ADJUST_INIT = 1.1;
const static uint8_t MI_ADJUST_LEV_INIT = 4;
const static uint8_t MI_ADJUST_LEV_MAX = MI_LEVEL_MAX;
const static uint8_t MI_ADJUST_LEV_MIN = MI_LEVEL_OFF;
const static uint16_t MI_ADJUST_SHOW_MS = 10000;

// ######## PowerMonitor(PM) ########

/** Low voltage level in mv */
static const uint16_t PM_PWR_LOW = 3300;
static const uint16_t PM_PWR_MAX = 3700;
static const uint16_t PM_VCC_READ_DELAY_MS = 5;
static const uint16_t PM_VCC_REF = 1076; // default for ATmega328P: 1110
static const uint8_t PM_READ_FREQ_MS = 1000;

// ####### Reader(RE) ######
const static uint8_t RE_PROBES = 3;
const static uint8_t RE_PROBE_AT = 1;

#endif  // CONFIG_H
