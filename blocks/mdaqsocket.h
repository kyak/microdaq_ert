#ifndef _MDAQSOCKET_H_
#define _MDAQSOCKET_H_

/* socket type parameter */ 
#define TCP_SOCKET 	(0)
#define UDP_SOCKET	(1)

/* Function connects to remote host via TCP or UDP depending on type parameter */ 
void SocketOpen( char *ip, int port, unsigned char blocking, int timeout, unsigned char type);
void SocketSend( char *ip, int port, unsigned char *data, unsigned int size);
void SocketRecv( char *ip, int port, unsigned char *data, int *status, unsigned int size, unsigned char blocking );
void SocketClose( char *ip, int port );

#endif /* _MDAQSOCKET_H_ */ 

