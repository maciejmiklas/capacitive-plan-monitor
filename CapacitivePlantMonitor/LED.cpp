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

LED* refLED;

void led_onButtonPress(va_list ap){
  refLED->onButtonPress();
}

void led_onMaxBrightness(va_list ap){
  refLED->onMaxBrightness();
}

void led_onBrightnessChange(va_list ap){
  refLED->onBrightnessChange(va_arg(ap, uint16_t));;
}

void led_onPowerLow(va_list ap){
  refLED->onPowerLow();
}

void led_onPowerNominal(va_list ap){
  refLED->onPowerNominal();
}

void led_onStandByOn(va_list ap){
  refLED->onStandByOn();
}

void led_onStandByOff(va_list ap){
  refLED->onStandByOff();
}

LED::LED()
  : brightness(BM_BRIGHTNESS_INITIAL) {
  powerLow = new LEDBlink(LedPin::PWR_LOW, LE_PWR_LOW_ON_DELAY, LE_PWR_LOW_OFF_DELAY, LE_PWR_LOW_ON_BRIGHTNESS, LE_PWR_LOW_OFF_BRIGHTNESS);
}

void LED::setup() {
  powerLow->setup();
  
  for (uint8_t pin = FIRST_PIN; pin <= LAST_PIN; pin++) {
    pinMode(pin, OUTPUT);
    analogWrite(pin, LOW);
  }

  refLED = this;

  eb_reg(BusEvent::BTN_ADJ_SENSOR, &led_onButtonPress);
  eb_reg(BusEvent::BTN_BRIGHTNESS, &led_onButtonPress);
  eb_reg(BusEvent::BRIGHTNESS_MAX, &led_onMaxBrightness);
  eb_reg(BusEvent::BRIGHTNESS_CHANGE, &led_onBrightnessChange);
  eb_reg(BusEvent::VCC_LOW, &led_onPowerLow);
  eb_reg(BusEvent::VCC_NOMINAL, &led_onPowerNominal);
  eb_reg(BusEvent::STANDBY_ON, &led_onStandByOn);
  eb_reg(BusEvent::STANDBY_OFF, &led_onStandByOff);
}

void LED::demo() {
  for (uint8_t bl = 0; bl < LE_DEMO_BLNIKS; bl++) {
    for (uint8_t pin = FIRST_PIN; pin <= LAST_PIN; pin++) {
      LedPin pinEn = static_cast<LedPin>(pin);
      on(pinEn);
      delay(LE_DEMO_DELAY);
      off(pinEn);
      delay(LE_DEMO_DELAY);
    }
  }
}

void LED::demosDone() {
   on(LedPin::AWAKE);
}

void LED::off(LedPin led) {
  uint8_t pin = led;
#if LOG && LOG_LE
  log(F("%s OFF %d"), NAME, pin);
#endif
  analogWrite(pin, LOW);
}

void LED::on(LedPin led) {
  on(led, brightness);
}

void LED::on(LedPin led, uint8_t brightness) {
  uint8_t pin = led;
#if LOG && LOG_LE
  log(F("%s ON %d %d"), NAME, pin, brightness);
#endif
  analogWrite(pin, brightness);
}

void LED::onStandByOn() {
  off(LedPin::AWAKE);
}

void LED::onStandByOff() {
  on(LedPin::AWAKE);
}

void LED::onBrightnessChange(uint8_t newbr) {
  brightness = newbr;
}

void LED::onPowerLow() {
  powerLow->on();
}

void LED::onPowerNominal() {
  powerLow->off();
}

void LED::onMaxBrightness() {
  for (uint8_t i = 0; i < LED_BR_MAX_BLINK_REPEAT; i++) {
    off(LedPin::AWAKE);
    delay(LED_BR_MAX_BLINK_OFF_DELAY);
    on(LedPin::AWAKE);
    delay(LED_BR_MAX_BLINK_ON_DELAY);
  }
  on(LedPin::AWAKE);
}

void LED::onButtonPress() {
  for (uint8_t i = 0; i < LE_PRESS_BLINK_REPEAT; i++) {
    off(LedPin::AWAKE);
    delay(LE_PRESS_BLINK_OFF_DELAY);
    on(LedPin::AWAKE);
    delay(LE_PRESS_BLINK_ON_DELAY);
  }
  on(LedPin::AWAKE);
}
