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
#ifndef MOISTURE_SENSOR_H
#define MOISTURE_SENSOR_H

#include "Device.h"
#include "Config.h"

/** Sets Timer 2 to generate PWM of 1.6MHz on #PWM_OUT_PIN */
class MoistureSensor : public Device {
public:
  MoistureSensor();

  /* returns last value read from moisture sensor from 0 to 255. */
  uint8_t read();

  // from Device.h
  virtual void init();
  virtual void demo();
  virtual void standby();
  virtual void wakeup();
  virtual void cycle();
  virtual const char* name();

private:
  const static uint8_t READ_PIN = PIN_MOISTURE_READ;
  const static uint8_t PWM_OUT_PIN = PIN_MOISTURE_PWM_OUT;

  // 10 = 1.45 MHz
  // 9  = 1.60 MHz
  // 8  = 1.78 MHz
  // 7  = 2.00 MHz
  const static uint8_t PWM_PERIOD = 9;

  static constexpr const char* NAME = "MS";
};

#endif  // MOISTURE_SENSOR_H