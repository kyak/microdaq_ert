/* 
 * Copyright 2012 The MathWorks, Inc.
 *
 * File: rt_main.c
 *
 * Abstract:
 *
 *   A real-time main that runs generated Simulink Coder code under most 
 *   operating systems.  Based on the definition of MULTITASKING, a single-task 
 *   or multitask step function is employed.
 *
 *   This file is a useful starting point for creating a custom main when 
 *   targeting a custom floating point processor or integer micro-controller.
 *
 *   Alternatively for ERT targets, you can generate a sample ert_main.c file 
 *   with the generated code by selecting the "Generate an example main program"
 *   option.  In this case, ert_main.c is precisely customized to the
 *   model requirements.  
 *
 * Required Defines:
 *
 *   MODEL - Model name
 *   NUMST - Number of sample times
 *
 */

/*==================*
 * Required defines *
 *==================*/

#ifndef MODEL
# error Must specify a model name.  Define MODEL=name.
#else
/* create generic macros that work with any model */
# define EXPAND_CONCAT(name1,name2) name1 ## name2
# define CONCAT(name1,name2) EXPAND_CONCAT(name1,name2)
# define MODEL_INITIALIZE CONCAT(MODEL,_initialize)
# define MODEL_STEP       CONCAT(MODEL,_step)
# define MODEL_TERMINATE  CONCAT(MODEL,_terminate)
# define RT_MDL           CONCAT(MODEL,_M)
#endif

#ifndef NUMST
# error Must specify the number of sample times.  Define NUMST=number.
#endif

#if CLASSIC_INTERFACE == 1
# error "Classic call interface is not supported by rt_main.c."
#endif

#if ONESTEPFCN==0
#error Separate output and update functions are not supported by rt_main.c. \
You must update rt_main.c to suit your application needs, or select \
the 'Single output/update function' option.
#endif

#if TERMFCN==0
#error The terminate function is required by rt_main.c. \
You must update rt_main.c to suit your application needs, or select \
the 'Terminate function required' option.
#endif

#if MULTI_INSTANCE_CODE==1
#error The static version of rt_main.c does not support reusable \
code generation.  Either deselect ERT option 'Generate reusable code', \
select option 'Generate an example main program', or modify rt_main.c for \
your application needs.
#endif

#define QUOTE1(name) #name
#define QUOTE(name) QUOTE1(name)    /* need to expand name    */

#ifndef SAVEFILE
# define MATFILE2(file) #file ".mat"
# define MATFILE1(file) MATFILE2(file)
# define MATFILE MATFILE1(MODEL)
#else
# define MATFILE QUOTE(SAVEFILE)
#endif

/*==========*
 * Includes *
 *==========*/

#include "rtwtypes.h"
#if !defined(INTEGER_CODE) || INTEGER_CODE == 0
# include <stdio.h>    /* optional for printf */
#else
#ifdef __cplusplus
extern "C" {
#endif
  extern int printf(const char *, ...); 
  extern int fflush(void *);
#ifdef __cplusplus
}
#endif
#endif
#include <string.h>  /* optional for strcmp */
#include "rtmodel.h" /* optional for automated builds */

#include "rt_logging.h"
#ifdef UseMMIDataLogging
#include "rt_logging_mmi.h"
#endif

#include "ext_work.h"

#ifdef MODEL_STEP_FCN_CONTROL_USED
#error The static version of rt_main.c does not support model step function prototype control.
#endif

/*========================* 
 * Setup for multitasking * 
 *========================*/

/* 
 * Let MT be synonym for MULTITASKING (to shorten command line for DOS) 
 */
#if defined(MT)
# if MT == 0
# undef MT
# else
# define MULTITASKING 1
# endif
#endif

#if defined(TID01EQ) && TID01EQ == 1
#define FIRST_TID 1
#else 
#define FIRST_TID 0
#endif

/*====================*
 * External functions *
 *====================*/

extern void MODEL_INITIALIZE(void);
extern void MODEL_TERMINATE(void);

#if !defined(MULTITASKING)
 extern void MODEL_STEP(void);       /* single-rate step function */
