/* mdaq_pwm.c -- PWM driver for MicroDAQ
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#include <stdint.h>

#include "ehrpwm.h"
#include "hardware.h"

#include "mdaq_pwm.h"

#define PWM_PERIOD_TO_US	(150)
#define DEFAULT_PWM_PERIOD	(100)

static uint32_t mdaq_pwm_period[6];

static void pwm_enable_clk(void)
{
	volatile uint32_t *addr = (uint32_t *)(SYS_CFG_BASE + 0x180);
	uint32_t reg = *addr;
	reg |= (1 << 12);
	*addr = reg;
}

#if 0
static void pwm_disable_clk(void)
{
	volatile uint32_t *addr = (uint32_t *)(SYS_CFG_BASE + 0x180);
	uint32_t reg = *addr;
	reg &= ~(1 << 12);
	*addr = reg;
}
#endif

/* TODO */
static void pwm_set_pinmux(void)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
		uint32_t mux_conf = 0;
		volatile uint32_t *mux_addr = (uint32_t *)(SYS_CFG_BASE + 0x120);

#define PINMUX_11	(11)
#define PINMUX_13	(13)

#define PWM0A_NIBBLE	(6)
#define PWM0B_NIBBLE	(5)

#define PWM1A_NIBBLE	(4)
#define PWM1B_NIBBLE	(3)

#define PWM2A_NIBBLE	(2)
#define PWM2B_NIBBLE	(1)

		mux_addr += PINMUX_11;

		mux_conf = *mux_addr;
		mux_conf &= ~(0xf << (PWM0A_NIBBLE * 4));
		mux_conf |= 0x2 << (PWM0A_NIBBLE * 4);
		*mux_addr = mux_conf;

		mux_conf &= ~(0xf << (PWM0B_NIBBLE * 4));
		mux_conf |= 0x2 << (PWM0B_NIBBLE * 4);
		*mux_addr = mux_conf;

		mux_addr = (uint32_t *)(SYS_CFG_BASE + 0x120);
		mux_addr += PINMUX_13;

		mux_conf = *mux_addr;
		mux_conf &= ~(0xf << (PWM1A_NIBBLE * 4));
		mux_conf |= 0x2 << (PWM1A_NIBBLE * 4);
		*mux_addr = mux_conf;

		mux_conf &= ~(0xf << (PWM1B_NIBBLE * 4));
		mux_conf |= 0x2 << (PWM1B_NIBBLE * 4);
		*mux_addr = mux_conf;

		mux_conf &= ~(0xf << (PWM2A_NIBBLE * 4));
		mux_conf |= 0x2 << (PWM2A_NIBBLE * 4);
		*mux_addr = mux_conf;

		mux_conf &= ~(0xf << (PWM2B_NIBBLE * 4));
		mux_conf |= 0x2 << (PWM2B_NIBBLE * 4);
		*mux_addr = mux_conf;

#endif
	return;
}

int mdaq_pwm_init(void)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)

	static int first_time_pwm_init = 1;
	int pwm_channel;

	if (first_time_pwm_init)
	{
		pwm_set_pinmux();

		pwm_enable_clk();

		for(pwm_channel = 0; pwm_channel <= PWM2B; pwm_channel++)
		{
			mdaq_pwm_stop(pwm_channel);
		}
		first_time_pwm_init = 0;
	}
#endif
	return 0;
}

int mdaq_pwm_setup(uint8_t channel, uint32_t period, uint8_t polarity)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	period *= PWM_PERIOD_TO_US;
	mdaq_pwm_period[channel] = period;
	ehrpwm_pwm_set_prd(channel, period, polarity);
	ehrpwm_pwm_set_dty(channel, 0);
#endif 
	return 0;
}

int mdaq_pwm_set_duty(uint8_t channel, float duty)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	uint32_t tmp;

	if (duty > 100.0)
		duty = 100.0; 
	if (duty < 0.0)
		duty = 0.0;

	tmp = (uint32_t)((float)mdaq_pwm_period[channel] * (duty / 100.0));
	return ehrpwm_pwm_set_dty(channel, tmp);
#endif 
}

int mdaq_pwm_set_polarity(uint8_t channel, uint8_t polarity)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	return ehrpwm_pwm_set_pol(channel, polarity);
#endif 
}

int mdaq_pwm_start(uint8_t channel)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	return ehrpwm_pwm_start(channel);
#endif 
}

int mdaq_pwm_stop(uint8_t channel)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	mdaq_pwm_set_duty(channel, 0);
	return ehrpwm_pwm_stop(channel);
#endif 
}

