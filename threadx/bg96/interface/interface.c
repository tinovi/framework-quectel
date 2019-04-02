/*
 *  Created on: 09.05.2018
 *      Author: Georgi Angelov
 */

#include <txm_module.h>
#include <qapi_timer.h>
#include <debug.h>

ULONG __attribute__ ((section (".data")))
(*_txm_module_kernel_call_dispatcher)(ULONG type, ULONG param_1, ULONG param_2, ULONG param3) = NULL;

TXM_MODULE_THREAD_ENTRY_INFO * __attribute__ ((section (".data")))
_txm_module_entry_info = NULL;

TXM_MODULE_INSTANCE * __attribute__ ((section (".data")))
_txm_module_instance_ptr = NULL;

void __attribute__ ((section (".shell_entry")))
_txm_module_thread_shell_entry(TX_THREAD * thread_ptr, TXM_MODULE_THREAD_ENTRY_INFO * thread_info)
{
	if (thread_info->txm_module_thread_entry_info_start_thread) {
		_txm_module_instance_ptr = thread_info->txm_module_thread_entry_info_module;
		_txm_module_entry_info = thread_info;
		_txm_module_kernel_call_dispatcher = thread_info->txm_module_thread_entry_info_kernel_call_dispatcher;
		while (!_txm_module_kernel_call_dispatcher) {
			// NO EXIT
		}
		_txm_module_kernel_call_dispatcher(66, (ULONG) thread_info->txm_module_thread_entry_info_callback_request_thread, 0, 0);
	}
	thread_info->txm_module_thread_entry_info_entry(thread_info->txm_module_thread_entry_info_parameter);
	_txm_module_kernel_call_dispatcher(91, (ULONG) thread_ptr, 0, 0);
}

void __attribute__ ((section (".thread_callback")))
_txm_module_callback_request_thread_entry(ULONG id) {
	TXM_MODULE_CALLBACK_NOTIFY callback_message;
	do {
		if (((ULONG (*)(ULONG, ULONG, ULONG, ULONG)) _txm_module_kernel_call_dispatcher)(42, (ULONG) _txm_module_entry_info->txm_module_thread_entry_info_callback_request_queue, (ULONG) &callback_message, -1))
			break;
		switch (callback_message.txm_module_callback_notify_type) {
		case 0u:
			//((void (*)(ULONG)) callback_message.txm_module_callback_notify_application_function)(callback_message.txm_module_callback_notify_param_1);
			//break;
		case 1u:
			//((void (*)(ULONG)) callback_message.txm_module_callback_notify_application_function)(callback_message.txm_module_callback_notify_param_1);
			//break;
		case 2u:
			//((void (*)(ULONG)) callback_message.txm_module_callback_notify_application_function)(callback_message.txm_module_callback_notify_param_1);
			//break;
		case 3u:
			((void (*)(ULONG)) callback_message.txm_module_callback_notify_application_function)(callback_message.txm_module_callback_notify_param_1);
			break;
		case 4u:
			((void (*)(ULONG, ULONG)) callback_message.txm_module_callback_notify_application_function)(callback_message.txm_module_callback_notify_param_1, callback_message.txm_module_callback_notify_param_2);
			break;
		default:
			break;
		}
	} while (_txm_module_kernel_call_dispatcher(43, (ULONG) _txm_module_entry_info->txm_module_thread_entry_info_callback_response_queue, (ULONG) &callback_message, -1));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ULONG _txm_module_system_call4(ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4) {
	ULONG extra_parameters[2];
	extra_parameters[0] = param_3;
	extra_parameters[1] = param_4;
	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG) extra_parameters);
}

ULONG _txm_module_system_call5(ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5) {
	ULONG extra_parameters[3];
	extra_parameters[0] = param_3;
	extra_parameters[1] = param_4;
	extra_parameters[2] = param_5;
	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG) extra_parameters);
}

ULONG _txm_module_system_call6(ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6) {
	ULONG extra_parameters[4];
	extra_parameters[0] = param_3;
	extra_parameters[1] = param_4;
	extra_parameters[2] = param_5;
	extra_parameters[3] = param_6;
	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG) extra_parameters);
}

ULONG _txm_module_system_call7(ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6, ULONG param_7) {
	ULONG extra_parameters[5];
	extra_parameters[0] = param_3;
	extra_parameters[1] = param_4;
	extra_parameters[2] = param_5;
	extra_parameters[3] = param_6;
	extra_parameters[4] = param_7;
	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG) extra_parameters);
}

ULONG _txm_module_system_call8(ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6, ULONG param_7, ULONG param_8) {
	ULONG extra_parameters[6];
	extra_parameters[0] = param_3;
	extra_parameters[1] = param_4;
	extra_parameters[2] = param_5;
	extra_parameters[3] = param_6;
	extra_parameters[4] = param_7;
	extra_parameters[5] = param_8;
	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG) extra_parameters);
}

ULONG _txm_module_system_call9(ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6, ULONG param_7, ULONG param_8, ULONG param_9) {
	ULONG extra_parameters[7];
	extra_parameters[0] = param_3;
	extra_parameters[1] = param_4;
	extra_parameters[2] = param_5;
	extra_parameters[3] = param_6;
	extra_parameters[4] = param_7;
	extra_parameters[5] = param_8;
	extra_parameters[6] = param_9;
	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG) extra_parameters);
}

