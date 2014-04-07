/*
 * Copyright 1994-2012 The MathWorks, Inc.
 *
 * File: ext_work.c     
 *
 * Abstract:
 *   
 */
// RTS library headers
#include <stdio.h>
#include <stdlib.h>        /* for exit() */

// Mathworks data type definitions
#include "rtwtypes.h"
#include "rtw_extmode.h"

// External mode headers
#include "ext_types.h"
#include "ext_share.h"
#include "updown.h"
#include "ext_svr_c6000.h"
#include "ext_svr_transport_c6000.h"
#include "ext_work.h"
//
// DSP/BIOS headers
//
#include <xdc/std.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>

#include <xdc/cfg/global.h>

// Define external mode simulation states
typedef enum {
    EXTMODE_STARTUP = 0,
    EXTMODE_NET_INITIALIZED,
    EXTMODE_WAITING_START_PACKET, 
    EXTMODE_RUNNING,
    EXTMODE_STOPPED,
    NUM_EXTMODE_SIM_STATES
} ExtModeSimStatus;

// Global variables used for external
int_T            volatile startModel       = FALSE;
TargetSimStatus  volatile modelStatus      = TARGET_STATUS_WAITING_TO_START;
ExtModeSimStatus volatile extmodeSimStatus = EXTMODE_STARTUP;
Semaphore_Handle uploadSem;
Semaphore_Handle extStartStopSem;
Task_Handle extern_pkt_tid;
Task_Handle extern_upload_tid;

// External mode task stack sizes
#define EXT_MODE_TSK_STACK_SIZE (6144)
uint8_T stack_pkt_tid[EXT_MODE_TSK_STACK_SIZE];
uint8_T stack_upload_tid[EXT_MODE_TSK_STACK_SIZE];
PRIVATE void rtExtModeInitUD(void);
//extern void TSK_prolog(TSK_Handle hTask);
//extern void TSK_epilog(TSK_Handle hTask);
//extern void waitNetworkStartup(void);

/* TODO: should be called in ext_main.c */ 
extern int_T rt_TermModel(void); 
extern Clock_Handle rt_task_handle;

ExtStepArgs sExtStepArgs;

// External mode startup function
void rtExtModeC6000Startup( RTWExtModeInfo *ei,
                            int_T          numSampTimes,
                            boolean_T      *stopReqPtr)
{
    Task_Params attr;
    Task_Params_init(&attr);
    Semaphore_Params sem_params; 
    Semaphore_Params_init(&sem_params);

    sem_params.mode = ti_sysbios_knl_Semaphore_Mode_BINARY; 
  
    sExtStepArgs.ei = ei;
    sExtStepArgs.numSampTimes = numSampTimes;
    sExtStepArgs.stopReqPtr = stopReqPtr;
    attr.arg1 = (UArg) &sExtStepArgs;

    // Set external mode state to 
    extmodeSimStatus = EXTMODE_STARTUP;

	// Initialize semaphores used for external mode
	// communication
    uploadSem = Semaphore_create(1, &sem_params, NULL);
    extStartStopSem = Semaphore_create(1, NULL, NULL);

    // Pause until Ethernet network initialization completes
    //waitNetworkStartup();
    extmodeSimStatus = EXTMODE_NET_INITIALIZED;

    // Initialize user data structure
    rtExtModeInitUD();
    rt_ExtModeInit();

    // Create external mode task
    attr.priority = 1;
    attr.stack = (Ptr) &stack_pkt_tid[0];
    attr.stackSize = EXT_MODE_TSK_STACK_SIZE;
    extern_pkt_tid = Task_create( (Task_FuncPtr) rtExtModeOneStep,
        &attr, NULL );
    if (extern_pkt_tid == NULL) 
    {
        printf("handle taskpawn error");
    }

 
    /*
     * Pause until receive model start packet - if external mode.
     * Make sure the external mode tasks are running so that 
     * we are listening for commands from the host.
     */
    extmodeSimStatus = EXTMODE_WAITING_START_PACKET;
    modelStatus      = TARGET_STATUS_WAITING_TO_START;
    if (ExtWaitForStartPkt()) 
    {
        printf("\nWaiting for start packet from host.\n");
        // rt_PktServerWork() function posts a semaphore when
        // it receives start packet from host
        // this function in turn runs as part of rt_PktServer task
        //Semaphore_pend(extStartStopSem, BIOS_WAIT_FOREVER);
        while (rt_PktServerWork(ei, numSampTimes, stopReqPtr) != EXT_MODEL_START)
        {
        };
    }
    modelStatus      = TARGET_STATUS_RUNNING;
    extmodeSimStatus = EXTMODE_RUNNING;
}

