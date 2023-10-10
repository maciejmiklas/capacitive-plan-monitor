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
#include "Reader.h"

Reader::Reader(ReaderSupplier* supplier)
  : supplier(supplier) {
}

uint16_t Reader::read() {
  uint16_t probes[RE_PROBES];
  for (uint8_t i = 0; i < RE_PROBES; i++) {
    probes[i] = supplier->read();
  }
  sort_u16(probes, RE_PROBES);
  uint16_t val = probes[RE_PROBE_AT];

#if LOG && LOG_RE
  log(F("%s RV %s=%d [%d,%d,%d]"), NAME, supplier->name(), val, probes[0], probes[1], probes[2]);
#endif

  return val;
}
