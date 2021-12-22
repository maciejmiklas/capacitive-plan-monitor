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

/** Logs free RAM if it has changed on every log_cycle() call. */
#define LOG_FREE_RAM true

#if ENABLE_LOGGER

  class Logger {
    public:
      Logger();
      void setup();
      void lnv(const __FlashStringHelper *ifsh, va_list args);
      void ln(const __FlashStringHelper *ifsh, ...);
      void lnRAM(char const *msg);
      void lnChangeRAM();

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

  Logger::Logger(){

  }

  inline void Logger::resetBuf(char *buf, uint8_t size) {
    for (uint8_t idx = 0; idx < size; idx++) {
      buf[idx] = '\0';
    }
  }

  inline void Logger::resetSbuf() {
    resetBuf(sbuf, SBUF_SIZE);
  }

  inline void Logger::resetPgbuf() {
    resetBuf(pgbuf, PGBUF_SIZE);
  }

  inline void Logger::copyPGM(const __FlashStringHelper *ifsh) {
    strcpy_P(pgbuf, (char *)ifsh);
  }

  void Logger::setup() {
    Serial.begin(SERIAL_SPEED);
    log_cycle();
    #if LOG_FREE_RAM
      log(F("LOG ON,RAM:%u"), getFreeRAM());
    #endif
  }

  void Logger::lnRAM(char const *msg) {
    uint16_t free = getFreeRAM();
    log(F("RAM(%s):%u"), msg, free);
  }

  void Logger::lnChangeRAM() {
    uint16_t free = getFreeRAM();
    if (lastFreeRam != free) {
      lastFreeRam = free;
      log(F("RAM:%u"), free);
    }
  }

  inline uint16_t Logger::getFreeRAM() {
    extern int __heap_start, *__brkval;
    int v;
    return (uint16_t)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
  }

  void Logger::lnv(const __FlashStringHelper *ifsh, va_list va) {
    resetPgbuf();
    resetSbuf();

    copyPGM(ifsh);
    vsprintf(sbuf, pgbuf, va);
    Serial.println(sbuf);
  }

  void Logger::ln(const __FlashStringHelper *ifsh, ...) {
    va_list va;
    va_start(va, ifsh);
    lnv(ifsh, va);
    va_end(va);
  }

  // ######################
  // ### Global Methods ###
  // ######################
  Logger* logger = new Logger();

  void log_setup() {
    logger->setup();
  }

  void log_cycle() {
    #if LOG_FREE_RAM
      logger->lnChangeRAM();
    #endif
  }

  void log(const __FlashStringHelper *ifsh, ...) {
    va_list va;
    va_start(va, ifsh);
    logger->lnv(ifsh, va);
    va_end(va);
  }

#endif  // ENABLE_LOGGER