/*
 wiring_digital.c - digital input and output functions
 Part of Arduino - http://www.arduino.cc/

 Copyright (c) 2013 Parav Nagarsheth
 Copyright (c) 2005-2006 David A. Mellis

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General
 Public License along with this library; if not, write to the
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA  02111-1307  USA

 Modified 28 September 2010 by Mark Sproul

 */

#include "wiring_digital.h"
#include "linux-virtual.h"
#include "virtual_main.h"
#include "Mux.h"
#include "pins_arduino.h"

WEAK void pinMode(uint8_t pin, uint8_t mode) {
    int pinIndex = pin - BASE_PIN_INDEX;
    if (pin > MAX_PIN_INDEX || pin < MIN_PIN_INDEX || !(g_APinDescription[pinIndex].pinType & GPIO))
        return;
    if (unlikely(g_APinDescription[pinIndex].state != GPIO)) {
        // the pin in GPIO capable but not configured as GPIO
        if (g_APinDescription[pinIndex].state < 0) {
            // the pin is locked, report an error
            perror("pin locked");
            return;
        }
        muxSelect(pinIndex, GPIO);
    }
    if (mode == INPUT)
        gpio_setdirection(g_APinDescription[pinIndex].gpioPin, "in");
    else
        gpio_setdirection(g_APinDescription[pinIndex].gpioPin, "out");
    return;
}

WEAK void digitalWrite(uint8_t pin, uint8_t val) {    
    int pinIndex = pin - BASE_PIN_INDEX;
    if ((pin > MAX_PIN_INDEX || pin < MIN_PIN_INDEX) || !((g_APinDescription[pinIndex].pinType & GPIO) || (g_APinDescription[pinIndex].pinType & LED)))
        return;

    if (unlikely(g_APinDescription[pinIndex].state == PWM)) {
        muxSelect(pinIndex, GPIO);
    }
    char buf[256];
    snprintf(buf, sizeof(buf), SYSFS_GPION_PATH, g_APinDescription[pinIndex].gpioPin);
    sysfs_write(buf, "value", val);
}

WEAK int digitalRead(uint8_t pin) {
    char value[4];
    int pinIndex = pin - BASE_PIN_INDEX;
    if (pin > MAX_PIN_INDEX || pin < MIN_PIN_INDEX || !(g_APinDescription[pinIndex].pinType & GPIO))
        return -1;
    if (unlikely(g_APinDescription[pinIndex].state == PWM)) {
        muxSelect(pinIndex, GPIO);
    }
    if (g_APinDescription[pinIndex].pinType & GPIO) {
        char buf[256];
        snprintf(buf, sizeof(buf), SYSFS_GPION_PATH, g_APinDescription[pinIndex].gpioPin);
        sysfs_read(buf, "value", value);
        return atoi(value);
    } else
        return 0;
}

