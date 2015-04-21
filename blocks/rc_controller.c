#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include "mdaq_pru.h"
#include "pru_rc_controller_bin.h"
#endif

#define THRESHOLD	(1500)

void RCControllerInit( unsigned int pru_num )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	mdaq_pru_stop(pru_num); 
	mdaq_pru_load(pru_num, (const uint32_t *)pru_rc_controller, 
			sizeof(pru_rc_controller) / 4 ); 
	mdaq_pru_start(pru_num); 
#endif
}

void RCControllerStep( unsigned char pru_num, 
		double *pwm, double *yaw, double *pitch, double *throttle) 
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	unsigned int t_pwm = mdaq_pru_reg_read(pru_num, 1);
	unsigned int t_yaw = mdaq_pru_reg_read(pru_num, 2);
	unsigned int t_pitch = mdaq_pru_reg_read(pru_num, 3);
	unsigned int t_throttle = mdaq_pru_reg_read(pru_num, 4);
		
	*pwm = (double)(t_pwm > THRESHOLD ? 0 : t_pwm);  
	*yaw = (double)(t_yaw > THRESHOLD ? 0 : t_yaw); 
	*pitch = (double)(t_pitch > THRESHOLD ? 0 : t_pitch); 
	*throttle = (double)(t_throttle > THRESHOLD ? 0 : t_throttle ); 
#endif
}
