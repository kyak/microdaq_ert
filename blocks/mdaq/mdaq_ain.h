/* mdaq_ain.h -- Adc driver for MicroDAQ device
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */


#ifndef MDAQ_AIN_H
#define MDAQ_AIN_H

#include <stdint.h>
#include "mdaq_trig.h"
#include "mdaq_ain_cap.h"

#define MDAQ_AIN_MAX		(8)

typedef struct mdaq_ain_config_
{
    int8_t              ch; 
    float               gain;
    float               offset; 
    float               value; 
    float               value_raw; 
    float               range_low; 
    float               range_high; 
    uint16_t			adc_value;
    mdaq_ain_range_t    range;  
    mdaq_ain_mode_t     mode; 
    mdaq_ain_pol_t		polarity;
}mdaq_ain_t; 


int mdaq_ain_init( void ); 
int mdaq_ain_config_init( mdaq_ain_t *config ); 

int mdaq_ain_read( mdaq_ain_t *config ); 
int mdaq_ain_scan( mdaq_ain_t *config, uint8_t no_ch, uint32_t no_scans,
						float *buf, uint32_t buf_len);

#endif /* MDAQ_AIN_H */ 
