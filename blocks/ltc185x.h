#ifndef _LTC185X_
#define _LTC185X_
#include <stdint.h> 
#include "mdaq-ain-cap.h"

int ltc185x_init( void ); 
int ltc185x_read_ch( uint16_t *data, uint8_t ch, uint8_t range,
		uint8_t mode, uint8_t polarity );

#endif /*_LTC185X_ */ 
