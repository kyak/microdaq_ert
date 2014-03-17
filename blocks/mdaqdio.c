#include "mdaq_dio.h"

void DIOInit(unsigned char pin, unsigned char dir, unsigned char init_value)
{
#ifndef MATLAB_MEX_FILE
	dio_set_pinmux(pin); 
	dio_set_dir(pin, dir); 
	dio_set(pin, init_value); 
#endif    
}
void DIOSetStep(unsigned char pin, unsigned char value)
{
#ifndef MATLAB_MEX_FILE
	dio_set(pin, value); 
#endif    
}

void DIOSetTerminate(unsigned char pin, unsigned char value)
{
#ifndef MATLAB_MEX_FILE
	dio_set(pin, value); 
#endif    
}

void DIOGetStep(unsigned char pin, unsigned char *value)
{
#ifndef MATLAB_MEX_FILE
	*value = dio_get(pin); 
#endif    
}

void DIOFncKeyInit(unsigned char func_key)
{
#ifndef MATLAB_MEX_FILE
	dio_set_pinmux(F1_KEY); 
	dio_set_pinmux(F2_KEY); 
	dio_set_dir(F1_KEY, 1); /* 1 - input  */ 
	dio_set_dir(F2_KEY, 1); 
#endif    
}

void DIOFncKeyStep(unsigned char func_key, unsigned char *value)
{
#ifndef MATLAB_MEX_FILE
	if ( func_key == 1 ) 
		*value = !dio_get(F1_KEY); 
	else if ( func_key == 2 ) 
		*value = !dio_get(F2_KEY); 
#endif    
}


