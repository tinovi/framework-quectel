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
*/

#ifndef _VARIANT_EC25_EVB_
#define _VARIANT_EC25_EVB_

#include "virtual_main.h"
#include <stdio.h>

#define F_CPU                   (1200000000UL)

#define A0	                    0
#define A1	                    0

#define SDA                     0
#define SCL                     0

#define MOSI                    0
#define MISO                    0
#define SCK                     0


#define PINS_COUNT              (6u)
#define LED_BUILTIN             0

#define BASE_PIN_INDEX          0
#define MAX_PIN_INDEX           BASE_PIN_INDEX + PINS_COUNT - 1
#define MIN_PIN_INDEX           BASE_PIN_INDEX

#define DEV_CONSOLE             "/dev/console"

#define SYSFS_GPIO_PATH         "/sys/class/gpio/"
#define SYSFS_GPION_PATH        "/sys/class/gpio/gpio%d/"

#define DEV_UART_PATH           "/dev/ttyHSL%d"
#define DEV_USB_PATH            "/dev/ttyUSB0"

#define DEV_SPI_PATH            "/dev/spidev1.1"
#define DEV_I2C_PATH            "/dev/i2c-2"

#define PORT_SMD(n)             "/dev/smd"#n /* AT-8, NMEA-7*/
#define PORT_TTY_NATIVE(n)      "/dev/ttyHSL"#n
#define PORT_TTY_CDC(n)         "/dev/ttyGS"#n

#define SYSFS_ADC_PATH          "/dev/null"
#define SYSFS_PWM_PATH          "/dev/null"
#define SYSFS_PWMN_PATH         "/dev/null"

#endif // _VARIANT_EC25_EVB_