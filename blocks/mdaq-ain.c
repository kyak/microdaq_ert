
#ifndef MATLAB_MEX_FILE
#include <stdio.h>
#include <string.h>

#include "mdaq-ain.h"
#include "ltc185x.h"

/* TODO: */
#define MDAQ_AIN_NOT_SUPPORTED 		(0)
#define MDAQ_AIN_LTC185X			(1)
#define MDAQ_AIN_ADS8568			(2)

static uint8_t get_adc_type( void )
{
    /* TODO: function should read config */
    return MDAQ_AIN_LTC185X; 
}

static int init_adc( uint8_t converter )
{
    switch( converter )
    {
        case MDAQ_AIN_LTC185X: 
        	ltc185x_init();

        break; 
        case MDAQ_AIN_ADS8568: 

        break; 
        default:

        break;
    }

    return 0; 
}

int mdaq_ain_init( void )
{
    int result; 
    uint8_t ain_converter; 

    ain_converter = get_adc_type();
    if ( ain_converter == MDAQ_AIN_NOT_SUPPORTED)
        return -1; 
   
    result = init_adc( ain_converter ); 
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

	ltc185x_read_ch(&(config->adc_value), config->ch, config->range,
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


int mdaq_ain_scan( mdaq_ain_t *config, uint8_t no_ch, uint32_t no_scans,
		 	 	 float *buf, uint32_t buf_len)
{
	uint8_t ch_index;
	uint32_t sample_count = 0, scan_index;

	if( no_scans > buf_len)
		no_scans  = buf_len;


	for(scan_index = 0; scan_index < no_scans; scan_index++)
	{
		for(ch_index = 0; ch_index < no_ch; ch_index++)
		{
			mdaq_ain_read(&config[ch_index]);
			buf[sample_count++] = config[ch_index].value_raw;
		}
	}

    return 0; 
}
#endif
