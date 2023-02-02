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
#ifndef VCC_MONITOR_H
#define VCC_MONITOR_H

#include "ArdLog.h"
#include "Config.h"
#include "Device.h"
#include "BrightnessListener.h"
#include "LED.h"
#include "Reader.h"
#include "VCCProvider.h"

class VCCMonitor : public Device, public VCCProvider {
public:
  VCCMonitor(LED* led);

  // from Device.h
  void setup();
  void standby();
  void wakeup();
  void cycle();
  const char* name();

  // from PowerProvider.h
  uint16_t mv();

private:
  LED* led;
  Reader* reader;
  static constexpr const char* NAME = "PM";
  uint16_t last;
};

class VCCMonitorReader : public ReaderSupplier {
public:
  VCCMonitorReader();
  uint16_t read();
  const char* name();

private:
  static constexpr const char* NAME = "PM";
};

#endif  // VCC_MONITOR_H