ULONG _txm_module_system_call10(ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6, ULONG param_7, ULONG param_8, ULONG param_9, ULONG param_10) {
	ULONG extra_parameters[8];
	extra_parameters[0] = param_3;
	extra_parameters[1] = param_4;
	extra_parameters[2] = param_5;
	extra_parameters[3] = param_6;
	extra_parameters[4] = param_7;
	extra_parameters[5] = param_8;
	extra_parameters[6] = param_9;
	extra_parameters[7] = param_10;
	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG) extra_parameters);
}

ULONG _txm_module_system_call11(ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6, ULONG param_7, ULONG param_8, ULONG param_9, ULONG param_10, ULONG param_11) {
	ULONG extra_parameters[9];
	extra_parameters[0] = param_3;
	extra_parameters[1] = param_4;
	extra_parameters[2] = param_5;
	extra_parameters[3] = param_6;
	extra_parameters[4] = param_7;
	extra_parameters[5] = param_8;
	extra_parameters[6] = param_9;
	extra_parameters[7] = param_10;
	extra_parameters[8] = param_11;
	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG) extra_parameters);
}

ULONG _txm_module_system_call12(ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6, ULONG param_7, ULONG param_8, ULONG param_9, ULONG param_10, ULONG param_11, ULONG param_12) {
	ULONG extra_parameters[10];
	extra_parameters[0] = param_3;
	extra_parameters[1] = param_4;
	extra_parameters[2] = param_5;
	extra_parameters[3] = param_6;
	extra_parameters[4] = param_7;
	extra_parameters[5] = param_8;
	extra_parameters[6] = param_9;
	extra_parameters[7] = param_10;
	extra_parameters[8] = param_11;
	extra_parameters[9] = param_12;
	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG) extra_parameters);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define HIDWORD(Z)	Z >> 32

static int timer_type_size = 0;
static int qapi_timer_user_initialized = 0;

void qapi_timer_user_init(void) {
	if (!timer_type_size && !qapi_timer_user_initialized) {
		_txm_module_system_call12(0x10102u, (ULONG) &timer_type_size, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		qapi_timer_user_initialized = 1;
	}
}

qapi_Status_t qapi_Timer_Def(qapi_TIMER_handle_t * timer_handle, qapi_TIMER_define_attr_t * timer_attr) {
	qapi_Status_t result;
	if (qapi_timer_user_initialized != 1)
		qapi_timer_user_init();
	if (!timer_handle)
		return -2;
	if (!timer_type_size)
		return -9;
	if (_txm_module_kernel_call_dispatcher(0x5Du, (ULONG) timer_handle, timer_type_size, 0))
		return -3;
	if (!*timer_handle)
		return -3;
	result = _txm_module_system_call12(0x100FAu, (ULONG) timer_handle, (ULONG) timer_attr, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	if (result)
		_txm_module_kernel_call_dispatcher(0x5Eu, (ULONG) timer_handle, 0, 0);
	return result;
}

qapi_Status_t qapi_Timer_Set(qapi_TIMER_handle_t timer_handle, qapi_TIMER_set_attr_t *timer_attr) {
	return _txm_module_system_call12(0x100FBu, (ULONG) timer_handle, (ULONG) timer_attr, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

qapi_Status_t qapi_Timer_Get_Timer_Info(qapi_TIMER_handle_t timer_handle, qapi_TIMER_get_info_attr_t *timer_get_info_attr, uint64_t *data) {
	return _txm_module_system_call12(0x100FFu, (ULONG) timer_handle, (ULONG) timer_get_info_attr, (ULONG) data, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

qapi_Status_t qapi_Timer_Sleep(uint64_t timeout, qapi_TIMER_unit_type unit, qbool_t non_deferrable) {
	return _txm_module_system_call12(0x10100u, HIDWORD(timeout), timeout, unit, non_deferrable, 0, 0, 0, 0, 0, 0, 0, 0);
}

qapi_Status_t qapi_Timer_Undef(qapi_TIMER_handle_t timer_handle) {
	qapi_Status_t result;
	result = _txm_module_system_call12(0x100FEu, (ULONG) timer_handle, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	if (!result)
		_txm_module_kernel_call_dispatcher(0x5Eu, (ULONG) timer_handle, 0, 0);
	return result;
}

qapi_Status_t qapi_Timer_Stop(qapi_TIMER_handle_t timer_handle) {
	return _txm_module_system_call12(0x100FDu, (ULONG) timer_handle, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

qapi_Status_t qapi_Timer_set_absolute(qapi_TIMER_handle_t timer_handle, uint64_t abs_time) {
	return _txm_module_system_call12(0x100FCu, (ULONG) timer_handle, HIDWORD(abs_time), abs_time, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

qapi_Status_t qapi_time_get(qapi_time_unit_type time_get_unit, qapi_time_get_t * time) {
	return _txm_module_system_call12(0x10101u, time_get_unit, (ULONG) time, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

