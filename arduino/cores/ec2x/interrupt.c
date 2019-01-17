/* interrupt.c  Interruption interface
Copyright (C) 2014 Intel Corporation

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
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

/*
 * Provides a pseudo interrupt inteface which is broadly an analoge of the Arduino pin based interrupt
 * callback mechanism
 * We don't support 'real' interrupts from kernel to user-space right now since that's way out of scope
 *
 * Author: Bryan O'Donoghue <bryan.odonoghue@intel.com>
 */

#define _GNU_SOURCE
#include <assert.h>
#include <errno.h>
#include <fcntl.h>              /* Obtain O_* constant definitions */
#include <netinet/in.h>
#include <mqueue.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <linux/hpet.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>

#include <interrupt.h>
#include <variant.h>
#include <wiring_digital.h>
#include <sysfs.h>
#include <poll.h>

/**
 * Attach a callback to a gpio edge interrupt asynchronous to sketch loop();
 *
 * function : the function to call when the interrupt occurs
 * microseconds: defines when the interrupt should be triggered in the timing loop. Must be even multiple of idesc.hpet_freq
 */

pthread_t pinInterrupts[PINS_COUNT];

struct interrupt_thread_param
{
	int32_t pin;
	uint32_t mode;
	int gpio_fd;
	void (*callback)(void);
};

void *interruptHandler(void *arg) {
	struct interrupt_thread_param *params = (struct interrupt_thread_param *)arg;
	struct pollfd fdset;
	int nfds = 1;
	char buf[1];

	fdset.fd = params->gpio_fd;
	fdset.events = POLLPRI;

	while (1) {
	
		read(params->gpio_fd, buf, 1);
		poll(&fdset, nfds, -1);

		if (fdset.revents & POLLPRI) {
			params->callback();
		}
	}
}

void attachInterrupt(uint32_t pin, void (*callback)(void), uint32_t mode) {
	//TODO
}

void detachInterrupt(uint32_t pin) {
	//TODO
}


/**
 * Attach a callback to a timer 'interrupt' asynchronous to sketch loop();
 *
 * function : the function to call when the interrupt occurs
 * microseconds: defines when the interrupt should be triggered in the timing loop. Must be even multiple of idesc.hpet_freq
 */
struct timer_thread_param {
	int32_t microseconds;
	void (*callback)(void);
};

void *timerHandler(void *arg) {
	struct timer_thread_param *params = (struct timer_thread_param *)arg;
	usleep(params->microseconds);
	params->callback();
}

void attachTimerInterrupt(void (*callback)(void), int32_t microseconds) {
	struct timer_thread_param *params;
	params=(struct timer_thread_param *)malloc(sizeof(struct timer_thread_param));
	params->microseconds = microseconds;
	params->callback = callback;
	pthread_t timerThread;
	pthread_create( &timerThread, NULL, timerHandler, (void*)params);
	pthread_detach(timerThread);
}