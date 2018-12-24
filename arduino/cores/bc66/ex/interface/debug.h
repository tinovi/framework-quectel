/*
 * debug.h
 *
 *  Created on: 08.08.2018
 *      Author: Georgi Angelov
 */

#ifndef DEBUG_H_
#define DEBUG_H_
#ifdef __cplusplus
extern "C" {
#endif

#if DEBUG > 0 /* form global settings */

#include "ql_uart.h"
#include "ql_stdlib.h"
void debug(char * fmt, ...);
void debug_init(void);

#define DEBUG_PORT      UART_PORT0
#define DEBUG_SIZE      512
extern char DEBUG_BUFFER[ DEBUG_SIZE ];
#define LOG(FORMAT, ... ) { \
    Ql_sprintf(DEBUG_BUFFER, FORMAT, ##__VA_ARGS__); \
    Ql_UART_Write((Enum_SerialPort)(DEBUG_PORT), (u8*)(DEBUG_BUFFER), Ql_strlen((const char *)(DEBUG_BUFFER))); \
}

#else
#   define LOG(FORMAT, ... )
#endif

#ifdef __cplusplus
}
#endif
#endif /* DEBUG_H_ */
