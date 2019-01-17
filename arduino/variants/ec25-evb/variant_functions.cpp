/*
 Copyright (c) 2015 Arduino LLC.  All right reserved.
 Martino Facchin <m.facchin@arduino.cc>

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
 
 MOD: Georgi Angelov
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <variant.h>

#ifdef __cplusplus
extern "C" {
#endif

void digitalWrite(uint8_t pin, uint8_t value) {
    //TODO
}

int digitalRead(uint8_t pin) {
    //TODO
    return 0;
}

void pinMode(uint8_t pin, uint8_t mode) {
    //TODO
}

#ifdef __cplusplus
}
#endif
