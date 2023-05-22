/*
3 * Licensed to the Apache Software Foundation (ASF) under one or more
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
#include "EventBus.h"

static constexpr const char* NAME = "EB";

const static uint8_t LISTNERS_MAX = 15;
static BusListener* listeners[LISTNERS_MAX];
static uint8_t listenersAmount = 0;

BusListener::~BusListener() {
}

BusListener::BusListener() {
  eb_register(this);
}

void eb_register(BusListener* listener) {
  if (listenersAmount == LISTNERS_MAX) {
#if LOG && LOG_EB
    log(F("%s LN ERR (%d) !"), NAME, listenersAmount);
#endif
    return;
  }

#if LOG && LOG_EB
  log(F("%s REG %d"), NAME, listenersAmount);
#endif
  listeners[listenersAmount++] = listener;
}

void eb_fire(BusEvent event, ...) {
#if LOG && LOG_EB
  log(F("%s LE %d"), NAME, event);
#endif

  for (uint8_t idx = 0; idx < listenersAmount; idx++) {
    va_list ap;
    va_start(ap, event);
    listeners[idx]->onEvent(event, ap);
    va_end(ap);
  }
}
