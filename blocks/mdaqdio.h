#ifndef __MDAQGPIO_H
#define __MDAQGPIO_H

#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include "gpio.h"
#endif

void DIOInit(unsigned char pin, unsigned char dir, unsigned char init_value);
void DIOSetStep(unsigned char pin, unsigned char value);
void DIOSetTerminate(unsigned char pin, unsigned char value);
void DIOGetStep(unsigned char pin, unsigned char *value);

void DIOFncKeyInit(unsigned char func_key);
void DIOFncKeyStep(unsigned char func_key, unsigned char *value);

#endif
