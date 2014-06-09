/* mdaq_net.c -- Socket driver for MicroDAQ device
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT) 


#include <string.h>

#include "hardware.h"
#include "utils.h"
#include "rpc.h"

#include "mdaq_net.h"


int mdaq_net_open(int port, int type, int protocol, int flags, int blocking)
{
	int result = -1;
	mdaq_rpc_t call;

	memset((void *)&call, 0x0, sizeof(mdaq_rpc_t));
	call.func 		 = MDAQNET_OPEN;
	call.args[0].i32 = port;
	call.args[1].i32 = type;
	call.args[2].i32 = protocol;
	call.args[3].i32 = flags;
	call.args[4].i32 = blocking;

	call.result = -1;

	result = mdaq_rpc_exec(0, &call, WAIT_FOREVER, NULL, 0, 0);
	return (result < 0) ? result : call.result;
}

int mdaq_net_close(int fd)
{
	mdaq_rpc_t call;

	memset((void *)&call, 0x0, sizeof(mdaq_rpc_t));
	call.func 		 = MDAQNET_CLOSE;
	call.args[0].i32 = fd;

	call.result = -1;

	mdaq_rpc_exec(0, &call, WAIT_FOREVER, NULL, 0, 0);
	return call.result;
}

int mdaq_net_send(int sockfd, const void *buf, size_t len, int flags)
{
	mdaq_rpc_t call;

	memset((void *)&call, 0x0, sizeof(mdaq_rpc_t));
	call.func 		 = MDAQNET_SEND;
	call.args[0].i32 = sockfd;
	call.args[2].i32 = flags;
	call.args[1].i32 = len;

	call.result = -1;

	mdaq_rpc_exec(0, &call, WAIT_FOREVER, (void *)buf, len, 0);

	return call.result;
}

int mdaq_net_recv(int sockfd, void *buf, size_t len, int flags)
{
	mdaq_rpc_t call;

	memset((void *)&call, 0x0, sizeof(mdaq_rpc_t));
	call.func 		 = MDAQNET_RECV;
	call.args[0].i32 = sockfd;
	call.args[2].i32 = flags;

	call.args[1].i32 = len;
	call.result = -1;

	mdaq_rpc_exec(0, &call, WAIT_FOREVER, buf, len, 1);

	return call.result;
}

int mdaq_net_init( void )
{
	mdaq_rpc_init();

	return 0;
}
#endif
