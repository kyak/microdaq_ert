//#define DEBUG

#include "rtiostream.h"
#include <stdint.h>

#ifdef DEBUG
#include <stdio.h>
#endif

static volatile uint8_t in_stream[2054] = {0};
static volatile uint8_t out_stream[2054] = {0};
static volatile uint32_t in_flag = 0;
static volatile uint32_t out_flag = 0;
static volatile uint32_t in_stream_pos = 0;
static volatile uint32_t out_stream_pos = 0;
static uint8_t was_sending = 0;

/* Initialize rtIOStream */
int rtIOStreamOpen(int argc, void *argv[])
{
    /* Initialize flags here just in case */
    in_flag = 0;
    out_flag = 0;
    in_stream_pos = 0;
    out_stream_pos = 0;
    was_sending = 0;

    return RTIOSTREAM_NO_ERROR;
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
    uint8_t *ptr = (uint8_t *)dst;

#ifdef DEBUG
    int i;
    printf("\n\nReceiving size: %d\n",size);
#endif

    *sizeRecvd=0U;

    /* One time set of actions when transitioning from send to receive. */
    if (was_sending == 1) {
        was_sending = 0;
        /* Reset the position in send buffer */
        out_stream_pos = 0;
        /* Since we are reading, it means that writing has finished */
        out_flag = 1;
    }

    if (in_flag == 0) /* No data to receive */
        return RTIOSTREAM_NO_ERROR;

    /* Get the "size" number of bytes as requested by PIL protocol.
     * Additionally, if we are outside the buffer, keep reading the
     * last element. This should model buffer overflow. */
    while (*sizeRecvd < size) {
    	if (in_stream_pos+*sizeRecvd > sizeof(in_stream)-1) {
    		*ptr++ = in_stream[sizeof(in_stream)-1];
    	} else {
    		*ptr++ = in_stream[in_stream_pos+*sizeRecvd];
    	}
        (*sizeRecvd)++;
    }
    /* Maintain the position in receive buffer */
    in_stream_pos += *sizeRecvd;

#ifdef DEBUG
    printf("Rcvd size: %d\n",*sizeRecvd);
    printf("in_stream_pos is: %d\n",in_stream_pos);
    printf("Rcvd data: ");
    for (i = in_stream_pos-*sizeRecvd; i<in_stream_pos; i++) {
        printf("%0x ",in_stream[i]);
    }
#endif

    return RTIOSTREAM_NO_ERROR;
}

/* Write data to rtIOStream */
int rtIOStreamSend(
        int          streamID,
        const void * src,
        size_t       size,
        size_t     * sizeSent)
{
    uint8_t *ptr = (uint8_t *)src;

#ifdef DEBUG
    int i;
    printf("\n\nSending size: %d\n",size);
#endif

    *sizeSent=0U;

    /* We are here */
    was_sending = 1;
    /* Reset the position in receive buffer */
    in_stream_pos = 0;
    in_flag = 0;

    /* Send the "size" number of bytes as requested by PIL protocol.
     * Additionally, if we are outside the buffer, keep writing the
     * last element. This should model buffer overflow. */
    while (*sizeSent < size) {
        if (out_stream_pos+*sizeSent > sizeof(out_stream)-1) {
        	out_stream[sizeof(out_stream)-1] = *ptr++;
        } else {
        	out_stream[out_stream_pos+*sizeSent] = *ptr++;
        }
        (*sizeSent)++;
    }
    /* Maintain the position in send buffer */
    out_stream_pos += *sizeSent;

#ifdef DEBUG
    printf("Sent size: %d\n",*sizeSent);
    printf("out_stream_pos is: %d\n",out_stream_pos);
    printf("Sent data: ");
    for (i = out_stream_pos-*sizeSent; i<out_stream_pos; i++) {
        printf("%0x ",out_stream[i]);
    }
#endif

    return RTIOSTREAM_NO_ERROR;
}

/* Close rtIOStream */
int rtIOStreamClose(int streamID)
{
    return RTIOSTREAM_NO_ERROR;
}
