/* dac7568.h -- DAC for MicroDAQ device
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#ifndef DAC7568_H
#define DAC7568_H

#include <stdint.h>
#define DAC7568_RESOLUTION 		(12)

#define DAC_ZERO_SCALE			(0)
#define DAC_MID_SCALE			(1)
#define DAC_FULL_SCALE			(2)

void dac7568_init(uint8_t mode, uint8_t init_state);
void dac7568_write_data(uint8_t ch, float value, uint8_t mode);
int dac7568_write_multi(uint8_t ch[], uint8_t ch_count, uint16_t data[], uint32_t mode);

#endif /* DAC7568_H */
