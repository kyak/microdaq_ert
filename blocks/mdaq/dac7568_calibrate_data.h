/* dac7568_calibrate_data.h -- DAC calibrate data
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#ifndef DAC7568_CALIBRATE_DATA_H
#define DAC7568_CALIBRATE_DATA_H
#include <stdint.h>

#define DAC7568_NR_CHANNELS		(8)

static float calibrate_data[DAC7568_NR_CHANNELS * 2] = {
	-2, -14,
	-1.55, -15.5,
	-1.7, -15,
	-2.35, -12.5,
	-2.05, -13.5,
	-1.9, -14,
	-1.95, -13.5,
	-1.65, -14.5
};

 

#endif /* DAC7568_CALIBRATE_DATA_H */
