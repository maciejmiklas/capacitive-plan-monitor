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

#include "LowPower.h"
#include <Arduino.h>
#include <avr/power.h>

// ####### CapactitvePlantMonitorPrj(CP) ######
const static uint16_t CP_LOOP_DELAY = 0;
const static uint16_t CP_DEMO_DELAY_MS = 500;
const static clock_div_t CP_CLOCK_DIV = clock_div_8;  // make sure that CP_CLOCK_DIV_INT has correcponding value!
const static uint8_t CP_CLOCK_DIV_INT = 8;

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
   However, in order to see initial logs set serial to 19200, because prescaller is set after system initialization.
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

// ######## MOISTURE SENSOR(MS) ########
const static uint8_t MS_PIN_PWM_OUT = D3_PWM;
const static uint8_t MS_PIN_READ = A0;

/** Clock 2MHz (16/8=2) -> PWM at 200kHz, 30% duty */
const static uint8_t MS_PWM_PERIOD = 9;
const static uint8_t MS_PWM_DUTY = 4;

// ######## LED(LE) ########
const static uint8_t LE_PIN_AWAKE = D5_PWM;
const static uint8_t LE_PIN_PWR_LOW = D6_PWM;
const static uint16_t LE_DEMO_DELAY = 100;
const static uint16_t LE_DEMO_BLNIKS = 3;
const static uint16_t LE_PWM_HZ = 100;

const static uint8_t LE_PRESS_BLINK_REPEAT = 3;
const static uint8_t LE_PRESS_BLINK_ON_DELAY = 3;
const static uint8_t LE_PRESS_BLINK_OFF_DELAY = 6;

const static uint8_t LED_BR_MAX_BLINK_REPEAT = 6;
const static uint8_t LED_BR_MAX_BLINK_ON_DELAY = 3;
const static uint8_t LED_BR_MAX_BLINK_OFF_DELAY = 6;

// ######## BrightnessManager(BM) ########
const static uint8_t BM_BRIGHTNESS_MIN = 1;
const static uint8_t BM_BRIGHTNESS_MAX = 255;
const static uint8_t BM_BRIGHTNESS_CHANGE = 10;
const static uint8_t BM_BRIGHTNESS_INITIAL = 1;

// ######## ProbeDriver(PD)  ########
const static uint32_t PD_PROBE_SUSPEND_MS = 5000;
const static uint32_t PD_FREQ_MS = 200;

// ######## MoistureDisplay(MI) ########

/** PIN 11 (SRCLK) on 74HC595 */
const static uint8_t MI_PIN_CLOCK = D7;

/** PIN 12 (RCLK) on 74HC595 */
const static uint8_t MI_PIN_LATCH = D8;

/** PIN 13 (OE) on 74HC595 */
const static uint8_t MI_PIN_ENABLE = D9_PWM;

/** PIN 14 (SER) on 74HC595 */
const static uint8_t MI_PIN_DATA = D10;

const static uint8_t MI_DEMO_DELAY = 50;
const static uint8_t MI_DEMO_MIDDLE_DELAY = 200;

/** Level that will disable all LEDs. */
const static uint8_t MI_LEVEL_OFF = 0;

/** Min level inclusive. */
const static uint8_t MI_LEVEL_MIN = 1;

/** Max level inclusive. */
const static uint8_t MI_LEVEL_MAX = 7;

const static uint8_t MI_BLINK_REPEAT = 5;
const static uint8_t MI_BLINK_ON_DELAY = 10;
const static uint8_t MI_BLINK_OFF_DELAY = 5;
const static uint8_t MI_BRIGHTNES_ON_DELAY = 100;

// ######## MOISTURE DRIVER(MD) ########

const static uint8_t MI_LEVEL_MAP_SIZE = 19;

/**
    Voltage level read from the moisture sensor over input A0 depend on the VCC level, which changes with a battery charge.
    Different battery level reflects the amplitude of generated square wave for a sensor. It is hard to write a function
    that appropriately adjusts readings based on changes in the VCC level because it is not linear. For this reason,
    we are using mapping table for different VCC levels.
*/
const static uint16_t MI_LEVEL_MAP[MI_LEVEL_MAP_SIZE][3] = {
  //{VCC, DRY, WET} (mV)
  { 5000, 4220, 3000 },
  { 4000, 2970, 1790 },
  { 3900, 2870, 1720 },
  { 3800, 2790, 1660 },
  { 3750, 2750, 1630 },
  { 3700, 2700, 1600 },
  { 3650, 2660, 1580 },
  { 3600, 2620, 1550 },
  { 3550, 2570, 1520 },
  { 3500, 2537, 1500 },
  { 3450, 2490, 1460 },
  { 3400, 2460, 1430 },
  { 3350, 2410, 1400 },
  { 3300, 2370, 1380 },
  { 3250, 2320, 1350 },
  { 3200, 2280, 1330 },
  { 3100, 2200, 1270 },
  { 3000, 2110, 1210 },
  { 2000, 2000, 1500 }
};

const static float MI_ADJUST_STEP = 0.05;
const static float MI_ADJUST_INIT = 1.0;
const static uint8_t MI_MIN_CHANGE_LEVEL = 1;
const static uint8_t MI_ADJUST_LEV_INIT = 4;
const static uint8_t MI_ADJUST_LEV_MAX = MI_LEVEL_MAX;
const static uint8_t MI_ADJUST_LEV_MIN = MI_LEVEL_OFF;
const static uint16_t MI_ADJUST_SHOW_MS = 5000;
const static uint16_t MI_MIN_VCC_CHANGE_MV = 20;

// ######## VCCMonitor(VC) ########

/** Low voltage level in mv */
static const uint16_t VC_PWR_LOW = 3400;
static const uint16_t VC_PWR_CRITICAL = 3200;
static const uint16_t VC_PWR_MAX = 3700;
static const uint16_t VC_VCC_READ_DELAY = 10;
static const uint16_t VC_VCC_REF = 1081;  // default for ATmega328P: 1110

// ####### Reader(RE) ######
const static uint8_t RE_PROBES = 3;
const static uint8_t RE_PROBE_AT = 1;

// ####### PowerSaver(PS) ######
const static uint16_t PS_STANDBY_DELAY_MS = 10000;
const static period_t PS_SLEEP = SLEEP_2S;

#endif  // CONFIG_H
