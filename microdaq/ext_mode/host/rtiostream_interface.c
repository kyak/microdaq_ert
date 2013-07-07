/* This file was copied from matlabroot\rtw\ext_mode\common\rtiostream_interface.c
 * as shipped with MATLAB R2013a and modified for custom External mode transport layer.
 * Look for a keyword "MIPE" to locate changes that were made */

/* <MIPE> */
#define ARGC_MAX 3 /* -ipaddr */
#define ARGV_INIT {NULL, NULL, NULL}
/* </MIPE> */

/*
 * Copyright 1994-2012 The MathWorks, Inc.
 *
 * File: rtiostream_interface.c     
 *
 * Abstract: Provide a host-side communications driver interface for Simulink
 * external mode.
 */


/***************** TRANSPORT-INDEPENDENT INCLUDES *****************************/

#include <ctype.h>
#include <string.h>

#include "version.h" /* MIN */
#include "mex.h"
#include "extsim.h"
#include "extutil.h"
#include "rtiostream.h"


#ifdef _WIN32
/* WINDOWS */
#if defined(_MSC_VER)
/* temporarily disable warning triggered by windows.h */
#pragma warning(push)
#pragma warning(disable: 4255)
#endif /* defined(_MSC_VER) */
#include <windows.h> /* for Sleep() */
#if defined(_MSC_VER)
/* restore warning */
#pragma warning(pop)
#endif /* defined(_MSC_VER) */
#else
#include <time.h> /* for nanosleep(), struct timespec */
#endif /* #ifdef _WIN32 */


typedef struct UserData_tag {
    RtIOStreamData rtiostreamData;
} UserData;

/* Function: SleepMilliseconds =========================================================
 * Abstract:
 *    Sleep for specified number of milliseconds. 
 *
 */
PRIVATE void SleepMilliseconds(const int t_msecs)
{
#if defined (_WIN32)

    Sleep( (DWORD)(t_msecs) );

#else

    struct timespec clkSleep;
    const int t_secs = t_msecs/1000;
    const int t_nsecs = (t_msecs - 1000 * t_secs) * 1e6; /*lint !e790 loss of precision double to int */
    
    clkSleep.tv_sec  = (time_t) t_secs;
    clkSleep.tv_nsec = (long)   t_nsecs;
    
    nanosleep( &clkSleep, NULL ); /*lint !e534 ignoring return value */

#endif
}


/* Function: ExtOpenConnection ===========================================================
 * Abstract:
 */
PUBLIC void ExtOpenConnection(ExternalSim *ES)
{
    UserData * const userData = (UserData *)esGetUserData(ES);

    /* rtIOStreamOpen has already been called from ExtProcessArgs */


    /* Initialize number of pending (cached) units of data */
    userData->rtiostreamData.numPending = 0;
    userData->rtiostreamData.startIdxPending = 0;

}

        



/* Function: ExtProcessArgs ===========================================================
 * Abstract:
 */
PUBLIC void ExtProcessArgs(
    ExternalSim   *ES,
    int           nrhs,
    const mxArray *prhs[])
{
    int argc = 0;
    const char * argv[ARGC_MAX] = ARGV_INIT;
    UserData  * const userData = (UserData *)esGetUserData(ES);
    int errorOccurred = 0;

    errorOccurred = ExtUtilCreateRtIOStreamArgs(ES, 
          nrhs, 
          prhs, 
          &argc, 
          argv);

    if (errorOccurred) {
       return;
    } 

    assert(argc <= ARGC_MAX);

    {
        /* Load the rtIOStream shared library */
        int error;
        error = ExtUtilLoadSharedLib(&userData->rtiostreamData);
        if (error != RTIOSTREAM_NO_ERROR) {

            /* Error out immediately */
            mexErrMsgIdAndTxt("rtiostream_interface:ExtProcessArgs:"
                              "LoadSharedLibFailure",
                              "Error loading rtIOStream shared library; "
                              "see command window for details.");

        } else {

            /* Call rtIOStreamOpen */
            userData->rtiostreamData.streamID = ( *(userData->rtiostreamData.libH.openFn) ) (argc, (void *)argv);
            if (userData->rtiostreamData.streamID == RTIOSTREAM_ERROR) {
                const char msg[] = 
                    "An error occurred attempting to open an rtIOStream. More detail "
                    "may be reported in the MATLAB command window\n";
                esSetError(ES, msg);
            }
        }
    }
}

