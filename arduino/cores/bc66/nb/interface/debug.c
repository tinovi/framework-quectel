/*
 * debug.c
 *
 *  Created on: 08.08.2018
 *      Author: Georgi Angelov
 */
#include "interface.h"

#if DEBUG_ENABLE > 0

char DBG_BUFFER[DBG_BUF_LEN];

static void CallBack_UART_Hdlr(Enum_SerialPort port, Enum_UARTEventType msg, bool level, void* customizedPara){}

void debug_init(void) {
	if ( Ql_UART_Register(DEBUG_PORT, CallBack_UART_Hdlr, NULL) )
		return;
	if (Ql_UART_Open(DEBUG_PORT, 115200, FC_NONE))
		return;
	LOG("[DBG] READY\n");
}

#endif