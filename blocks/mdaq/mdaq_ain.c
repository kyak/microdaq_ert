/* mdaq_ain.c -- Adc driver for MicroDAQ device
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

 #if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT) 
#include <string.h>

#include "mdaq_ain_adc.h"
#include "mdaq_ain.h"

struct mdaq_adc
{
    uint8_t ch_count;
    uint8_t resolution;
    uint32_t cap;
    float hi_range; 
    float low_range; 

    int (*init)( void );
    int (*read)( uint16_t*, uint8_t, uint8_t, uint8_t, uint8_t);
    int (*scan)( uint16_t*, uint8_t*, uint8_t, uint8_t, uint8_t, uint8_t);
}; 

/* TODO: */
static struct mdaq_adc mdaq_adc;

#if 0
static uint8_t get_adc_type( void )
{
    return MDAQ_AIN_ADS8568;
}
#endif

static int config_adc( struct mdaq_adc *c, uint8_t adc )
{
	int adc_driver;

	if ( adc > ADC09)
		return -1;

	adc_driver = (adc > MDAQ_AIN_LTC185X) ? MDAQ_AIN_ADS8568 : MDAQ_AIN_LTC185X;

	memset((void *)c, 0x0, sizeof(struct mdaq_adc));

	/* Assign driver */
    switch( adc_driver )
    {
        case MDAQ_AIN_LTC185X:
        	c->init	= ltc185x_init;
        	c->read	= ltc185x_read_ch;
        	c->scan	= ltc185x_scan_ch;
        	break;

        case MDAQ_AIN_ADS8568:
        	c->init	= ads8568_init;
        	c->read	= ads8568_read_ch;
        	c->scan	= ads8568_scan_ch;
        	break;

        default:
        	/* unsupported converter - clear structure */
        	memset((void *)c, 0x0, sizeof(struct mdaq_adc));
        	return -1;
    }

    /* other ADC parameters */
    c->ch_count 	= adc_configs[adc].ch_count;
    c->resolution 	= adc_configs[adc].resolution;
    c->hi_range 	= adc_configs[adc].high_range;
    c->low_range 	= adc_configs[adc].low_range;

    return 0;
}

static int mdaq_ain_calc( mdaq_ain_t *c, const
		uint16_t adc_value[], float value[], uint8_t ch_count )
{
	int ch_index;

	if (c->range == AIN_RANGE_5V)
	{
		c->range_high = 5.0;
		c->range_low  = 0.0;
	}
	else if (c->range == AIN_RANGE_10V)
	{
		c->range_high = 10.0;
		c->range_low  = 0.0;
	}

	if(c->polarity == AIN_POL_BIPOLAR)
		c->range_low = -c->range_high;

	for(ch_index = 0; ch_index < ch_count; ch_index++)
	{
		if(c->polarity == AIN_POL_BIPOLAR)
			value[ch_index] = ((c->range_high - c->range_low) / 0xffff) *
						(int16_t)(adc_value[ch_index]);
		else
			value[ch_index] = ((c->range_high - c->range_low) / 0xffff) *
						adc_value[ch_index];
	}
    return 0;
}

int mdaq_ain_init( uint8_t adc )
{
    int result; 

#if 0 /* TODO: detect hardware */
    int detected_adc = get_adc_type();
    if ( detected_adc =! adc)
        return -1; 
#endif

    config_adc( &mdaq_adc, adc );
   
    result = mdaq_adc.init();
    if ( result < 0 ) 
        return -1; 
     
    return 0; 
}

int mdaq_ain_config_init( mdaq_ain_t *config )
{
    if ( NULL == config )
        return -1; 
    
    memset((void *)config, 0, sizeof(mdaq_ain_t)); 
    config->gain = 1;

    return 0;
}

int mdaq_ain_read( mdaq_ain_t *config )
{
	float range;

	mdaq_adc.read(&(config->adc_value), config->ch, config->range,
			config->mode, config->polarity);

	if (config->range == AIN_RANGE_5V)
	{
		config->range_high = 5.0;
		config->range_low  = 0.0;
	}
	else if (config->range == AIN_RANGE_10V)
	{
		config->range_high = 10.0;
		config->range_low  = 0.0;
	}

	if(config->polarity == AIN_POL_BIPOLAR)
		config->range_low = -config->range_high;

	range = config->range_high - config->range_low;

	if(config->polarity == AIN_POL_BIPOLAR)
		config->value_raw = (range / 0xffff) * 	(int16_t)config->adc_value;
	else
		config->value_raw = (range / 0xffff) *  config->adc_value;

	config->value = (config->value_raw * config->gain) + config->offset;

    return 0; 
}

int mdaq_ain_scan( mdaq_ain_t *c, uint8_t ch[], uint8_t ch_count,
		uint16_t *adc_value, float *value)
{
	/* check parameters */
	if(mdaq_adc.scan == NULL ||
			ch_count == 0 ||
			ch_count > MDAQ_AIN_MAX ||
			adc_value == NULL ||
			value == NULL )
		return -1;

	int result = mdaq_adc.scan(adc_value, ch, ch_count,
			c->range, c->mode, c->polarity);

	/* calculate real value */
	mdaq_ain_calc(c, adc_value, value, ch_count );

	return 0;
}
#endif
