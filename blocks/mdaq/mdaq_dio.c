/* mdaq_dio.c -- DIO driver for MicroDAQ device
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */ 
#include "hardware.h"
#include "gpio.h"
#include "mdaq_dio.h"

typedef struct dio_config_
{
	unsigned int pin; 
	unsigned int gpio_bank; 
	unsigned int gpio_pin; 
	unsigned int pinmux; 
	unsigned int nibble; 	
}dio_config_t;

#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
static dio_config_t dio_pins[] = {
		{ DIO1, 1, 7, 16, 5 }, 
		{ DIO2, 1, 6, 16, 4 }, 
		{ DIO3, 1, 5, 16, 3 }, 
		{ DIO4, 1, 4, 16, 2 }, 
		{ DIO5, 1, 14, 17, 4 }, 
		{ DIO6, 1, 13, 17, 3 }, 
		{ DIO7, 1, 3, 16, 1 }, 
		{ DIO8, 1, 0, 15, 6 }, 
		{ DIO9, 0, 8, 14, 6 }, 
		{ DIO10, 0, 9, 14, 7 }, 
		{ DIO11, 0, 10, 15, 0 }, 
		{ DIO12, 0, 11, 15, 1 }, 
		{ DIO13, 0, 12, 15, 2 }, 
		{ DIO14, 0, 13, 15, 3 }, 
		{ DIO15, 0, 14, 15, 4 }, 
		{ DIO16, 0, 15, 15, 5 },
		{ F1_KEY, 3, 12, 9, 7 },
		{ F2_KEY, 2, 11, 9, 2 }
};
#endif 

void dio_set_pinmux( uint8_t dio_pin ) 
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	uint32_t mux_conf = 0; 
	volatile uint32_t *mux_addr = (uint32_t *)(SYS_CFG_BASE + 0x120); 

	if (  dio_pin > F2_KEY ) 
		return; 

	mux_addr += dio_pins[dio_pin].pinmux;
	mux_conf = *mux_addr; 

	mux_conf &= ~(0xf << (dio_pins[dio_pin].nibble * 4));
	mux_conf |= 0x8 << (dio_pins[dio_pin].nibble * 4);

	*mux_addr = mux_conf; 	
#endif 
}

void dio_set_dir( uint8_t dio_pin, uint8_t dir)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    unsigned int gpio_pin = ( 0x10 * dio_pins[dio_pin].gpio_bank ) | dio_pins[dio_pin].gpio_pin; 
    GPIO_setDir((GPIO_PinNumber_t)gpio_pin, (GPIO_PortDir_t)dir); 
#endif 
}

void dio_set( uint8_t dio_pin, uint8_t value) 
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    unsigned int gpio_pin = ( 0x10 * dio_pins[dio_pin].gpio_bank ) | 
			                         dio_pins[dio_pin].gpio_pin; 
    GPIO_setOutput((GPIO_PinNumber_t)gpio_pin, (GPIO_PinStatus_t)value);
#endif 
}

uint8_t dio_get( uint8_t dio_pin)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    unsigned int gpio_pin = ( 0x10 * dio_pins[dio_pin].gpio_bank ) | dio_pins[dio_pin].gpio_pin; 
    return (unsigned char)GPIO_getInput((GPIO_PinNumber_t)gpio_pin);
#endif 
}

