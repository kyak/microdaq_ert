/* mdaq_net.c -- Socket driver for MicroDAQ device
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT) 

#include <stdio.h>
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

static uint32_t inet_addr(const char *ip_addr)
{
	int a, b, c, d;
	char addr[4];

	sscanf(ip_addr, "%d.%d.%d.%d", &a, &b, &c, &d);
	addr[0] = a;
	addr[1] = b;
	addr[2] = c;
	addr[3] = d;

	return *(uint32_t*)addr;
}

/* TODO: one common API */
int mdaq_net_open2(const char *ip_addr, int port, int type, int protocol, int flags, int timeout)
{
	int result = -1;
	mdaq_rpc_t call;

	memset((void *)&call, 0x0, sizeof(mdaq_rpc_t));
	call.func 		 = MDAQNET_OPEN;
	call.args[0].i32 = port;
	call.args[1].i32 = type;
	call.args[2].i32 = protocol;
	call.args[3].i32 = flags;
	call.args[4].i32 = timeout;
	call.args[5].i32 = inet_addr(ip_addr);

	call.result = -1;

	result = mdaq_rpc_exec(1, &call, WAIT_FOREVER, NULL, 0, 0);
	return (result < 0) ? result : call.result;
}

/* TODO: one common API */
int mdaq_net_close2(int fd)
{
	mdaq_rpc_t call;

	memset((void *)&call, 0x0, sizeof(mdaq_rpc_t));
	call.func 		 = MDAQNET_CLOSE;
	call.args[0].i32 = fd;

	call.result = -1;

	mdaq_rpc_exec(1, &call, WAIT_FOREVER, NULL, 0, 0);
	return call.result;
}

/* TODO: one common API */
int mdaq_net_send2(int sockfd, const void *buf, size_t len, int flags)
{
	mdaq_rpc_t call;

	memset((void *)&call, 0x0, sizeof(mdaq_rpc_t));
	call.func 		 = MDAQNET_SEND;
	call.args[0].i32 = sockfd;
	call.args[2].i32 = flags;
	call.args[1].i32 = len;

	call.result = -1;

	mdaq_rpc_exec(1, &call, WAIT_FOREVER, (void *)buf, len, 0);

	return call.result;
}

/* TODO: one common API */
int mdaq_net_recv2(int sockfd, void *buf, size_t len, int flags)
{
	mdaq_rpc_t call;

	memset((void *)&call, 0x0, sizeof(mdaq_rpc_t));
	call.func 		 = MDAQNET_RECV;
	call.args[0].i32 = sockfd;
	call.args[1].i32 = len;
	call.args[2].i32 = flags;

	call.result = -1;

	mdaq_rpc_exec(1, &call, WAIT_FOREVER, buf, len, 1);

	return call.result;
}

int mdaq_net_init( void )
{
	mdaq_rpc_init();

	return 0;
}
#endif
