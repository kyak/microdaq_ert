#ifndef _MDAQUART_H_
#define _MDAQUART_H_

void UARTConfig( unsigned char module, unsigned char baud_rate, unsigned char data_bits, unsigned char parity, unsigned char stop_bits, unsigned char flow_control);
void UARTSendInit( unsigned char module, unsigned short data_size );
void UARTSend( unsigned char module, unsigned char *data );
void UARTRecvInit( unsigned char module, unsigned short data_size, unsigned char blocking, unsigned short timeout );
void UARTRecv( unsigned char module, unsigned char *data, int *status );

#endif /* _MDAQUART_H_ */ 

