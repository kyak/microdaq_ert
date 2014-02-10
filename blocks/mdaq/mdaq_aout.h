/* mdaq_aout.h -- DAC driver for MicroDAQ device
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */


#ifndef MDAQ_AOUT_H
#define MDAQ_AOUT_H
#include <stdint.h>

#define MDAQ_AOUT_MAX		(8)

#define AOUT_ASYNC			(1 << 1)
#define AOUT_SYNC			(1 << 2)

enum dac_id
{
	DAC01 = 1,
	DAC02
};

typedef struct mdaq_aout_config_
{
    int8_t              ch;
    float               gain;
    float               offset;
    float               range_low;
    float               range_high;
    uint16_t			dac_value;
    uint16_t     		mode;
}mdaq_aout_t;

int mdaq_aout_init( uint8_t converter,  uint8_t mode);
int mdaq_aout_write(uint8_t ch, float data );
int mdaq_aout_write_multi( uint8_t ch[], uint8_t ch_count,
		const float *value, uint32_t mode);

#endif /* MDAQ_AOUT_H */
