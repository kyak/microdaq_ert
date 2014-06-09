/* mdaq_file.c -- File access driver for MicroDAQ device
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

#include "mdaq_file.h"

int mdaq_file_open(const char *name, int flags)
{
	int result = -1;
	mdaq_rpc_t call;

	memset((void *)&call, 0x0, sizeof(mdaq_rpc_t));
	call.func 		 = MDAQFILE_OPEN;
	call.args[0].i32 = flags;

	call.result = -1;

	result = mdaq_rpc_exec(1, &call, WAIT_FOREVER, (void *)name, strlen(name) + 1, 0);
	return (result < 0) ? result : call.result;
}

int mdaq_file_close(int fd)
{
	mdaq_rpc_t call;

	memset((void *)&call, 0x0, sizeof(mdaq_rpc_t));
	call.func 		 = MDAQFILE_CLOSE;
	call.args[0].i32 = fd;

	call.result = -1;

	mdaq_rpc_exec(1, &call, WAIT_FOREVER, NULL, 0, 0);
	return call.result;
}

/* TODO: */ 
int mdaq_file_lseek(int fd, long offset, int whence)
{
	return 0; 
}

int mdaq_file_write(int fd, const void *buf, size_t len)
{
	mdaq_rpc_t call;

	memset((void *)&call, 0x0, sizeof(mdaq_rpc_t));
	call.func 		 = MDAQFILE_WRITE;
	call.args[0].i32 = fd;
	call.args[1].i32 = 0; 
	call.args[2].i32 = len;

	call.result = -1;

	mdaq_rpc_exec(1, &call, WAIT_FOREVER, (void *)buf, len, 0);

	return call.result;
}

int mdaq_file_read(int fd, void *buf, size_t len)
{
	mdaq_rpc_t call;

	memset((void *)&call, 0x0, sizeof(mdaq_rpc_t));
	call.func 		 = MDAQFILE_READ;
	call.args[0].i32 = fd;
	call.args[1].i32 = 0; 
	call.args[2].i32 = len;

	call.result = -1;

	mdaq_rpc_exec(1, &call, WAIT_FOREVER, buf, len, 1);

	return call.result;
}

int mdaq_file_flush(int fd)
{
	mdaq_rpc_t call;

	memset((void *)&call, 0x0, sizeof(mdaq_rpc_t));
	call.func 		 = MDAQFILE_FLUSH;
	call.args[0].i32 = fd;

	call.result = -1;

	mdaq_rpc_exec(1, &call, WAIT_FOREVER, NULL, 0, 0);
	return call.result;
}

int mdaq_file_init( void )
{
	mdaq_rpc_init();

	return 0;
}
#endif

