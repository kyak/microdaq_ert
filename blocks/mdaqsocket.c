#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)

#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "mdaq_net.h"
#include "mdaqsocket.h"
#endif

#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)

#define MAX_CON 	(16)
struct connection_desc
{
	uint32_t addr;
	uint32_t port;
};

static struct connection_desc con[16];

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

static int get_conn_fd(uint32_t addr, int port)
{
	int i;
	for( i = 0; i < MAX_CON; i++ )
		if( con[i].addr == addr && con[i].port == port)
			return i;

	return -1;
}
#endif 

void SocketOpen( char *ip, int port, unsigned char blocking, int timeout, unsigned char type)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	static int first_time = 1;
	uint32_t addr  = inet_addr(ip);

	if (first_time)
	{
		mdaq_net_init();
		memset((void *)&con, 0x0, sizeof(con));
		first_time = 0;
	}

	if (get_conn_fd(addr, port) == -1)
	{
		int fd = mdaq_net_open2(ip, port,
				type == TCP_SOCKET ? SOCK_STREAM : SOCK_DGRAM,
				type == TCP_SOCKET ? IPPROTO_TCP : IPPROTO_UDP,
				0,
				timeout);
		if( fd >= MAX_CON)
			return;

		con[fd].addr = addr;
		con[fd].port = port;
	}
	else
	{
		/* In use */
	}

#endif
}

void SocketSend( char *ip, int port, unsigned char *data, unsigned int size)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	int fd = get_conn_fd(inet_addr(ip), port);
	if (fd  > -1 )
		mdaq_net_send2(fd, (void *)data, size, 0 );	  
#endif
}

void SocketRecv( char *ip, int port, unsigned char *data, int *status, unsigned int size, unsigned char blocking)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	int fd = get_conn_fd(inet_addr(ip), port);
	if ( fd > -1 )
		*status = mdaq_net_recv2(fd, (void *)data, size, blocking ? 0 : MSG_DONTWAIT );	  
#endif
}

void SocketClose( char *ip, int port )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	int fd = get_conn_fd(inet_addr(ip), port);
	if ( fd > -1 )
		mdaq_net_close2(fd); 
#endif
}

