#ifndef _MDAQUART_H_
#define _MDAQUART_H_

void UARTConfig( unsigned char module, unsigned char baud_rate, unsigned char data_bits, unsigned char parity, unsigned char stop_bits, unsigned char flow_control);
void UARTSend( unsigned char module, unsigned char *data, unsigned int size );
void UARTRecv( unsigned char module, unsigned char *data, int *status, unsigned int size, unsigned char blocking, unsigned int timeout, unsigned int msg_header, unsigned char use_msg_header );

#endif /* _MDAQUART_H_ */ 

