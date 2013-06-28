#ifdef _WIN32
#define RTIOSTREAMAPI __declspec( dllexport )
#endif

#include "rtiostream.h"
#include "MLink.h"
#include <string.h>
#include "mex.h"

#ifdef _WIN32
#include <Windows.h>
#define SLEEP_SET_OBJ Sleep(10);
#else
#include <unistd.h>
#define SLEEP_SET_OBJ usleep(10000);
#endif

static volatile uint8_t in_stream[300] = {0};
static volatile uint8_t out_stream[300] = {0};
static uint8_t in_flag = 0;
static uint8_t out_flag = 0;
static volatile uint32_t in_stream_pos = 0;
static volatile uint32_t out_stream_pos = 0;
static uint8_t was_sending = 0;

/* Initialize rtIOStream */
RTIOSTREAMAPI int rtIOStreamOpen(int argc, void *argv[])
{
    int result, streamID, count = 0;
    char * ipaddr = "10.10.1.1";
    /* Parse arguments */
    while(count < argc) {
        const char *option = (char *)argv[count];
        count++;
        if (option != NULL) {
            if ((strcmp(option, "-ipaddr") == 0) && (count != argc)) {
                ipaddr = (char *)argv[count];
                count++;
                argv[count-2] = NULL;
                argv[count-1] = NULL;
            }
        }
    }
    result = mlink_connect(ipaddr, 4343, &streamID);
    if (result < 0) {
      return RTIOSTREAM_ERROR;
    } else {
      return streamID;
    }
}

/* Read data from rtIOStream */
RTIOSTREAMAPI int rtIOStreamRecv(
        int      streamID,  // A handle to the stream that was returned by a previous call to rtIOStreamOpen.
        void   * dst,       // A pointer to the start of the buffer where received data must be copied.
        size_t   size, 	    // Size of data to copy into the buffer. For byte-addressable architectures,
                            // size is measured in bytes. Some DSP architectures are not byte-addressable.
                            // In these cases, size is measured in number of WORDs, where sizeof(WORD) == 1.
        size_t * sizeRecvd) // The number of units of data received and copied into the buffer dst (zero if no data was copied).
{
    uint8_t *ptr = (uint8_t *)dst;
    uint8_t result = 0;
    int i;
       
    *sizeRecvd=0U;
    
    if (was_sending == 1) { //we haven't send the buffer to target yet
        in_stream_pos = 0; //since we are reading, it means that writing has finished
        in_flag = 1;
        was_sending = 0;
        result = mlink_set_obj(&streamID, "in_stream", &in_stream, sizeof(in_stream));
        if (result < 0)
           return RTIOSTREAM_ERROR;
        SLEEP_SET_OBJ
        //send the flag to target
        result = mlink_set_obj(&streamID, "in_flag", &in_flag, sizeof(in_flag));
        if (result < 0)
            return RTIOSTREAM_ERROR;
        SLEEP_SET_OBJ
    }
    
    /* Check if the data is ready from target; target's out_flag is set */
    result = mlink_get_obj(&streamID, "out_flag", &out_flag, sizeof(out_flag));
    if (result < 0)
        return RTIOSTREAM_ERROR;
    
    if (out_flag == 0) /* No data to receive */
        return RTIOSTREAM_NO_ERROR;
    
    /* Get the data from target */
    /* TODO: possible to optimize: get only bytes from out_stream_pos to 
     * out_stream_pos+size */
    result = mlink_get_obj(&streamID, "out_stream", &out_stream, sizeof(out_stream));
    if (result < 0)
        return RTIOSTREAM_ERROR;
    
    while (*sizeRecvd < size) {
        *ptr++ = out_stream[out_stream_pos+*sizeRecvd];
        (*sizeRecvd)++;
    }
    out_stream_pos += *sizeRecvd;

    //printf("\nRcvd size: %d\n",size);
//     printf("\nRcvd data: ");
//     for (i = out_stream_pos-*sizeRecvd; i<out_stream_pos; i++) {
//         printf("%0x ",out_stream[i]);
//     }
    return RTIOSTREAM_NO_ERROR;
}

/* Write data to rtIOStream */
RTIOSTREAMAPI int rtIOStreamSend(
        int          streamID,
        const void * src,
        size_t       size,
        size_t     * sizeSent)
{
    uint8_t *ptr = (uint8_t *)src;
    uint8_t result = 0;
    int i;
    
    *sizeSent=0U;
    
    was_sending = 1;
    out_stream_pos = 0;
    out_flag = 0;
    result = mlink_set_obj(&streamID, "out_flag", &out_flag, sizeof(out_flag));
    if (result < 0)
        return RTIOSTREAM_ERROR;
    SLEEP_SET_OBJ
    
    while (*sizeSent < size) {
        in_stream[in_stream_pos+*sizeSent] = *ptr++;
        (*sizeSent)++;
    }
    in_stream_pos += *sizeSent;

    //printf("\nSent size: %d\n",size);
//     printf("\nSent data: ");
//     for (i = in_stream_pos-*sizeSent; i<in_stream_pos; i++) {
//         printf("%0x ",in_stream[i]);
//     }

    return RTIOSTREAM_NO_ERROR;
}

/* Close rtIOStream */
RTIOSTREAMAPI int rtIOStreamClose(int streamID)
{
    //int result;
    //Do we need to stop DSP?
    //result = mlink_dsp_stop(&streamID);
    mlink_disconnect(streamID);
    return RTIOSTREAM_NO_ERROR;
}
