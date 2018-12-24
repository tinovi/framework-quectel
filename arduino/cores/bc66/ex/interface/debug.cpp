/*
 * debug.c
 *
 *  Created on: 08.08.2018
 *      Author: Georgi Angelov
 */
#include "interface.h"

#if DEBUG > 0

char DEBUG_BUFFER[ DEBUG_SIZE ];
extern void uart_callback(Enum_SerialPort port, Enum_UARTEventType msg, bool level, void * user);

void debug_init(void) {
	if ( Ql_UART_Register(DEBUG_PORT, uart_callback, NULL) ) return;
	if ( Ql_UART_Open(DEBUG_PORT, 115200, FC_NONE) ) return;
	LOG("[DBG] READY\n");
}

#endif