void rtExtModeC6000Cleanup(int_T numSampTimes)
{
    // Change external mode state to STOP
    // to signal rtExtModeOneStep() task to
    // complete remaining Pkt / Upload work
    extmodeSimStatus = EXTMODE_STOPPED;

    // Wait for external mode server task to
    // shutdown
    /*Semaphore_pend(extStartStopSem, BIOS_WAIT_FOREVER); */
    

    // Delete external mode task
    //TSK_epilog( extern_pkt_tid );
    /*Task_delete( &extern_pkt_tid ); */
}

// This task is run at priority level 1, essentially a background
// task. 
void rtExtModeOneStep(UArg arg0, ExtStepArgs *arg1)
{
    // Process external mode packets and upload data
    //TSK_prolog( TSK_self() );
    RTWExtModeInfo *ei = arg1->ei;
    int_T numSampTimes = arg1->numSampTimes;
    boolean_T *stopReqPtr = arg1->stopReqPtr;
    while (extmodeSimStatus != EXTMODE_STOPPED) {
        rt_PktServerWork(ei, numSampTimes, stopReqPtr);
        rt_UploadServerWork(numSampTimes);
    }
    rt_ExtModeShutdown(numSampTimes);
    //TSK_epilog( TSK_self() );
    
    /* TODO: */ 
    Clock_delete( &rt_task_handle );
    rt_TermModel();
    
    // Signal completion of Pkt / Upload server work
    Semaphore_post(extStartStopSem);
}

void rtExtModeUpload(int_T tid, real_T taskTime)
{
    rt_UploadBufAddTimePoint(tid, taskTime);
}

void rtExtModeCheckEndTrigger(void)
{
    rt_UploadCheckEndTrigger();
}

void rtExtModeUploadCheckTrigger(int_T numSampTimes)
{
    rt_UploadCheckTrigger(numSampTimes);
}

void rtExtModeCheckInit(int_T numSampTimes)
{
    UNUSED_PARAMETER(numSampTimes);
    if (rt_ExtModeInit() != EXT_NO_ERROR) exit(EXIT_FAILURE);
}

void rtExtModeShutdown(int_T numSampTimes)
{
    //rt_ExtModeShutdown(numSampTimes);
}

extern PUBLIC const char_T *ExtInitUD(void);
PRIVATE void rtExtModeInitUD(void)
{
    const char_T *extErrStr = ExtInitUD();
   
    if (extErrStr != NULL) {
        printf("\nError processing External Mode command line arguments:\n");
        printf("\t%s", extErrStr);

        exit(EXIT_FAILURE);
    }
}

/* Start of ERT specific functions and data */
#ifndef C6000_EXT_MODE
static void displayUsage(void)
{
    (void) printf("usage: model_name -tf <finaltime> -w -port <TCPport>\n");
    (void) printf("arguments:\n");
    (void) printf("  -tf <finaltime> - overrides final time specified in "
                  "Simulink (inf for no limit).\n");
    (void) printf("  -w              - waits for Simulink to start model "
                  "in External Mode.\n");
    (void) printf("  -port <TCPport> - overrides 17725 default port in "
                  "External Mode, valid range 256 to 65535.\n");
}
#endif

static const real_T RUN_FOREVER = (real_T)-1;
#if INTEGER_CODE == 0
static real_T finaltime = (real_T)-2; /* default to stop time in Sim Params. */
#else
static real_T finaltime = (real_T)-1; /* default to stop time inf */
#endif

void rtERTExtModeSetTFinal(real_T *rtmTFinal)
{
    if (finaltime >= (real_T)0 || finaltime == RUN_FOREVER) {
        *rtmTFinal = finaltime;
    }
}

void rtSetTFinalForExtMode(real_T *rtmTFinal)
{
    rtERTExtModeSetTFinal(rtmTFinal);
}

void rtERTExtModeStartMsg(void)
{
    #ifndef EXTMODE_DISABLEPRINTF
        (void)printf("\n** starting the model **\n");
    #endif
}


/* End of ERT specific functions and data */

/* [EOF] ext_work.c */


