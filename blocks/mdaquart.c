#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include "mdaq_uart.h"
#include "mdaquart.h"
#endif

#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
static mdaq_uart_config_t uart[3]; 
#endif 

/* TODO: remove this function */ 
static int recv_data_size; 
static int send_data_size; 
static int blocking_operation; 
static int uart_timeout; 

void UARTConfig( unsigned char module, unsigned char baud_rate, unsigned char data_bits, unsigned char parity, unsigned char stop_bits, unsigned char flow_control)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	int result; 

	if ( module > 2 )
		return ; 

	mdaq_uart_init(); 

	switch(baud_rate)
	{
		case 1: 
			uart[module].baud_rate = B2400; 
			break;
		case 2: 
			uart[module].baud_rate = B4800; 
			break;
		case 3: 
			uart[module].baud_rate = B9600; 
			break;
		case 4: 
			uart[module].baud_rate = B19200; 
			break;
		case 5: 
			uart[module].baud_rate = B38400; 
			break;
		case 6: 
			uart[module].baud_rate = B57600; 
			break;
		case 7: 
			uart[module].baud_rate = B115200; 
			break;
		default: 
			uart[module].baud_rate = B115200; 
	}

	uart[module].data_bits = data_bits; 
	uart[module].parity = parity; 
	uart[module].stop_bits = stop_bits; 
	uart[module].flow_control = flow_control; 

	result = mdaq_uart_open(module); 	
	if ( result < 0 ) 
		return; 

	result = mdaq_uart_config(module, &(uart[module])); 	
	if ( result < 0 ) 
		return; 
#endif
}
/* TODO: remove this function */ 
void UARTSendInit( unsigned char module, unsigned short data_size )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	send_data_size = data_size;  
#endif
}

void UARTSend( unsigned char module, unsigned char *data )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	mdaq_uart_write(module, (void *)data, send_data_size); 
#endif
}

/* TODO: remove this function */ 
void UARTRecvInit( unsigned char module, unsigned short data_size, unsigned char blocking, unsigned short timeout )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	recv_data_size = data_size; 
	blocking_operation = blocking; 
	uart_timeout = timeout; 
#endif
}

void UARTRecv( unsigned char module, unsigned char *data, int *status )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)

	int result = mdaq_uart_read(module, (void *)data, recv_data_size, blocking_operation ? uart_timeout : 0); 
	if (blocking_operation)
			*status = result; 
	else 
			*status = result > 0 ? result : 0; 
#endif
}

