
#ifndef _EHRPWM_H_
#define _EHRPWM_H_

#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
int ehrpwm_db_set_delay(uint8_t module, unsigned char edge,
		enum config_mask cfgmask, unsigned long delay);

/* Dead Band Configuration functions */
int ehrpwm_db_set_mode(uint8_t module, unsigned char inmode,
		unsigned char polsel, unsigned char outmode);

int ehrpwm_pc_configure(uint8_t module, unsigned char chpduty,
		unsigned char chpfreq, unsigned char oshtwidth);
int ehrpwm_pc_en_dis(uint8_t module, unsigned char chpen);
int ehrpwm_pwm_start(uint8_t module);
int ehrpwm_pwm_stop(uint8_t module);
int ehrpwm_pwm_set_pol(uint8_t module, uint8_t polarity);
int ehrpwm_pwm_set_prd(uint8_t module, uint32_t period, uint8_t polarity);
int ehrpwm_hr_duty_config(uint8_t module, uint16_t tick_hz, uint32_t duty_ns);
int ehrpwm_pwm_set_dty(uint8_t module, uint32_t duty);
#endif 

#endif /* _EHRPWM_H_ */
