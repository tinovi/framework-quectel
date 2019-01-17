/*
  HardwareSerial.cpp - Hardware serial library for Wiring
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

#include <unistd.h>
#include <fcntl.h>

#include "wiring.h"
#include "InternalSerial.h"
#include "trace.h"

fd_set InternalSerial::tty_set;
int    InternalSerial::max_fd = 0;

InternalSerial::InternalSerial(const char * path) {
	port_path = path;
}

void InternalSerial::reset_port(void) {
	tcflush(fd, TCIFLUSH);
	::close(fd);
}

void InternalSerial::config_port(void) {
	fd = open(port_path, O_RDWR | O_NOCTTY | O_NONBLOCK);
	if(fd < 0) {
	    trace_error("port open( %s ) = %d\n", port_path, fd);
	    exit(-1);
	}
	if ((fd + 1) > max_fd)
	    max_fd = fd + 1;
}

void InternalSerial::begin(void) {
	config_port();
}

void InternalSerial::flush() {
	tcflush(fd, TCIFLUSH);
}

void InternalSerial::end() {
	reset_port();
}

int InternalSerial::write(void * buf, size_t count) {
    int res = ::write(fd, buf, count);
	return res;
}

int InternalSerial::write(char * str) {
    return write(str, strlen(str));
}

ssize_t InternalSerial::read(void * buf, size_t count) {
	FD_ZERO(&tty_set);
	FD_SET(fd, &tty_set);
	select(max_fd, &tty_set, NULL, NULL, 0);
	if (FD_ISSET(fd, &tty_set))
		return ::read(fd, buf, count);
	return 0;
}