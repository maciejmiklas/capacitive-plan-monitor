#include "ArdLog.h"

#if ENABLE_LOGGER

#if LOG_TIME
static struct Time {
	uint16_t dd;
	uint8_t hh;
	uint8_t mm;
	uint8_t ss;
	uint16_t ml;
} ts;
#endif

#if LOG_FREE_RAM
static uint16_t lastRam = 0;
#endif

/** Buffer for created message */
static char sbuf[SBUF_SIZE] = { 0 };

/** Buffer for sprintf-template passed as first argument to log method. */
static char pgbuf[PGBUF_SIZE] = { 0 };

#if LOG_TIME
const static uint16_t TR_MS_SEC = 1000;
const static uint32_t TR_SEC_DD = 86400;
const static uint16_t TR_SEC_HH = 3600;
const static uint16_t TR_SEC_MM = 60;
#endif // LOG_TIME

static inline HardwareSerial& serial();
static inline void pgmCopy(const __FlashStringHelper *ifsh);
static inline void reset_pgbuf();
static inline void reset_sbuf();
static inline void resetbuf(char *buf, uint8_t size);

#if LOG_FREE_RAM
  static inline void freeRAMln();
  static inline uint16_t getFreeRam();
#endif

#if LOG_TIME
  static inline void sampleTime();
#endif // LOG_TIME

void log_setup() {
	serial().begin(SERIAL_SPEED);
	log_cycle();
  #if LOG_FREE_RAM
    log(F("LOG ON,RAM:%u"), getFreeRam());
  #endif
}

#if LOG_FREE_RAM
  void log_freeRAM(char const *msg) {
    uint16_t free = getFreeRam();
    log(F("RAM(%s):%u"), msg, free);
  }

  static inline uint16_t getFreeRam() {
    extern int __heap_start, *__brkval;
    int v;
    return (uint16_t) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
  }

  static inline void freeRAMln() {
    uint16_t free = getFreeRam();
    if (lastRam != free) {
      lastRam = free;
      log(F("RAM:%u"), free);
    }
  }
#endif

void log_cycle() {
  #if LOG_TIME
    sampleTime();
  #endif

  #if LOG_FREE_RAM
    freeRAMln();
  #endif
}

#if ENABLE_LOGGER
void logs(const char* msg, uint8_t size) {
	HardwareSerial &ser = serial();
	ser.write(msg, size);
	ser.print('\n');
}

void logs(const __FlashStringHelper *ifsh, char* msg, uint8_t size) {
	HardwareSerial &ser = serial();
	reset_sbuf();
	pgmCopy(ifsh);
	ser.print(pgbuf);
	msg[size - 1] = '\0';
	ser.write(msg);
	ser.print('\n');
}

void logc(char val) {
	HardwareSerial &ser = serial();
	ser.print(val);
}

void logs(const __FlashStringHelper *ifsh, const char* msg, uint8_t size) {
	HardwareSerial &ser = serial();

	reset_sbuf();
	pgmCopy(ifsh);
	ser.print(pgbuf);
	ser.write(msg, size);
	ser.print('\n');
}
#endif // ENABLE_LOGS

void log(const __FlashStringHelper *ifsh, ...) {
#if USE_CURRENT_TIME
	sampleTime();
#endif

	HardwareSerial &ser = serial();
	reset_sbuf();
#if LOG_FULL_TIME
	sprintf(sbuf, ">[%03u-%02u:%02u:%02u,%03u]>", ts.dd, ts.hh, ts.mm, ts.ss, ts.ml);
#endif

#if LOG_SHORT_TIME
	sprintf(sbuf, ">[%02u:%02u,%03u]>", ts.mm, ts.ss, ts.ml);
#endif
	ser.print(sbuf);
	// print the message
	reset_pgbuf();
	reset_sbuf();

	pgmCopy(ifsh);
	va_list va;
	va_start(va, ifsh);
	vsprintf(sbuf, pgbuf, va);
	va_end(va);
	ser.println(sbuf);
}
// ###########################################################
// ### Private methods
// ###########################################################

#if LOG_TIME
//long milis =  126000000 + 1440000 + 17000;// 1d 11h 24m 17s
//long milis =  345600000 + 1440000 + 17000;// 4d 0h 24m 17s
//long milis =  446400000 + 1440000 + 17000;// 5d 4h 24m 17s
static inline void sampleTime() {
	uint32_t cycleMs = util_ms();
	uint32_t sec = cycleMs / TR_MS_SEC;

	// days
	ts.dd = sec / TR_SEC_DD;
	uint32_t tmp = sec - ts.dd * TR_SEC_DD;

	// hours of a day
	ts.hh = tmp / TR_SEC_HH;
	tmp -= ts.hh * TR_SEC_HH;

	// minutes of an hour
	ts.mm = tmp / TR_SEC_MM;
	tmp -= ts.mm * TR_SEC_MM;

	// seconds of a minute
	ts.ss = tmp;

	// millis of a second
	ts.ml = (cycleMs % 1000);
}
#endif // LOG_TIME

static inline HardwareSerial& serial() {
#if USE_SERIAL_1
	return Serial1;
#endif

#if USE_SERIAL_2
	return Serial2;
#endif

#if USE_SERIAL_3
	return Serial3;
#endif

	return Serial;
}

static inline void resetbuf(char *buf, uint8_t size) {
	for (uint8_t idx = 0; idx < size; idx++) {
		buf[idx] = '\0';
	}
}

static inline void reset_sbuf() {
	resetbuf(sbuf, SBUF_SIZE);
}

static inline void reset_pgbuf() {
	resetbuf(pgbuf, PGBUF_SIZE);
}

static inline void pgmCopy(const __FlashStringHelper *ifsh) {
	strcpy_P(pgbuf, (char*)ifsh);
}

#endif // ENABLE_LOGGER


