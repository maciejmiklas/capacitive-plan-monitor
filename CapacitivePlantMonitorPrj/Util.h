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
#ifndef UTIL_H
#define UTIL_H

#include <Arduino.h>

void util_setup();
void util_cycle();
uint32_t util_ms();

inline int comp_16(const void *cmp1, const void *cmp2) {
  uint16_t a = *((uint16_t *)cmp1);
  uint16_t b = *((uint16_t *)cmp2);
  return a - b;
}

inline void sort_16(uint16_t arr[], uint8_t size) {
  qsort(arr, size, sizeof(arr[0]), comp_16);
}

#endif  // UTIL_H