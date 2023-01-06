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
#ifndef ARD_LOG_H
#define ARD_LOG_H

#include <Arduino.h>
#include <stdarg.h>

/** Enables logger so that it can log over serial port. */
#define LOG true

/** Enable logger for: CapacitivePlantMonitor */
#define LOG_CPM false

/** Enable logger for: BrightnessListener */
#define LOG_BL true

/** Enable logger for: BrightnessManager */
#define LOG_BM true

/** Enable logger for: LED */
#define LOG_LE false

/** Enable logger for: MoistureDisplay */
#define LOG_MI false

/** Enable logger for: MoistureSensor */
#define LOG_MS false

/** Enable logger for: MoistureDriver */
#define LOG_MD false

/** Enable logger for: PowerMonitor */
#define LOG_PM false

/** Enable logger for: Storage */
#define LOG_ST false

/** Enable logger for: Reader */
#define LOG_RE false

void log_setup();
void log_cycle();
void log(const __FlashStringHelper *ifsh, ...);

class Logger {
  public:
    Logger();
    void setup();
    void logv(const __FlashStringHelper *ifsh, va_list args);
    void log(const __FlashStringHelper *ifsh, ...);
    void logRAM(char const *msg);
    void logChangeRAM();

  private:
    const static uint32_t SERIAL_SPEED = 115200;

    /** Buffer size for sprintf-template passed as first argument to log method. */
    const static uint8_t PGBUF_SIZE = 64;

    /** Buffer size for created message. */
    const static uint8_t SBUF_SIZE = 96;

    /** Buffer for created message */
    char sbuf[SBUF_SIZE] = { 0 };

    /** Buffer for sprintf-template passed as first argument to log method. */
    char pgbuf[PGBUF_SIZE] = { 0 };

    uint16_t lastFreeRam = 0;

    inline void resetBuf(char *buf, uint8_t size);
    inline void resetSbuf();
    inline void resetPgbuf();
    inline void copyPGM(const __FlashStringHelper *ifsh);

    inline uint16_t getFreeRAM();
};
#endif /* ARD_LOG_H */
