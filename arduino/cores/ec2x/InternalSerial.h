/*
  HardwareSerial.h - Hardware serial library for Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 2  April	2018 by Georgi Angelov
*/

#ifndef InternalSerialh
#define InternalSerialh

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <termios.h>
#include <sys/select.h>
#include <pthread.h>

class InternalSerial
{
    private:
        void config_port(void);
        void reset_port(void);

    public:
        InternalSerial(const char *);
        int fd;
        static fd_set tty_set;
        static int max_fd;
        const char * port_path;
        void flush();
        void begin(void);
        void end(void);
        int write(void * data, size_t count);
        int write(char * str);
        ssize_t read(void * buf, size_t count);
};

#endif

