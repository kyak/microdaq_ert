/* ltc185x.h -- Adc driver for MicroDAQ device
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#ifndef _LTC185X_
#define _LTC185X_
#include <stdint.h> 
#include "mdaq_ain_cap.h"

int ltc185x_init( void ); 
int ltc185x_read_ch( uint16_t *data, uint8_t ch, uint8_t range,
		uint8_t mode, uint8_t polarity );

#endif /*_LTC185X_ */ 
