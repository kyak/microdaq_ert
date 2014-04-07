/* mdaq_net.c -- Socket driver for MicroDAQ device
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT) 
//#define MDAQNET_SYSBIOS_MODE
#ifdef MDAQNET_SYSBIOS_MODE

#include <xdc/std.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>

#include <xdc/cfg/global.h>

#include <stdio.h>
#endif

#include <string.h>

#include "hardware.h"
#include "utils.h"

#include "mdaq_net.h"

#define MDAQNET_OPEN			(0x30)
#define MDAQNET_CLOSE			(0x31)
#define MDAQNET_RECV			(0x32)
#define MDAQNET_SEND			(0x33)
#define MDAQNET_SETOPT			(0x34)

#define MDAQNET_IRQ				(5)
#define MDAQNET_MEM_ADDR		(0x80010000)
#define MDAQNET_MEM_SIZE		(0x8000)

#define MDAQNET_RPC_MAX_ARGS	(10)
#define WAIT_FOREVER			(~0)
#define MDAQNET_BUF_SIZE		(0x8000)

#ifdef	MDAQNET_SYSBIOS_MODE
static Semaphore_Handle rpc_done_sem;
#endif

typedef union param_
{
	int8_t		i8;
	int16_t		i16;
	int32_t		i32;
	int64_t		i64;
}param_t;

typedef struct mdaq_net_rpc_
{
	volatile uint32_t	func;
	volatile int 		result;
	volatile int 		sem1;
	volatile int 		sem2;
	param_t		args[MDAQNET_RPC_MAX_ARGS];
}mdaq_net_rpc_t;

static volatile mdaq_net_rpc_t *rpc_node;
static volatile uint8_t *rpc_buffer;


#ifdef	MDAQNET_SYSBIOS_MODE
static void mdaq_net_isr( void )
{
	volatile uint32_t reg = raw_read32(SYS_CHIPSIG_CLR);
	reg |= 1 << 2;
	raw_write32(reg, SYS_CHIPSIG_CLR);
    Semaphore_post(rpc_done_sem);
}

static uint32_t ms_to_ticks( uint32_t ms )
{
	/* TODO: */
	return BIOS_WAIT_FOREVER;
}
#endif

static inline void mdaq_net_rpc_set_params(const mdaq_net_rpc_t *call)
{
	memcpy((void*)rpc_node, (void *)call, sizeof(mdaq_net_rpc_t));
}

static inline void mdaq_net_rpc_get_params(mdaq_net_rpc_t *call)
{
	memcpy((void *)call, (void*)rpc_node, sizeof(mdaq_net_rpc_t));
}

static int mdaq_net_rpc_exec( mdaq_net_rpc_t *call, uint32_t timeout )
{
	volatile uint32_t reg = raw_read32(SYS_CHIPSIG);

	if ( !rpc_node || !rpc_buffer )
		return -1;

	mdaq_net_rpc_set_params( call );

	reg |= 0x1;
	raw_write32(reg, SYS_CHIPSIG);

#ifndef	MDAQNET_SYSBIOS_MODE

	/* TODO: */ 
	volatile int d = 0;
	for (d = 0; d < 50000; d++);

	while( !call->sem1 )
		mdaq_net_rpc_get_params(call);

	return 0;
#else
	Bool result = Semaphore_pend(rpc_done_sem, timeout);

	if (result == TRUE)
	{
		mdaq_net_rpc_get_params(call);
		return 0;
	}
	return -1;
#endif

}


int mdaq_net_open(int port, int type, int protocol, int flags, int blocking)
{
	int result = -1;
	mdaq_net_rpc_t call;

	memset((void *)&call, 0x0, sizeof(mdaq_net_rpc_t));
	call.func 		 = MDAQNET_OPEN;
	call.args[0].i32 = port;
	call.args[1].i32 = type;
	call.args[2].i32 = protocol;
	call.args[3].i32 = flags;
	call.args[4].i32 = blocking;

	call.result = -1;

	result = mdaq_net_rpc_exec( &call, WAIT_FOREVER);
	return (result < 0) ? result : call.result;
}

int mdaq_net_close(int fd)
{
	mdaq_net_rpc_t call;

	memset((void *)&call, 0x0, sizeof(mdaq_net_rpc_t));
	call.func 		 = MDAQNET_CLOSE;
	call.args[0].i32 = fd;

	call.result = -1;

	mdaq_net_rpc_exec(&call, WAIT_FOREVER);
	return call.result;
}

int mdaq_net_send(int sockfd, const void *buf, size_t len, int flags)
{
	mdaq_net_rpc_t call;

	memset((void *)&call, 0x0, sizeof(mdaq_net_rpc_t));
	call.func 		 = MDAQNET_SEND;
	call.args[0].i32 = sockfd;
	call.args[2].i32 = flags;

	if (len > (MDAQNET_MEM_SIZE - sizeof(mdaq_net_rpc_t)) )
		len = (MDAQNET_MEM_SIZE - sizeof(mdaq_net_rpc_t));

	call.args[1].i32 = len;
	call.result = -1;

	memcpy((void *)rpc_buffer, (void *)buf, len);
	mdaq_net_rpc_exec( &call, WAIT_FOREVER);

	return call.result;
}

int mdaq_net_recv(int sockfd, void *buf, size_t len, int flags)
{
	mdaq_net_rpc_t call;

	memset((void *)&call, 0x0, sizeof(mdaq_net_rpc_t));
	call.func 		 = MDAQNET_RECV;
	call.args[0].i32 = sockfd;
	call.args[2].i32 = flags;

	if (len > (MDAQNET_MEM_SIZE - sizeof(mdaq_net_rpc_t)) )
		len = (MDAQNET_MEM_SIZE - sizeof(mdaq_net_rpc_t));

	call.args[1].i32 = len;
	call.result = -1;

	mdaq_net_rpc_exec( &call, WAIT_FOREVER );
	if ( call.result > 0 && call.result <= len )
		memcpy((void *)buf, (void *)rpc_buffer, call.result);

	return call.result;
}

int mdaq_net_init( void )
{
    rpc_node = (mdaq_net_rpc_t*)MDAQNET_MEM_ADDR;
    rpc_buffer = (uint8_t*)(MDAQNET_MEM_ADDR + sizeof(mdaq_net_rpc_t));

#ifdef MDAQNET_SYSBIOS_MODE
	Hwi_Handle hwi0;
	Hwi_Params hwiParams;

	Hwi_Params_init(&hwiParams);
	hwiParams.arg = MDAQNET_IRQ;

	hwi0 = Hwi_create(MDAQNET_IRQ, (ti_sysbios_hal_Hwi_FuncPtr)mdaq_net_isr,
			&hwiParams, NULL);
	if (hwi0 == NULL){
		return -1;
	}

	rpc_done_sem = Semaphore_create(0, NULL, NULL);
	if (rpc_done_sem == NULL ){
		return -1;
	}
#endif

    return 0;
}
#endif