#else
 extern void MODEL_STEP(int_T tid);  /* multirate step function */
#endif

Clock_Handle rt_task_handle;
Void rt_task_function(UArg arg0);
int_T rt_TermModel(void);

/*==================================*
 * Global data local to this module *
 *==================================*/
#ifndef MULTITASKING
static boolean_T OverrunFlags[1];    /* ISR overrun flags */
static boolean_T eventFlags[1];      /* necessary for overlapping preemption */
#else
static boolean_T OverrunFlags[NUMST];
static boolean_T eventFlags[NUMST]; 
#endif

/*===================*
 * Visible functions *
 *===================*/

#if !defined(MULTITASKING) /* single task */

/* Function: rtOneStep ========================================================
 *
 * Abstract:
 *   Perform one step of the model.  This function is modeled such that
 *   it could be called from an interrupt service routine (ISR) with minor
 *   modifications.
 */
static void rt_OneStep(void)
{
    /* Disable interrupts here */

    /***********************************************
     * Check and see if base step time is too fast *
     ***********************************************/
    if (OverrunFlags[0]++) {
        rtmSetErrorStatus(RT_MDL, "Overrun");
    }

    /*************************************************
     * Check and see if an error status has been set *
     * by an overrun or by the generated code.       *
     *************************************************/
    if (rtmGetErrorStatus(RT_MDL) != NULL) {
	rt_TermModel(); 
        return;
    }

    if (rtmGetStopRequested(RT_MDL)) {
	rt_TermModel(); 
        return;
    }

    /* Save FPU context here (if necessary) */
    /* Reenable interrupts here */
    /* Set model inputs here */

    /**************
     * Step model *
     **************/
    MODEL_STEP();

    /* Get model outputs here */

    /**************************
     * Decrement overrun flag *
     **************************/
    OverrunFlags[0]--;

    rtExtModeCheckEndTrigger();

    /* Disable interrupts here */
    /* Restore FPU context here (if necessary) */
    /* Reenable interrupts here */

} /* end rtOneStep */

#else /* multitask */

/* Function: rtOneStep ========================================================
 *
 * Abstract:
 *   Perform one step of the model.  This function is modeled such that
 *   it could be called from an interrupt service routine (ISR) with minor
 *   modifications.
 *
 *   Note that error checking is only necessary when this routine is
 *   attached to an interrupt.
 *
 *   Also, you may wish to unroll any or all of for and while loops to
 *   improve the real-time performance of this function.
 */
static void rt_OneStep(void)
{
    int_T i;

    /* Disable interrupts here */

    /***********************************************
     * Check and see if base step time is too fast *
     ***********************************************/
    if (OverrunFlags[0]++) {
        rtmSetErrorStatus(RT_MDL, "Overrun");
    }

    /*************************************************
     * Check and see if an error status has been set *
     * by an overrun or by the generated code.       *
     *************************************************/
    if (rtmGetErrorStatus(RT_MDL) != NULL) {
        return;
    }

    /* Save FPU context here (if necessary) */
    /* Reenable interrupts here */
    
    /*************************************************
     * Update EventFlags and check subrate overrun   *
     *************************************************/
    for (i = FIRST_TID+1; i < NUMST; i++) {
        if (rtmStepTask(RT_MDL,i) && eventFlags[i]++) {
            OverrunFlags[0]--;
            OverrunFlags[i]++;
            /* Sampling too fast */
            rtmSetErrorStatus(RT_MDL, "Overrun");
            return;
        }
        if (++rtmTaskCounter(RT_MDL,i) == rtmCounterLimit(RT_MDL,i))
            rtmTaskCounter(RT_MDL, i) = 0;
    }

    /* Set model inputs associated with base rate here */

    /*******************************************
     * Step the model for the base sample time *
     *******************************************/
    MODEL_STEP(0);

    /* Get model outputs associated with base rate here */

    /************************************************************************
     * Model step complete for base sample time, now it is okay to          *
     * re-interrupt this ISR.                                               *
     ************************************************************************/
    OverrunFlags[0]--;

    /*********************************************************
     * Step the model for any other sample times (subrates) *
     *********************************************************/
    for (i = FIRST_TID+1; i < NUMST; i++) {
        /*************************************************************
         * If task "i" is running, don't run any lower priority task *
         *************************************************************/
        if (OverrunFlags[i]) return; 

        if (eventFlags[i]) {
            OverrunFlags[i]++;

            /* Set model inputs associated with subrate here */

            /******************************************
             * Step the model for sample time "i" *
             ******************************************/
            MODEL_STEP(i);

            /* Get model outputs associated with subrate here */
            
            /**********************************************
             * Indicate task complete for sample time "i" *
             **********************************************/
            OverrunFlags[i]--;
            eventFlags[i]--;
        }
    }

    rtExtModeCheckEndTrigger();
    /* Disable interrupts here */
    /* Restore FPU context here (if necessary) */
    /* Enable interrupts here */

} /* end rtOneStep */

