/* mdaq_net.c -- Uart driver for MicroDAQ device
 *
 * Copyright (C) 2014 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#include <stdint.h>
#include <string.h>

#include "hardware.h"
#include "mdaq_rpc.h"
#include "mdaq_uart.h"

#define PINMUX_8	(8)
#define PINMUX_11	(11)

#define UART0_RX_NIBBLE	(3)
#define UART0_TX_NIBBLE	(4)

#define UART1_RX_NIBBLE	(2)
#define UART1_TX_NIBBLE	(3)

static void uart_set_pinmux(int port)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	uint32_t mux_conf = 0;
	volatile uint32_t *mux_addr = (uint32_t *)(SYS_CFG_BASE + 0x120);

	if(port == 0) 
	{
		mux_addr += PINMUX_8;
		mux_conf = *mux_addr;
		mux_conf &= ~(0xf << (UART0_RX_NIBBLE * 4));
		mux_conf |= 0x1 << (UART0_RX_NIBBLE * 4);
		mux_conf &= ~(0xf << (UART0_TX_NIBBLE * 4));
		mux_conf |= 0x1 << (UART0_TX_NIBBLE * 4);
		*mux_addr = mux_conf;
	}

	else if(port == 1)
	{
		mux_addr = (uint32_t *)(SYS_CFG_BASE + 0x120);
		mux_addr += PINMUX_11;
		mux_conf = *mux_addr;
		mux_conf &= ~(0xf << (UART1_RX_NIBBLE * 4));
		mux_conf |= 0x1 << (UART1_RX_NIBBLE * 4);
		mux_conf &= ~(0xf << (UART1_TX_NIBBLE * 4));
		mux_conf |= 0x1 << (UART1_TX_NIBBLE * 4);
		*mux_addr = mux_conf;
	}
#endif
}

int mdaq_uart_open(int port_num)
{
	int result = -1;
	mdaq_rpc_t call;

	uart_set_pinmux(port_num);

	memset((void *)&call, 0x0, sizeof(mdaq_rpc_t));
	call.func 		 = MDAQUART_OPEN;
	call.args[1].i32 = port_num;

	call.result = -1;

	result = mdaq_rpc_exec( &call, WAIT_FOREVER, NULL, 0, 0);

	return (result < 0) ? result : call.result;
}

int mdaq_uart_write(int port, void *data, int len)
{
	int result = -1;
	mdaq_rpc_t call;

	memset((void *)&call, 0x0, sizeof(mdaq_rpc_t));
	call.func 		 = MDAQUART_WRITE;
	call.args[0].i32 = port;
	call.args[1].i32 = len;

	call.result = -1;

	result = mdaq_rpc_exec( &call, WAIT_FOREVER, data, len, 0);

	return (result < 0) ? result : call.result;
}

int mdaq_uart_read(int port, void *data, int len, int timeout)
{
	int result = -1;
	mdaq_rpc_t call;

	memset((void *)&call, 0x0, sizeof(mdaq_rpc_t));
	call.func 		 = MDAQUART_READ;
	call.args[0].i32 = port;
	call.args[1].i32 = len;
	call.args[2].i32 = timeout * 10;

	call.result = -1;

	result = mdaq_rpc_exec( &call, WAIT_FOREVER, data, len, 1);

	return (result < 0) ? result : call.result;
}

int mdaq_uart_setspeed(int speed)
{
	int result = -1;
	mdaq_rpc_t call;

	memset((void *)&call, 0x0, sizeof(mdaq_rpc_t));
	call.func 		 = MDAQUART_SETSPEED;
	call.args[1].i32 = speed;

	call.result = -1;

	result = mdaq_rpc_exec( &call, WAIT_FOREVER, NULL, 0, 0);

	return (result < 0) ? result : call.result;
}

int mdaq_uart_config(int port, mdaq_uart_config_t *c )
{
	int result = -1;
	mdaq_rpc_t call;

	if ( c->baud_rate < B2400 || c->baud_rate > B115200 )
		return -1;

	if (c->data_bits < 5 || c->data_bits > 8)
		return -1;

	if (c->stop_bits < 1 || c->stop_bits > 2)
		return -1;

	memset((void *)&call, 0x0, sizeof(mdaq_rpc_t));
	call.func 		 = MDAQUART_SETSPEED;

	call.args[0].i32 = port;
	call.args[1].i32 = c->baud_rate;
	call.args[2].i32 = c->data_bits;
	call.args[3].i32 = c->parity;
	call.args[4].i32 = c->stop_bits;
	call.args[5].i32 = c->flow_control;

	call.result = -1;

	result = mdaq_rpc_exec( &call, WAIT_FOREVER, NULL, 0, 0);

	return (result < 0) ? result : call.result;
}


int mdaq_uart_close(int port)
{
	int result = -1;
	mdaq_rpc_t call;

	memset((void *)&call, 0x0, sizeof(mdaq_rpc_t));
	call.func 		 = MDAQUART_CLOSE;
	call.args[0].i32 = port;

	call.result = -1;

	result = mdaq_rpc_exec( &call, WAIT_FOREVER, NULL, 0, 0);

	return (result < 0) ? result : call.result;
}

int mdaq_uart_init( void )
{
	mdaq_rpc_init();
	return 0;
}

