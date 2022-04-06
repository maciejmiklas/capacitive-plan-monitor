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
#ifndef PIN_H
#define PIN_H

#include <Arduino.h>

// ######## BUTTONS ######## 
const static uint8_t PIN_BNT_BRIGHTNESS = 4;

// ######## MOISTURE ######## 
const static uint8_t PIN_MOISTURE_PWM_OUT = 3;
const static uint8_t PIN_MOISTURE_READ = A0;

// ######## LED ######## 
const static uint8_t PIN_LED_MESURE = 5;
const static uint8_t PIN_LED_PWR_LOW = 6;

// ######## MD ######## 

/** PIN 11 (OE) on 74HC595 */
const static uint8_t PIN_MD_ENABLE = 10;

/** PIN 11 (SRCLK) on 74HC595 */
const static uint8_t PIN_MD_CLOCK = 7;

/** PIN 12 (RCLK) on 74HC595 */
const static uint8_t PIN_MD_LATCH = 8;

/** PIN 14 on 74HC595 */
const static uint8_t PIN_MD_DATA = 9;

// ######## PWR ######## 
const static uint8_t PIN_PWR_READ = A1;

#endif  // PIN_H