#endif /* MULTITASKING */

/* Function: rt_InitModel ====================================================
 * 
 * Abstract: 
 *   Initialized the model and the overrun flags
 *
 */
void rt_InitModel(void)
{
#if defined(MULTITASKING)
    int i;
    for(i=0; i < NUMST; i++) {
        OverrunFlags[i] = 0;
        eventFlags[i] = 0;
    }
#else
    OverrunFlags[0] = 0;
    eventFlags[0] = 0;
#endif

    /************************
     * Initialize the model *
     ************************/
    MODEL_INITIALIZE();
}

/* Function: rt_TermModel ====================================================
 * 
 * Abstract:
 *   Terminates the model and prints the error status
 *
 */
int_T rt_TermModel(void)
{
    static int term = 0; 

    /* prevent to call MODEL_TERMINATE more then once */ 
    if ( !term ) 
    {
        term = 1; 
        MODEL_TERMINATE();

        {
            const char_T *errStatus = (const char_T *) (rtmGetErrorStatus(RT_MDL));
            int_T i;

            if (errStatus != NULL && strcmp(errStatus, "Simulation finished")) {
                (void)printf("%s\n", errStatus);
                for (i = 0; i < NUMST; i++) {
                    if (OverrunFlags[i]) {
                        (void)printf("ISR overrun - sampling rate too"
                                "fast for sample time index %d.\n", i);
                    }
                }
                return(1);
            }
        }
    } 
    return(0);
}

/* Function: main =============================================================
 *
 * Abstract:
 *   Execute model on a generic target such as a workstation.
 */
int_T main(int_T argc, const char *argv[])
{
    /* External mode */
    Clock_Params clkParams;
    Timer_Params user_sys_tick_params;
    Timer_Handle user_sys_tick_timer;

    /************************
     * Initialize the model *
     ************************/
    rt_InitModel();

    /* External mode */
    rtSetTFinalForExtMode(&rtmGetTFinal(RT_MDL));
    rtExtModeCheckInit(NUMST);

    /* Create timer for user system tick */
    Timer_Params_init(&user_sys_tick_params);
    user_sys_tick_params.period = STEP_SIZE;
    user_sys_tick_params.periodType = Timer_PeriodType_MICROSECS;
    user_sys_tick_params.arg = 1;

    user_sys_tick_timer = Timer_create(1,
    		(ti_sysbios_hal_Timer_FuncPtr)Clock_tick, &user_sys_tick_params, NULL);

    if(user_sys_tick_timer == NULL)
    {
    	System_abort("Unable to create user system tick timer!");
    }

    /* Create a periodic Clock Instance with period = 1 system time units */
    Clock_Params_init(&clkParams);
    clkParams.period = 1;
    clkParams.startFlag = TRUE;
    rt_task_handle = Clock_create(rt_task_function, 10, &clkParams, NULL);
    
    rtExtModeC6000Startup(rtmGetRTWExtModeInfo(RT_MDL),
                          NUMST,
                          (boolean_T *)&rtmGetStopRequested(RT_MDL));
    BIOS_start();
}

Void rt_task_function(UArg arg0)
{
    /* Base rate */
    rt_OneStep();
}

