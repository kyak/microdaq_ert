/* mdaq_dio.h -- DIO driver for MicroDAQ device
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */ 

#ifndef MDAQ_DIO_
#define MDAQ_DIO_

#include <stdint.h>

enum dio_pin_
{
	DIO1 = 0, 
	DIO2, 
	DIO3, 
	DIO4, 
	DIO5, 
	DIO6, 
	DIO7, 
	DIO8, 
	DIO9, 
	DIO10, 
	DIO11, 
	DIO12, 
	DIO13, 
	DIO14, 
	DIO15, 
	DIO16,
	F1_KEY, 
	F2_KEY
};

void dio_set_pinmux( uint8_t dio_pin ); 
void dio_set_dir( uint8_t dio_pin, uint8_t dir);
void dio_set( uint8_t dio_pin, uint8_t value);
uint8_t dio_get( uint8_t dio_pin);

#endif /* MDAQ_DIO_ */ 
