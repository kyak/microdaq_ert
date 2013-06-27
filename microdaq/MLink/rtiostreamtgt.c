#include "rtiostream.h"
#include <stdint.h>

static volatile uint8_t in_stream[300] = {0};
static volatile uint8_t out_stream[300] = {0};
static volatile uint8_t in_flag = 0;
static volatile uint8_t out_flag = 0;
static volatile uint32_t in_stream_pos = 0;
static volatile uint32_t out_stream_pos = 0;
static uint8_t was_sending = 0;

/* Initialize rtIOStream */
int rtIOStreamOpen(int argc, void *argv[])
{
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
    
    *sizeRecvd=0U;
    
    if (was_sending == 1) {
        out_stream_pos = 0;
        out_flag = 1;
        was_sending = 0;
    }
    
    if (in_flag == 0) //No data to receive
        return RTIOSTREAM_NO_ERROR;

    while (*sizeRecvd < size) {
        *ptr++ = in_stream[in_stream_pos+*sizeRecvd];
        (*sizeRecvd)++;
    }
    in_stream_pos += *sizeRecvd;

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

    *sizeSent=0U;
    
    was_sending = 1;
    in_stream_pos = 0;
    in_flag = 0;

    while (*sizeSent < size) {
        out_stream[out_stream_pos+*sizeSent] = *ptr++;
        (*sizeSent)++;
    }
    out_stream_pos += *sizeSent;

    return RTIOSTREAM_NO_ERROR;
}

/* Close rtIOStream */
int rtIOStreamClose(int streamID)
{
    return RTIOSTREAM_NO_ERROR;
}