/* Function: ExtUserDataCreate =================================================
 * Abstract:
 *  Create the user data.
 */
PUBLIC UserData *ExtUserDataCreate(void)
{
    UserData *ud = (UserData *)calloc(1UL, sizeof(UserData));
    return(ud);
} /* end ExtUserDataCreate */


/* Function: ExtUserDataDestroy ================================================
 * Abstract:
 *  Destroy the user data.
 */
PUBLIC void ExtUserDataDestroy(UserData *userData)
{
    if (userData != NULL) {
        free(userData);
    }
} /* end ExtUserDataDestroy */


/* Function: ExtGetTargetPkt ===================================================
 * Abstract:
 *  Attempts to get the specified number of bytes from the comm line.  The
 *  number of bytes read is returned via the 'nBytesGot' parameter.
 *  EXT_NO_ERROR is returned on success, EXT_ERROR is returned on failure.
 *
 * NOTES:
 *  o it is not an error for 'nBytesGot' to be returned as 0
 *  o it is o.k. for this function to block if no data is available (e.g.,
 *    a recv call on a blocking socket)
 */
PUBLIC boolean_T ExtGetTargetPkt(
    const ExternalSim *ES,
    const int         totalNBytesToGet,
    int               *nBytesGot, /* out */
    char              *dst)       /* out */
{
    int retVal;
    boolean_T error;
    size_t sizeRecvd;
    size_t nBytesToGet = (size_t) totalNBytesToGet;
    size_t numFromCache = 0;
    UserData  *userData = (UserData *)esGetUserData(ES);

    if (userData->rtiostreamData.numPending > 0) {

        numFromCache = MIN((size_t)nBytesToGet, (size_t)userData->rtiostreamData.numPending);

        memcpy(dst, &(userData->rtiostreamData.pendingRecvdData[userData->rtiostreamData.startIdxPending]), numFromCache);

        userData->rtiostreamData.numPending -= (int)numFromCache;
        userData->rtiostreamData.startIdxPending += numFromCache;

        dst += numFromCache;
        nBytesToGet -= numFromCache;

    }

    /* Call rtIOStreamRecv */
    retVal = ( *(userData->rtiostreamData.libH.recvFn) ) ((const int) userData->rtiostreamData.streamID,
                            dst,
                            (size_t) nBytesToGet,
                            &sizeRecvd);

    *nBytesGot = (int) (sizeRecvd + numFromCache);

    if (retVal==RTIOSTREAM_ERROR) {
        error = EXT_ERROR;
    } else {
        error = EXT_NO_ERROR;
    }

    return error;
} /* end ExtGetTargetPkt */

/* Function: ExtSetTargetPkt ===================================================
 * Abstract:
 *  Sets (sends) the specified number of bytes on the comm line.  As long as
 *  an error does not occur, this function is guaranteed to set the requested
 *  number of bytes.  The number of bytes set is returned via the 'nBytesSet'
 *  parameter.  EXT_NO_ERROR is returned on success, EXT_ERROR is returned on
 *  failure.
 *
 * NOTES:
 *  o it is o.k. for this function to block if no room is available (e.g.,
 *    a send call on a blocking socket)
 */
PUBLIC boolean_T ExtSetTargetPkt(
    const ExternalSim *ES,
    const int         nBytesToSet,
    const char        *src,
    int               *nBytesSet) /* out */
{   
	UserData *userData = (UserData *)esGetUserData(ES);
    boolean_T errorCode = EXT_NO_ERROR;
	int retVal;	
    #if defined (LEGO_NXT)
    const int sendTimeOutSecs = 10;
    #else
    const int sendTimeOutSecs = 120;
    #endif
    int timeoutOccurred = 0;
	
    *nBytesSet = 0;  /* assume */
    retVal = rtIOStreamBlockingSend( &(userData->rtiostreamData.libH) ,
                                    userData->rtiostreamData.streamID,
                                    (const uint8_T *) src,
                                    (size_t) nBytesToSet,
                                    sendTimeOutSecs, 
                                    &timeoutOccurred);
    if (retVal) {
        errorCode = EXT_ERROR;
        return errorCode;
    }
    
    *nBytesSet = nBytesToSet;
    return errorCode;

    
} /* end ExtSetTargetPkt */


