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
#include "LED.h"

LED::LED()
  : brightness(BM_BRIGHTNESS_INITIAL) {
}

void LED::setup() {
  for (uint8_t pin = FIRST_PIN; pin <= LAST_PIN; pin++) {
    pinMode(pin, OUTPUT);
    analogWrite(pin, LOW);
  }
}

void LED::demo() {
  for (uint8_t bl = 0; bl < LE_DEMO_BLNIKS; bl++) {
    for (uint8_t pin = FIRST_PIN; pin <= LAST_PIN; pin++) {
      LedPin pinEn = static_cast<LedPin>(pin);
      on(pinEn);
      delay(LE_DEMO_DELAY_MS);
      off(pinEn);
      delay(LE_DEMO_DELAY_MS);
    }
  }
}

void LED::off(LedPin led) {
  uint8_t pin = led;
#if LOG && LOG_LE
  log(F("%s OFF %d"), NAME, pin);
#endif
  analogWrite(pin, LOW);
}

void LED::on(LedPin led) {
  uint8_t pin = led;
#if LOG && LOG_LE
  log(F("%s ON %d %d"), NAME, pin, brightness);
#endif
  analogWrite(pin, brightness);
}

const char* LED::listenerName() {
  return NAME;
}

void LED::onEvent(BusEvent event, va_list ap) {
  if (event == BusEvent::BTN_ADJ_SENSOR || event == BusEvent::BTN_BRIGHTNESS) {
    blinkOnButton();

  } else if (event == BusEvent::SYSTEM_INIT) {
    setup();

  } else if (event == BusEvent::BRIGHTNESS_MAX) {
    blinkOnMaxBrightness();

  } else if (event == BusEvent::BRIGHTNESS_CHANGE) {
    brightness = va_arg(ap, uint16_t);

  } else if (event == BusEvent::VCC_LOW) {
    lowPowerOn();

  } else if (event == BusEvent::VCC_NORMAL) {
    lowPowerOff();
  }
}

void LED::lowPowerOn() {  // TODO should be blinking
  on(LedPin::PWR_LOW);
}

void LED::lowPowerOff() {
  off(LedPin::PWR_LOW);
}

void LED::blinkOnMaxBrightness() {
  for (uint8_t i = 0; i < LED_BR_MAX_BLINK_REPEAT; i++) {
    off(LedPin::AWAKE);
    delay(LED_BR_MAX_BLINK_OFF_MS);
    on(LedPin::AWAKE);
    delay(LED_BR_MAX_BLINK_ON_MS);
  }
  on(LedPin::AWAKE);
}

void LED::blinkOnButton() {
  for (uint8_t i = 0; i < LE_PRESS_BLINK_REPEAT; i++) {
    off(LedPin::AWAKE);
    delay(LE_PRESS_BLINK_OFF_MS);
    on(LedPin::AWAKE);
    delay(LE_PRESS_BLINK_ON_MS);
  }
  on(LedPin::AWAKE);
}
