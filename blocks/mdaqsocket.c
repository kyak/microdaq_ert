#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)

#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "mdaq_socket.h"
#endif


void SocketOpen( char *ip, int port, unsigned char blocking, int timeout, unsigned char type)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	mdaq_socket_open( ip, port, blocking, timeout, type); 
#endif
}

void SocketSend( char *ip, int port, unsigned char *data, unsigned int size)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	mdaq_socket_send( ip, port, data, size);
#endif
}

void SocketRecv( char *ip, int port, unsigned char *data, int *status, unsigned int size, unsigned char blocking)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	mdaq_socket_recv( ip, port, data, status, size, blocking);
#endif
}

void SocketClose( char *ip, int port )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	mdaq_socket_close( ip, port );
#endif
}

