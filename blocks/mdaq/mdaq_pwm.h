/* mdaq_pwm.h -- PWM driver for MicroDAQ
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#ifndef MDAQ_PWM_H_
#define MDAQ_PWM_H_

#include <stdint.h>

enum mdaq_pwm_channels
{
	PWM0A = 0,
	PWM0B,
	PWM1A,
	PWM1B,
	PWM2A,
	PWM2B
};

enum mdaq_pwm_polarity
{
	ACTIVE_HIGH = 0,
	ACTIVE_LOW
};

int mdaq_pwm_init(void);
int mdaq_pwm_start(uint8_t channel);
int mdaq_pwm_stop(uint8_t channel);
int mdaq_pwm_setup(uint8_t channel, uint32_t period, uint8_t polarity);
int mdaq_pwm_set_duty(uint8_t channel, float duty);
int mdaq_pwm_set_polarity(uint8_t channel, uint8_t polarity);

#endif /* MDAQ_PWM_H_ */
