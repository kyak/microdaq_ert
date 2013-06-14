#ifndef __MDAQLED_H
#define __MDAQLED_H

#ifndef MATLAB_MEX_FILE
#include "gpio.h"
#endif

void mdaqled_init(void);
void mdaqled_set(unsigned char led, unsigned char state);

#endif
