#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include "pru.h"
#include "mdaqmotor.h"
#endif

#define MOTOR_DRIVER_PRU	(1)
#define CONFIG_REG		(0)
#define PWM_REG			(1)
#define MAX_KHZ_FREQ	(10)

#define GATE_EN_BIT		(0)
#define SET_DIR_BIT		(1)

static unsigned short pwm_period; 
void MOTORInit(unsigned char motor, unsigned char type, unsigned char pwm_freq)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	if ( pwm_freq > MAX_KHZ_FREQ )
		pwm_freq = MAX_KHZ_FREQ; 

	unsigned int pwm_config = 10000 / pwm_freq; 
	pwm_period = 10000 / pwm_freq;

	pru_set_reg(MOTOR_DRIVER_PRU, CONFIG_REG, 0x0); 
	pru_set_reg(MOTOR_DRIVER_PRU, PWM_REG, pwm_config); 

#endif
}

void MOTORStep(unsigned char motor, unsigned char en, unsigned char dir, unsigned int pwm_duty)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    unsigned int config = 0; 
    unsigned int pwm_config = 0;  
    if ( en )
    {
            /* first 16 bit for PWM period */ 
            pwm_config |= pwm_period; 
            /* last 16 bit for PWM duty */ 
            pwm_config |= ( ( (pwm_duty * pwm_period) / 1000 )  << 16);

            /* set PRU register with new PWM config */ 
	        pru_set_reg(MOTOR_DRIVER_PRU, PWM_REG, pwm_config); 
           
            config |= (1 << GATE_EN_BIT); 
            if ( dir )
            {
                config |= (1 << SET_DIR_BIT); 
            }
            pru_set_reg(MOTOR_DRIVER_PRU, CONFIG_REG, config);
    }
    else 
    {
        if ( dir )
        {
            config |= (1 << SET_DIR_BIT); 
        }
        pru_set_reg(MOTOR_DRIVER_PRU, CONFIG_REG, config);
    }
#endif
}

void MOTORTerminate(unsigned char motor)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	pru_set_reg(MOTOR_DRIVER_PRU, CONFIG_REG, 0x0);
	pru_set_reg(MOTOR_DRIVER_PRU, PWM_REG, 0x0);
#endif
}

