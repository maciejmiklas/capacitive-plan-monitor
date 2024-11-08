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

#include "Config.h"
#include "Reader.h"
#include "EventBus.h"
#include "Arduino.h"
#include "Device.h"

class MoistureReader : public ReaderSupplier {
public:
  MoistureReader();
  uint16_t read();
  const char* name();

private:
  static constexpr const char* NAME = "MS";
};

class MoistureSensor : public Device {
public:

  MoistureSensor();

  /* returns last value read from moisture sensor from 0 to 1023. */
  uint16_t read();

  // from Device.h
  void setup();  

  void onWakeup();
  void onStandby();

private:

  static constexpr const char* NAME = "MS";
  Reader* reader;
};

#endif  // MOISTURE_SENSOR_H