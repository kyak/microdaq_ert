#ifndef _RC_CONTROLLER_H
#define _RC_CONTROLLER_H

void RCControllerInit( unsigned int pru_num );
void RCControllerStep( unsigned char pru_num, double *pwm, double *yaw, double *pitch, double *throttle);

#endif /* _RC_CONTROLLER_H */

