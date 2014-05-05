#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include "pru.h"
#include "mdaq_dio.h"
#include "pru_rc_controller_bin.h"
#define THRESHOLD	(1500)
#endif

void RCControllerInit( unsigned int pru_num )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	dio_set_pinmux(8); 
	dio_set_pinmux(9); 
	dio_set_pinmux(10); 
	dio_set_pinmux(11); 

	dio_set_dir(DIO9, 1); 
	dio_set_dir(DIO10, 1); 
	dio_set_dir(DIO11, 1); 
	dio_set_dir(DIO12, 1); 

	pru_stop(pru_num); 
	pru_load(pru_num, (const uint32_t *)pru_rc_controller, 
			sizeof(pru_rc_controller) / 4 ); 
	pru_run(pru_num); 
#endif
}

void RCControllerStep( unsigned char pru_num, 
		double *pwm, double *yaw, double *pitch, double *throttle) 
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	unsigned int t_pwm = pru_get_reg(pru_num, 1);
	unsigned int t_yaw = pru_get_reg(pru_num, 2);
	unsigned int t_pitch = pru_get_reg(pru_num, 3);
	unsigned int t_throttle = pru_get_reg(pru_num, 4);
		
	*pwm = (double)(t_pwm > THRESHOLD ? 0 : t_pwm);  
	*yaw = (double)(t_yaw > THRESHOLD ? 0 : t_yaw); 
	*pitch = (double)(t_pitch > THRESHOLD ? 0 : t_pitch); 
	*throttle = (double)(t_throttle > THRESHOLD ? 0 : t_throttle ); 
#endif
}
