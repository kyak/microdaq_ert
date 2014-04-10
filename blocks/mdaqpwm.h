#ifndef _MDAQPWM_H_
#define _MDAQPWM_H_

void PWMInit(unsigned char module, unsigned int period, unsigned char polarity );
void PWMStep( unsigned char module, double pwm_a, double pwm_b );
void PWMTerminate( unsigned char module );

#endif /* _MDAQPWM_H_ */ 

