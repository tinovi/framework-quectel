/*
    BG96 - MAIN
    Created on: 01.01.2019
    Author: Georgi Angelov  
 */

#include <_ansi.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#include <qapi_types.h>
#include <qapi.h>
#include <qapi_status.h>
#include <qapi_uart.h>
#include <qapi_timer.h>
#include <qapi_device_info.h>
#include <qurt_timetick.h>
#include <quectel_utils.h>
#include <quectel_uart_apis.h>

static char *rx_buff = NULL;
static char *tx_buff = NULL;
static QT_UART_CONF_PARA uart_conf;

void *_sbrk(intptr_t increment) { return (void *)-1; }

void quectel_dbg_uart_init(qapi_UART_Port_Id_e port_id)
{
    uart_conf.hdlr = NULL;
    uart_conf.port_id = port_id;
    uart_conf.tx_buff = tx_buff;
    uart_conf.tx_len = sizeof(tx_buff);
    uart_conf.rx_buff = rx_buff;
    uart_conf.rx_len = sizeof(rx_buff);
    uart_conf.baudrate = 115200;
    uart_init(&uart_conf);
}

__attribute__((section(".library"))) int TXM_MODULE_THREAD_ENTRY(void)
{
    quectel_dbg_uart_init(QAPI_UART_PORT_002_E);
    qt_uart_dbg(uart_conf.hdlr, "\nSETUP");
    while (1)
    {
        qt_uart_dbg(uart_conf.hdlr, "LOOP");
        tx_thread_sleep(500); // only main thread or qapi_Timer_Sleep(500, QAPI_TIMER_UNIT_TICK, 1);
    }
}