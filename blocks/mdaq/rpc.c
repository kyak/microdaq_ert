/* mdaq_rpc.c -- Simple RPC implementation for MicroDAQ
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

#include "hardware.h"
#include "utils.h"

#ifdef	MDAQNET_SYSBIOS_MODE
static Semaphore_Handle rpc_done_sem;
#endif

#endif

#include <stdint.h>
#include "rpc.h"

static volatile mdaq_rpc_t *rpc_node;
static volatile uint8_t *rpc_buffer;

#ifdef	MDAQRPC_SYSBIOS_MODE
static void mdaq_rpc_isr( void )
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


int mdaq_rpc_exec( mdaq_rpc_t *call, uint32_t timeout, void *data, uint32_t len, int read )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	volatile uint32_t reg = raw_read32(SYS_CHIPSIG);

	if ( !rpc_node || !rpc_buffer )
		return -1;

	if (len > (MDAQRPC_MEM_SIZE - sizeof(mdaq_rpc_t)) )
		len = (MDAQRPC_MEM_SIZE - sizeof(mdaq_rpc_t));

	/* TODO: handle larger data chunks */
	if (!read)
		memcpy((void *)rpc_buffer, (void *)data, len);

	memcpy((void*)rpc_node, (void *)call, sizeof(mdaq_rpc_t));

	reg |= 0x1;
	raw_write32(reg, SYS_CHIPSIG);

#ifndef	MDAQNET_SYSBIOS_MODE

	/* TODO: without delay test fails !!! */
	volatile int d = 0;
	for (d = 0; d < 50000; d++);

	while( !call->sem1 )
		memcpy((void *)call, (void*)rpc_node, sizeof(mdaq_rpc_t));

	if (read && call->result > 0 && call->result <= len )
		memcpy((void *)data, (void *)rpc_buffer, call->result);

	return 0;

#else
	Bool result = Semaphore_pend(rpc_done_sem, timeout);

	if (result == TRUE)
	{
		mdaq_rpc_get_params(call);
		return 0;
	}
	return -1;
#endif
#endif 

}

void mdaq_rpc_init( void )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    rpc_node = (mdaq_rpc_t*)MDAQRPC_MEM_ADDR;
    rpc_buffer = (uint8_t*)(MDAQRPC_MEM_ADDR + sizeof(mdaq_rpc_t));

#ifdef MDAQNET_SYSBIOS_MODE
	Hwi_Handle hwi0;
	Hwi_Params hwiParams;

	Hwi_Params_init(&hwiParams);
	hwiParams.arg = MDAQRPC_IRQ;

	hwi0 = Hwi_create(MDAQRPC_IRQ, (ti_sysbios_hal_Hwi_FuncPtr)mdaq_net_isr,
			&hwiParams, NULL);
	if (hwi0 == NULL){
		return -1;
	}

	rpc_done_sem = Semaphore_create(0, NULL, NULL);
	if (rpc_done_sem == NULL ){
		return -1;
	}
#endif
#endif 
}
