//#define DEBUG

#ifdef _WIN32
#define RTIOSTREAMAPI __declspec( dllexport )
#endif

#include "rtiostream.h"
#include "MLink.h"
#include <string.h>

#ifdef DEBUG
#include "mex.h"
#endif

#ifdef _WIN32
#include <Windows.h>
#define SLEEP_SET_OBJ Sleep(7);
#else
#include <unistd.h>
#define SLEEP_SET_OBJ usleep(7000);
#endif

static volatile uint8_t in_stream[2054] = {0};
static volatile uint8_t out_stream[2054] = {0};
static uint32_t in_flag = 0;
static uint32_t out_flag = 0;
static volatile uint32_t in_stream_pos = 0;
static volatile uint32_t out_stream_pos = 0;
static uint8_t was_sending = 0;

/* Initialize rtIOStream */
RTIOSTREAMAPI int rtIOStreamOpen(int argc, void *argv[])
{
    int result, streamID, count = 0;
    char * ipaddr = "10.10.1.1";
    /* Initialize flags to avoid weird behaviour when this library is reused */
    in_flag = 0;
    out_flag = 0;
    in_stream_pos = 0;
    out_stream_pos = 0;
    was_sending = 0;

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

#ifdef DEBUG
    int i;
    printf("\n\nReceiving size: %d\n",size);
#endif

    *sizeRecvd=0U;

    /* One time set of actions when transitioning from send to receive.
     * These steps are done in order to actually send the buffer to target */
    if (was_sending == 1) {
        /* Since we are reading, it means that writing has finished */
        in_flag = 1;
        was_sending = 0;
        /* Send the buffer to the target. in_stream is assumed to be uint8s */
        result = mlink_set_obj(&streamID, "in_stream", &in_stream, in_stream_pos);
        if (result < 0)
            return RTIOSTREAM_ERROR;
        SLEEP_SET_OBJ
        /* Reset the position in send buffer */
        in_stream_pos = 0;
        /* Send the flag for the target indicating that there is something in input buffer */
        result = mlink_set_obj(&streamID, "in_flag", &in_flag, sizeof(in_flag));
        if (result < 0)
            return RTIOSTREAM_ERROR;
        SLEEP_SET_OBJ
    }

    /* Check if there is data in target's send buffer */
    result = mlink_get_obj(&streamID, "out_flag", &out_flag, sizeof(out_flag));
    if (result < 0)
        return RTIOSTREAM_ERROR;

    if (out_flag == 0) /* No data to receive */
        return RTIOSTREAM_NO_ERROR;

    /* Get the data from target.
     * TODO: possible to optimize: get only bytes from out_stream_pos to 
     * out_stream_pos+size */
    result = mlink_get_obj(&streamID, "out_stream", &out_stream, out_stream_pos+size);
    if (result < 0)
        return RTIOSTREAM_ERROR;

    /* Get the "size" number of bytes as requested by PIL protocol.
     * Additionally, if we are outside the buffer, keep reading the
     * last element. This should model buffer overflow. */
    while (*sizeRecvd < size) {
        if (out_stream_pos+*sizeRecvd > sizeof(out_stream)-1) {
            *ptr++ = out_stream[sizeof(out_stream)-1];
        } else {
            *ptr++ = out_stream[out_stream_pos+*sizeRecvd];
        }
        (*sizeRecvd)++;
    }
    /* Maintain the position in receive buffer */
    out_stream_pos += *sizeRecvd;

#ifdef DEBUG
    printf("Rcvd size: %d\n",*sizeRecvd);
    printf("out_stream_pos is: %d\n",out_stream_pos);
    printf("Rcvd data: ");
    for (i = out_stream_pos-*sizeRecvd; i<out_stream_pos; i++) {
        printf("%0x ",out_stream[i]);
    }
#endif

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

#ifdef DEBUG
    int i;
    printf("\n\nSending size: %d\n",size);
#endif

    *sizeSent=0U;

    /* We are here */
    was_sending = 1;
    /* Reset the position in receive buffer */
    out_stream_pos = 0;
    /* Reset the out_flag and send it to the target
     * We really need to do that so the host wouldn't
     * mistakenly read data again, even if it's not available */
    out_flag = 0;
    result = mlink_set_obj(&streamID, "out_flag", &out_flag, sizeof(out_flag));
    if (result < 0)
        return RTIOSTREAM_ERROR;
    SLEEP_SET_OBJ

    /* Check if the data has actually been read completely by target
     * If it hasn't, we can't send */
    result = mlink_get_obj(&streamID, "in_flag", &in_flag, sizeof(in_flag));
    if (result < 0)
        return RTIOSTREAM_ERROR;
    if (in_flag > 0)
        return RTIOSTREAM_NO_ERROR;

    /* Send the "size" number of bytes as requested by PIL protocol.
     * Additionally, if we are outside the buffer, keep writing the
     * last element. This should model buffer overflow. */
    while (*sizeSent < size) {
        if (in_stream_pos+*sizeSent > sizeof(in_stream)-1) {
            in_stream[sizeof(in_stream)-1] = *ptr++;
        } else {
            in_stream[in_stream_pos+*sizeSent] = *ptr++;
        }
        (*sizeSent)++;
    }
    /* Maintain the position in send buffer */
    in_stream_pos += *sizeSent;

#ifdef DEBUG
    printf("Sent size: %d\n",*sizeSent);
    printf("in_stream_pos is: %d\n",in_stream_pos);
    printf("Sent data: ");
    for (i = in_stream_pos-*sizeSent; i<in_stream_pos; i++) {
        printf("%0x ",in_stream[i]);
    }
#endif

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
