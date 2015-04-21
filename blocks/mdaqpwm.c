#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include "mdaq_pwm.h"
#endif

void PWMInit(unsigned char module, unsigned int period, unsigned char polarity )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    mdaq_pwm_init(module, period,  polarity, 0, 0);
#endif 
}

void PWMStep( unsigned char module, double pwm_a, double pwm_b ) 
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    mdaq_pwm_write(module, pwm_a, pwm_b);
#endif 
}

void PWMTerminate( unsigned char module )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    mdaq_pwm_write(module, 0, 0);
#endif 
}

