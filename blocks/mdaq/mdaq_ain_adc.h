/* mdaq_ain_adc.h -- Adc driver for MicroDAQ device
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#ifndef MDAQ_AIN_ADC_H
#define MRAQ_AIN_ADC_H

#include <stdint.h>
#include "ads8568.h"
#include "ltc185x.h"

/* supported ADCs */
#define MDAQ_AIN_LTC185X			(2)
#define MDAQ_AIN_ADS8568			(9)

/* ADC capabilities */
#define ADC_DIFF 		(1 << 0)
#define ADC_POLARITY	(1 << 1)
#define ADC_RANGE		(1 << 2)
#define ADC_SIMULT		(1 << 3)


/* ADC config structure */
struct ain_adc_config
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
struct ain_adc_config adc_configs[] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0}, /* not supported */
		/* LTC185x */
		{ADC01, 166000, 8, 12, 10, 1, 1, -10.0, 10.0},
		{ADC02, 166000, 8, 16, 10, 1, 1, -10.0, 10.0},
		/* ADS8x68 */
		{ADC03, 200000, 8, 12, 10, 1, 0, -10.0, 10.0},
		{ADC04, 400000, 8, 12, 10, 1, 0, -10.0, 10.0},
		{ADC05, 600000, 8, 12, 10, 1, 0, -10.0, 10.0},
		{ADC06, 200000, 16, 12, 10, 1, 0, -10.0, 10.0},
		{ADC07, 400000, 16, 12, 10, 1, 0, -10.0, 10.0},
		{ADC08, 600000, 16, 12, 10, 1, 0, -10.0, 10.0},
		{ADC09, 500000, 16, 16, 10, 1, 0, -10.0, 10.0}
};

#endif /* MDAQ_AIN_ADC_H */