/* Function: ExtTargetPktPending ===============================================
 * Abstract:
 *  Returns true, via the 'pending' arg, if data is pending on the comm line.
 *  Returns false otherwise.  If the timeout is 0, do simple polling (i.e.,
 *  return immediately).  Otherwise, wait the specified amount of seconds.
 *
 *  EXT_NO_ERROR is returned on success, EXT_ERROR on failure (reaching
 *  a nonzero timeout is considered a failure).
 */
PUBLIC boolean_T ExtTargetPktPending(
    const ExternalSim *ES,
    boolean_T         *pending,
    long int          timeOutSecs,
    long int          timeOutUSecs)
{
#define SLEEP_MSECS 10
    boolean_T retVal = EXT_NO_ERROR;
    int result;
    size_t sizeRecvd=0;
    int num_attempts;
    UserData *userData = (UserData *)esGetUserData(ES);

    num_attempts = (timeOutSecs*1000 + timeOutUSecs/1000)/SLEEP_MSECS;/*lint !e712 
                                                                       * loss of precision
                                                                       * long to int */

    /* Check for pending data at least once */
    if (num_attempts <= 0) {
        num_attempts = 1;
    }

    if (userData->rtiostreamData.numPending > 0) {
        *pending = 1;
        return retVal;
    } else {
        *pending = 0;
    }

    while (num_attempts>0 && sizeRecvd==0) {
        /* Call rtIOStreamRecv */
        result = ( *(userData->rtiostreamData.libH.recvFn) ) (userData->rtiostreamData.streamID,
                                userData->rtiostreamData.pendingRecvdData,
                                (const size_t)PENDING_DATA_CACHE_SIZE,
                                &sizeRecvd);

        if (result==RTIOSTREAM_ERROR) {
            retVal = EXT_ERROR;
            return retVal;
        }

        if (sizeRecvd==0) {
            SleepMilliseconds(SLEEP_MSECS);
        }
        num_attempts--;
    }
        
    if (sizeRecvd>0) {
        *pending = 1;
        userData->rtiostreamData.numPending = (int)sizeRecvd;
        userData->rtiostreamData.startIdxPending = 0;
    }

    return retVal;

} /* end ExtTargetPktPending */

/* Function: ExtCloseConnection ================================================
 * Abstract:
 *  Close the connection with the target.  In some cases, this may be 
 *  trivial (e.g., shared memory, serial cable).  In the case of sockets it
 *  takes a little work.
 *
 * NOTES:
 *  o It is assumed that this function is always successful.
 *  o It is possible that user data will be NULL (due to a shutdown
 *    caused by an error early in the connect process).
 */
PUBLIC void ExtCloseConnection(const ExternalSim *ES)
{
    UserData           *userData = (UserData *)esGetUserData(ES);
    /* only if shared library has been loaded */
    if (userData->rtiostreamData.sharedLibLoaded) {
       /* Call rtIOStreamClose */
       ( *(userData->rtiostreamData.libH.closeFn) ) (userData->rtiostreamData.streamID);
       /* unload the library */
       if (ExtUtilUnloadSharedLib(&userData->rtiostreamData) != RTIOSTREAM_NO_ERROR) {
          mexPrintf("Error unloading rtIOStream shared library.");
       }
    }

    return;
} /* end ExtCloseConnection */

/* LocalWords:  nanosleep timespec rtiostreamserial rtiostreamtcpip libmw
 * LocalWords:  Process nanosleep timespec rtiostreamserial rtiostreamtcpip
 * LocalWords:  libmw Process TCP recv
 */
