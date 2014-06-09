/* mdaq_rpc.h -- Simple RPC implementation for MicroDAQ
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */


#ifndef MDAQ_RPC_H_
#define MDAQ_RPC_H_

#define MDAQRPC_IRQ				(5)
#define MDAQRPC_MEM_ADDR		(0x80010000)
#define MDAQRPC_MEM_SIZE		(0x8000)

#define MDAQRPC_RPC_MAX_ARGS	(10)
#define WAIT_FOREVER			(~0)
#define MDAQRPC_BUF_SIZE		(0x8000)

/* PRC procedure call numbers */
#define MDAQNET_OPEN			(0x30)
#define MDAQNET_CLOSE			(0x31)
#define MDAQNET_RECV			(0x32)
#define MDAQNET_SEND			(0x33)
#define MDAQNET_SETOPT			(0x34)

#define MDAQUART_OPEN           (0x40)
#define MDAQUART_WRITE          (0x41)
#define MDAQUART_READ           (0x42)
#define MDAQUART_SETSPEED       (0x43)
#define MDAQUART_CLOSE          (0x44)
#define MDAQUART_SETMODE        (0x45)

#define MDAQFILE_OPEN			(0x50)
#define MDAQFILE_WRITE			(0x51)
#define MDAQFILE_READ			(0x52)
#define MDAQFILE_FLUSH			(0x53)
#define MDAQFILE_CLOSE			(0x54)


typedef union param_
{
	int8_t		i8;
	int16_t		i16;
	int32_t		i32;
	int64_t		i64;
}param_t;

typedef struct mdaq_rpc_
{
	volatile uint32_t	func;
	volatile int 		result;
	volatile int 		sem1;
	volatile int 		sem2;
	param_t				args[MDAQRPC_RPC_MAX_ARGS];
}mdaq_rpc_t;

int mdaq_rpc_exec( mdaq_rpc_t *call, uint32_t timeout, void *data, uint32_t len, int read );
void mdaq_rpc_init( void );

#endif /* MDAQ_RPC_H_ */
