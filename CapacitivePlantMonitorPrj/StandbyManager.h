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
#include "EventBus.h"
#include <avr/sleep.h>
#include <avr/power.h>

class StandbyManager : public BusListener {

public:
  StandbyManager();

  // from EventBus.h
  void onEvent(BusEvent event, va_list ap);
  const char* listenerName();

private:
 static constexpr const char* NAME = "SM";

  void setup();
};

#endif  // STANDBY_MANGER_H