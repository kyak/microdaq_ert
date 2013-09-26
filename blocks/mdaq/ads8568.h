/* ads8568.c -- Adc driver for MicroDAQ device
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#include "gpio.h"

#ifndef ADS8568_H_
#define ADS8568_H_

#define		LCD_D0		GP1_7
#define		LCD_D1		GP1_6
#define		LCD_D2		GP1_5
#define		LCD_D3		GP1_4
#define		LCD_D4		GP1_14
#define		LCD_D5		GP1_13
#define		LCD_D6		GP1_3
#define		LCD_D7		GP1_0
#define		LCD_D8		GP0_8
#define		LCD_D9		GP0_9
#define		LCD_D10		GP0_10
#define		LCD_D11		GP0_11
#define		LCD_D12		GP0_12
#define		LCD_D13		GP0_13
#define		LCD_D14		GP0_14
#define		LCD_D15		GP0_15
#define 	ADC_RD		GP1_8

#define 	ADC_CS1		GP3_10
#define 	ADC_CS2		GP3_9
#define 	ADC_CONVST	GP2_12
#define 	ADC_BUSY	GP2_15
#define 	ADC_HW_SW	GP1_10
#define 	ADC_WR		GP1_9
#define 	ADC_RESET	GP2_4

#define 	ADS8568_CH_MAX	(16)

typedef enum
{
	ADC_LIDD_MODE = 0,
	ADC_GPIO_MODE = 1
}adc_mode_t;


typedef struct
{
	adc_mode_t	mode;
	uint8_t		ch_config;
	int16_t		*data;
	uint32_t 	freq;
}adc_config_t;

int ads8568_init( void );

int ads8568_read_ch( uint16_t *data, uint8_t ch, uint8_t range,
        uint8_t mode, uint8_t polarity );

int ads8568_scan_ch( uint16_t *data, uint8_t *ch, uint8_t ch_count, 
        uint8_t range, uint8_t mode, uint8_t polarity );

#endif /* ADS8568_H_ */
