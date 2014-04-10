#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include "mdaq_pwm.h"
#include "mdaqpwm.h"
#endif

void PWMInit(unsigned char module, unsigned int period, unsigned char polarity )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	module *= 2; 
	mdaq_pwm_init(); 
	mdaq_pwm_setup( module, period, polarity); 
	mdaq_pwm_setup( module + 1, period, polarity); 
	mdaq_pwm_start( module ); 
	mdaq_pwm_start( module + 1); 
#endif 
}

void PWMStep( unsigned char module, double pwm_a, double pwm_b ) 
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	module *= 2; 
	mdaq_pwm_set_duty(module, pwm_a);
	mdaq_pwm_set_duty(module + 1, pwm_b);
#endif 
}

void PWMTerminate( unsigned char module )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	module *= 2; 
	mdaq_pwm_stop( module ); 
	mdaq_pwm_stop( module + 1); 
#endif 
}

