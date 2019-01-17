/*
 * trace.h
 */

#ifndef __TRACE_H__
#define __TRACE_H__

#ifdef __cplusplus
extern "C" {
#endif

#define trace printf

#define trace_debug(fmt, ...)   trace("[DBG] "); trace(fmt, ##__VA_ARGS__) 
#define trace_info(fmt , ...)   trace("[INF] "); trace(fmt, ##__VA_ARGS__) 
#define trace_error(fmt , ...)  trace("[ERR] "); trace(fmt, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif


#endif /* __TRACE_H__ */

