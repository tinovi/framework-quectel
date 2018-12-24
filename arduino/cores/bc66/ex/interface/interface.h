/*
 * interface.h
 *
 *  Created on: 08.08.2018
 *      Author: Georgi Angelov
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <_ansi.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


#include "ext_api.h"


#include "debug.h"
#include "device.h"

#include "custom_feature_def.h"
#include "ql_type.h"
#include "ql_system.h"
#include "ql_memory.h"
#include "ql_stdlib.h"
#include "ql_trace.h"
#include "ql_error.h"
#include "ql_common.h"
#include "ql_uart.h"
#include "ql_gpio.h"
#include "ql_adc.h"
#include "ql_pwm.h"
#include "ql_spi.h"
#include "ql_iic.h"
#include "ql_eint.h"
#include "ql_power.h"
#include "ql_rtc.h"
#include "ql_time.h"
#include "ql_timer.h"
#include "ql_wtd.h"
#include "ril.h"
#include "ril_system.h"
#include "ril_util.h"
#include "ril_lwm2m.h"
#include "ril_network.h"
#include "ril_onenet.h"
#include "ril_socket.h"

extern void __libc_init_array(void);
extern void __libc_fini_array(void);
void *memset(void *dst, int c, size_t n);

typedef enum {
	MSG_UART_OPEN = 0x1010,
	MSG_EINT_OPEN = 0x1011,
	MSG_ADC_OPEN  = 0x1012,
	MSG_TIMER_OPEN = 0x1013,


} message_e;

typedef struct {
	uint32_t event;
	unsigned int id;
	tel_conn_mgr_pdp_type_enum type;
	tel_conn_mgr_register_handle_t hdl;
	int result;
} pdp_context_t;
int pdp_act(const char * apn, const char * user, const char * pass, uint32_t timeout);
void pdp_deact(void);

typedef struct {
	uint32_t event;
	uint32_t count;
	uint32_t interval;
	uint32_t sampling;
	uint32_t value;
	int error;
} adc_context_t;

typedef enum /*Enum_URCType*/ {
    URC_STATE_SYS_BEGIN 	= 0,
    URC_STATE_SYS_INIT 		= 1,
    URC_STATE_SIM_CARD 		= 2,
    URC_STATE_NW_GSM 		= 3,
    URC_STATE_NW_GPRS 		= 4,
    URC_STATE_NW_EGPRS 		= 5,
    URC_STATE_CFUN,
    URC_STATE_COMING_CALL,
    URC_STATE_CALL,
    URC_STATE_NEW_SMS,
    URC_STATE_MODULE_VOLTAGE,
	URC_STATE_ALARM_RING,
	URC_STATE_SOCKET_RECV_DATA,       // Indication for recv data from server
	URC_STATE_SOCKET_CLOSE,           // Indication for close socket from server
	URC_STATE_LwM2M_RECV_DATA,        // Indication for  recv data from server
	URC_STATE_LwM2M_OBSERVE,          // Indication for recv observe
	URC_STATE_ONENET_EVENT,           // Indication for  Notify the TE of Event
	URC_STATE_ONENET_OBSERVE,         // Indication for  Notify the TE an Observe Request
	URC_STATE_ONENET_DISCOVER,        // Indication for Notify the TE to Respond the Discover Request
	URC_STATE_ONENET_WRITE,           // Indication for Notify the TE to Respond the Write Request
	URC_STATE_ONENET_READ,            // Indication fro Notify the TE to Response the Read Request
	URC_STATE_ONENET_EXECUTE,         // Indication for Notify the TE to Response the Execute Request

	RIL_READY,
	URC_STATE_MAX,
}urc_states_e;

typedef struct{
	uint32_t state[URC_STATE_MAX]; // collect URC values
	char imei[20];
	char version[20];
	pdp_context_t pdp;
	uint32_t event;
} device_t;

#define DEV_EVENT_RIL 	1
#define DEV_EVENT_SIM 	2

extern device_t dev;


#define	atoi 			Ql_atoi
#define atof 			Ql_atof
#define memcmp  		Ql_memcmp
#define memmove 		Ql_memmove
#define strcpy 			Ql_strcpy
#define strncpy 		Ql_strncpy
#define strcat			Ql_strcat
#define strncat 		Ql_strncat
#define strcmp			Ql_strcmp
#define strncmp			Ql_strncmp
#define strchr			Ql_strchr
#define strlen			Ql_strlen
#define strstr   		Ql_strstr
#define toupper  		Ql_toupper
#define tolower  		Ql_tolower
#define sprintf  		Ql_sprintf
#define snprintf  		Ql_snprintf
#define sscanf  		Ql_sscanf
#define strtok			Ql_strtok
#define strsep 			Ql_strsep

#define OK		0
#define ERROR  -1

#ifdef __cplusplus
}
#endif
#endif /* INTERFACE_H_ */
