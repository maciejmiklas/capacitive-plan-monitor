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

#ifndef STANDBY_MANGER_H
#define STANDBY_MANGER_H

#include "ArdLog.h"
#include "Config.h"
#include "Util.h"
#include "Device.h"
#include "LED.h"
#include <avr/sleep.h>
#include <avr/power.h>

class StandbyManager {

public:
  StandbyManager(LED* led, Device** devices,uint8_t devicesSize);
  
  void setup();
  void cycle();

private:
  Device** devices;
  uint8_t devicesSize;
  LED* led;

  void standby();
  void wakeup();
};

#endif  // STANDBY_MANGER_H