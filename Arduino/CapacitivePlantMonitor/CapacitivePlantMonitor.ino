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

 /** Enables logger so that it can log over serial port. */
#define ENABLE_LOGGER true

/** Enables log on Debug level. */
#define LOG true

/** Enables log on Trace level. */
#define TRACE true

CapacitiveSensor* cs = new CapacitiveSensor();


void setup() {
  util_setup();

  #if ENABLE_LOGGER
    log_setup();
  #endif 

  cs->setup();
  cs->start();
}

uint16_t loopIdex = 0;
void loop(){
  util_cycle();

  #if ENABLE_LOGGER
    log_cycle();
  #endif 

  #if LOG
    log(F("**** Loop %d ****"), loopIdex++);
    log(F("T1 = %ld"), millis());
  #endif

  delay(1000);

  #if LOG
    log(F("T2 = %ld"), millis());
  #endif

  delay(1000);
}