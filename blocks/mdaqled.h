#ifndef __MDAQLED_H
#define __MDAQLED_H

#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include "gpio.h"
#endif

void mdaqled_init(void);
void mdaqled_set(unsigned char led, unsigned char state);

#endif
