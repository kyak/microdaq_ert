/* mdaq_out.c -- DAC driver for MicroDAQ device
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */
 
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT) 
#include "dac7568.h"
#include "mdaq_aout.h"


/* TODO: sync/async mode */

/* TODO: move to separate file ?  */

struct ain_aout_config
{
	uint32_t id;
	uint32_t samples_per_sec;
	uint8_t ch_count;
	uint8_t resolution;
	uint8_t range;
	uint8_t bipolar;
	uint8_t differential;
	float low_range;
	float high_range;
};

/* available ADCs parameters */
struct ain_aout_config dac_configs[] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0}, /* not supported */
		/* DAC7567 DAC8568*/
		{DAC01, 500000, 8, 12, 10, 1, 1, 0.0, 5.0},
		{DAC02, 500000, 8, 12, 10, 1, 1, -10.0, 10.0},
};

struct mdaq_dac
{
    uint8_t ch_count;
    uint8_t resolution;
    uint32_t config;
    float hi_range;
    float low_range;
};

/* TODO: */
static struct mdaq_dac mdaq_dac;

int mdaq_aout_init( uint8_t dac, uint8_t mode)
{
	uint8_t init_state;

/* TODO: */
	if ( dac > DAC02 || !dac )
		return -1;

/* TODO: */
	switch(dac)
	{
		case DAC01: init_state = DAC_ZERO_SCALE; break;
		case DAC02: init_state = DAC_MID_SCALE; break;
		default:
			init_state = DAC_ZERO_SCALE;
	}

	dac7568_init( mode, init_state );

	mdaq_dac.hi_range = dac_configs[dac].high_range;
	mdaq_dac.low_range = dac_configs[dac].low_range;
	mdaq_dac.resolution = dac_configs[dac].resolution;

    return 0;
}

static void calc_dac_data(const float data[], uint16_t dac_data[], uint8_t count)
{
	int i;
	int digital_range = ( 1 << mdaq_dac.resolution ) - 1;
	float voltage_step = (float)digital_range / (mdaq_dac.hi_range - mdaq_dac.low_range) ;
	float offset = (mdaq_dac.low_range < 0) ? -mdaq_dac.low_range : 0;

	for(i = 0; i < count; i++ )
		dac_data[i] = (uint16_t)((offset + data[i]) * voltage_step);

	return;
}

int mdaq_aout_write(uint8_t ch, float data )
{
	int digital_range = ( 1 << mdaq_dac.resolution ) - 1;
	float voltage_step = mdaq_dac.hi_range - mdaq_dac.low_range / (float)digital_range;
	float offset = (mdaq_dac.low_range < 0) ? -mdaq_dac.low_range : 0;

	dac7568_write_data(ch, (uint16_t)((offset + data) * voltage_step), AOUT_ASYNC);

	return 0;
}

int mdaq_aout_write_multi( uint8_t ch[], uint8_t ch_count,
		const float *value, uint32_t mode)
{
	uint16_t buf[MDAQ_AOUT_MAX];

	calc_dac_data(value, buf, ch_count);
	dac7568_write_multi(ch, ch_count, buf, mode);

	return 0;
}

#endif
