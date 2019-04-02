/*
 * debug.h
 *
 *  Created on: 13.05.2018
 *      Author: Georgi Angelov
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define DEBUG

#ifdef DEBUG

void dbg_set(void * p);
void dbg_printf(char * format, ...);
void dbg_printf_ex(char * format, ...);

#define DBG_SET(_F_)		do { dbg_set(_F_); } while(0)
#define TRACE_T(fmt, ...)  	do { dbg_printf_ex(fmt, ##__VA_ARGS__); } while(0)
#define TRACE_D(fmt, ...)  	do { dbg_printf("[DBG] "); dbg_printf(fmt, ##__VA_ARGS__); } while(0)
#define TRACE_I(fmt, ...)  	do { dbg_printf("[INF] "); dbg_printf(fmt, ##__VA_ARGS__); } while(0)
#define TRACE_E(fmt, ...)  	do { dbg_printf("[ERR] "); dbg_printf(fmt, ##__VA_ARGS__); } while(0)

#else // DEBUG

#define DBG_SET(_H_)
#define TRACE_T(fmt, ...)
#define TRACE_D(fmt, ...)
#define TRACE_I(fmt, ...)
#define TRACE_E(fmt, ...)

#endif

#ifdef __cplusplus
}
#endif

#endif /* DEBUG_H_ */
