/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <variant.h>
#include <wordexp.h>
#include <unistd.h>
#include <interface/ql_oe.h>
#include "virtual_main.h"
#include "HardwareSerial.h"
#include "DebugSerial.h"


#ifdef __cplusplus
extern "C" {
#endif

#define ARRAY_SIZE(arr)         ( sizeof(arr) / sizeof( (arr)[0]) )

#define PIN_DEF(x, y, z, r, f)  { x, y, z, r, f } 

/*  Pins descriptions */
PinDescription g_APinDescription[] = {
  /*PIN-1*/  PIN_DEF(0,  25,  GPIO, 0, NULL), //pin-1
  /*PIN-2*/  PIN_DEF(1,  10,  GPIO, 0, NULL), //pin-
  /*PIN-3*/  PIN_DEF(2,  42,  GPIO, 0, NULL), //pin-
  /*PIN-4*/  PIN_DEF(3,  11,  GPIO, 0, NULL), //pin-
  /*PIN-5*/  PIN_DEF(4,  24,  GPIO, 0, NULL), //pin-
  /*PIN-13*/ PIN_DEF(5,  34,  GPIO, 0, NULL), //pin-
} ;

#ifdef __cplusplus
}
#endif

const unsigned int MAX_PIN = ARRAY_SIZE(g_APinDescription);

HardwareSerial  Serial(PORT_TTY_NATIVE(0));
HardwareSerial  Serial1(PORT_TTY_NATIVE(3), true);
HardwareSerial  SerialUSB(PORT_TTY_CDC(0));
DebugSerial_    DebugSerial(DEV_CONSOLE);

#ifdef __cplusplus
extern "C" {
#endif

int muxSelect(uint8_t pin, uint32_t newFunction) {
    //TODO
    return 0;
}

#ifdef __cplusplus
}
#endif
