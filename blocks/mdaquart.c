#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include <string.h>
#include "mdaq_uart.h"
#endif

#define RX_BUF_SIZE     (512)
#define MSG_TIMEOUT     (-1)

#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
static mdaq_uart_config_t uart[3]; 
#endif 

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

void UARTSend( unsigned char module, unsigned char *data, unsigned int size )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    mdaq_uart_write(module, (void *)data, size); 
#endif
}


void UARTRecv( unsigned char module, unsigned char *data, int *status, unsigned int size, unsigned char blocking, unsigned int timeout, unsigned int msg_header, unsigned char use_msg_header )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)

    int data_idx = 0;

    static unsigned char rx_buffer[RX_BUF_SIZE + 4]; /* 4 bytes for header */
    static int rx_buf_idx = 0;
    static int msg_header_at = 0; 

    int result = mdaq_uart_read(module, rx_buffer + rx_buf_idx,
            size + ( sizeof(msg_header) - rx_buf_idx) , blocking ? timeout : 0);

    if ( use_msg_header )
    {
        if ( result > 0 ) 
        {
            if(rx_buf_idx && !msg_header_at)
            {
                if ( rx_buf_idx + result >= size )
                {
                    memcpy(data, rx_buffer, size);
                    *status = size;
                    rx_buf_idx = 0;
                }
                else
                {
                    rx_buf_idx += result;
                }
            }
            else
            {
                for ( data_idx = 0; data_idx < result; data_idx++ )
                {
                    if ( rx_buffer[data_idx + rx_buf_idx] == *(((unsigned char *)(&msg_header)) + msg_header_at) )
                        msg_header_at++;
                    else
                        msg_header_at = 0;

                    if (msg_header_at == sizeof(msg_header))
                    {
                        data_idx++;
                        if( size ==  rx_buf_idx + result - data_idx)
                        {
                            memcpy(data, rx_buffer + rx_buf_idx + data_idx,
                                    (result - data_idx) > RX_BUF_SIZE ? RX_BUF_SIZE : result - data_idx);

                            *status = size;
                            rx_buf_idx = 0;
                        }
                        else
                        {
                            memmove(rx_buffer, rx_buffer + rx_buf_idx + data_idx,
                                    (result - data_idx) > RX_BUF_SIZE ? RX_BUF_SIZE : result - data_idx);

                            rx_buf_idx = result - data_idx;
                            *status = MSG_TIMEOUT;
                        }

                        msg_header_at = 0;
                        break;
                    }
                }
                if ( data_idx == result && msg_header_at < sizeof(msg_header))
                    *status = -1;
            }
        }
        else
        {
            *status = result;
        }
    }
    else
    {
        if (blocking)
            *status = result; 
        else 
            *status = result > 0 ? result : 0; 
    }

#endif
}

