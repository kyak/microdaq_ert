#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include <string.h>
#include "mdaq_dio.h"
#endif 

void DIOConfig(unsigned char func1, unsigned char func2, 
		unsigned char func3, unsigned char func4, 
		unsigned char func5, unsigned char func6, 
		unsigned char dir1, unsigned char dir2, 
		unsigned char dir3, unsigned char dir4)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	mdaq_dio_func(ENC1_FUNC, func1);
	mdaq_dio_func(ENC2_FUNC, func2);
	mdaq_dio_func(PWM1_FUNC, func3);
	mdaq_dio_func(PWM2_FUNC, func4);
	mdaq_dio_func(PWM3_FUNC, func5);
	mdaq_dio_func(UART_FUNC, func6);

	mdaq_bank_dir(DIO_BANK1, dir1);
	mdaq_bank_dir(DIO_BANK2, dir2);
	mdaq_bank_dir(DIO_BANK3, dir3);
	mdaq_bank_dir(DIO_BANK4, dir4);
#endif    
}


void DIOInit(unsigned char pin, unsigned char dir, unsigned char init_value)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    mdaq_dio_write(pin, init_value); 
#endif    
}
void DIOSetStep(unsigned char pin, unsigned char value)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    mdaq_dio_write(pin, value); 
#endif    
}

void DIOSetTerminate(unsigned char pin, unsigned char value)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    mdaq_dio_write(pin, value); 
#endif    
}

void DIOGetStep(unsigned char pin, unsigned char *value)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    *value = mdaq_dio_read(pin); 
#endif    
}

void DIOFncKeyStep(unsigned char func_key, unsigned char *value)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    if ( func_key == 1 ) 
        *value = !mdaq_dio_read(F1);
    else if ( func_key == 2 ) 
        *value = !mdaq_dio_read(F2);
#endif    
}


