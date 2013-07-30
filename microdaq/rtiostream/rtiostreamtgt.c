/* rtiostream.c -- rtiostream implemenation for MicroDAQ device
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */


//#define DEBUG_RTIOSTREAM

#include <stdint.h>

#include "rtiostream.h"
#include "mdaq_net.h"

#ifdef DEBUG_RTIOSTREAM
#include <stdio.h>
#endif


/* Initialize rtIOStream */
int rtIOStreamOpen(int argc, void *argv[])
{
	int fd;
	mdaq_net_init();

	fd = mdaq_net_open(4344, SOCK_STREAM, IPPROTO_TCP, 0, 1 /* blocking */ );
#ifdef DEBUG_RTIOSTREAM
	printf("rtIOStreamOpen: %d\n", fd);
#endif
	if (fd < 0)
		return RTIOSTREAM_ERROR;

    return fd;
}

/* Read data from rtIOStream */
int rtIOStreamRecv(
        int      streamID,  // A handle to the stream that was returned by a previous call to rtIOStreamOpen.
        void   * dst,       // A pointer to the start of the buffer where received data must be copied.
        size_t   size, 	    // Size of data to copy into the buffer. For byte-addressable architectures,
                            // size is measured in bytes. Some DSP architectures are not byte-addressable.
                            // In these cases, size is measured in number of WORDs, where sizeof(WORD) == 1.
        size_t * sizeRecvd) // The number of units of data received and copied into the buffer dst (zero if no data was copied).
{
	int result = 0;

    result = mdaq_net_recv(streamID, dst, size, MSG_DONTWAIT);
    if ( result >= 0)
    	*sizeRecvd = result;
    else
    	*sizeRecvd = 0;
#ifdef DEBUG_RTIOSTREAM
    printf("rtIOStreamRecv: size:%d result:%d\n", size, result);
#endif
    if(result == -EAGAIN || result >= 0)
    	return RTIOSTREAM_NO_ERROR;
    else
    	return RTIOSTREAM_ERROR;
}

/* Write data to rtIOStream */
int rtIOStreamSend(
        int          streamID,
        const void * src,
        size_t       size,
        size_t     * sizeSent)
{
	int result = 0;
	result = mdaq_net_send(streamID, src, size, 0);
#ifdef DEBUG_RTIOSTREAM
	printf("rtIOStreamSend: size:%d result:%d\n", size, result);
#endif
	if(result >=0){
		*sizeSent = result;
		return RTIOSTREAM_NO_ERROR;
	}
	result = 0;
	return RTIOSTREAM_ERROR;
}

/* Close rtIOStream */
int rtIOStreamClose(int streamID)
{
#ifdef DEBUG_RTIOSTREAM
	printf("rtIOStreamClose: fd:%d\n", streamID);
#endif
	return (mdaq_net_close(streamID) < 0) ? RTIOSTREAM_ERROR : RTIOSTREAM_NO_ERROR;
}


