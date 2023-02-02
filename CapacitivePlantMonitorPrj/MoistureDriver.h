#include "Arduino.h"
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
#ifndef MOISTURE_DRIVER_H
#define MOISTURE_DRIVER_H

#include "Config.h"
#include "ArdLog.h"
#include "Device.h"
#include "MoistureSensor.h"
#include "MoistureDisplay.h"
#include "VCCProvider.h"

class MoistureDriver : public Device {
public:

  MoistureDriver(MoistureSensor* sensor, MoistureDisplay* display, VCCProvider* vcc);

  // from Device.h
  void setup();
  void standby();
  void wakeup();
  void cycle();
  const char* name();
  void adjustyNextLevel();

private:
  static constexpr const char* NAME = "MD";
  MoistureSensor* sensor;
  MoistureDisplay* display;
  VCCProvider* vcc;

  float adjust;
  uint8_t adjustLevel;
  boolean adjustUp;
  long adjustPressMs;  
  uint8_t getLevel();
};

#endif  // MOISTURE_DRIVER_H