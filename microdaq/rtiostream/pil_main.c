/* Copyright 2006-2011 The MathWorks, Inc. */

/* This is a shipping version of PIL main, modified for MicroDAQ device */

/* 
 * File: pil_main.c
 *
 * PIL main
 *
 */ 

#include "xil_interface_lib.h"

int main(void) {
   XIL_INTERFACE_LIB_ERROR_CODE errorCode = XIL_INTERFACE_LIB_SUCCESS;
   /* avoid warnings about infinite loops */
   volatile int loop = 1;
   /* XIL initialization */   
   const int argc = 0;
   void * argv = (void *) 0;
   errorCode = xilInit(argc, argv);
   if (errorCode != XIL_INTERFACE_LIB_SUCCESS) {
      /* trap error with infinite loop */
      while (loop) {
      }
   }
   /* main XIL loop */
   while(loop) {
      errorCode = xilRun();
      if (errorCode != XIL_INTERFACE_LIB_SUCCESS) {
          if (errorCode == XIL_INTERFACE_LIB_TERMINATE) {
              int exitCode; 
              /* orderly shutdown of rtiostream */
              exitCode = xilTerminateComms(); 
              if (exitCode == XIL_INTERFACE_LIB_SUCCESS) {
                  exitCode = 0;
              }
              /* terminate */
              return exitCode;
          } else {
              /* terminate with error code */
              return errorCode;
          }
      }
   } 
   return errorCode;
}
