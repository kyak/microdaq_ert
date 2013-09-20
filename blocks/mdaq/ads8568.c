/* ads8568.c -- Adc driver for MicroDAQ device
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include <stdint.h>
#include <string.h>

#include "ads8568.h"
#include "gpio.h"
#include "hardware.h"

#ifdef 	   LIDD_MODE
#include "pinmux_config_lidd.h"
#else
#include "pinmux_config_gpio.h"
#endif

static void adc_set_gpio_data_bus(void);

static void ads8568_init_gpio( void )
{
	/* set direction of gpio */
	/* TODO: */
	adc_set_gpio_data_bus();

	GPIO_setDir( ADC_CS1,	GPIO_OUTPUT );
	GPIO_setDir( ADC_CS2, 	GPIO_OUTPUT );
	GPIO_setDir( ADC_CONVST,GPIO_OUTPUT );
	GPIO_setDir( ADC_HW_SW, GPIO_OUTPUT );
	GPIO_setDir( ADC_WR,	GPIO_OUTPUT );
	GPIO_setDir( ADC_RESET, GPIO_OUTPUT );

	GPIO_setDir( ADC_BUSY, 	GPIO_INPUT	);

	/* set initial state of gpio */
	GPIO_setOutput( ADC_CS1, 	GPIO_HIGH );
	GPIO_setOutput( ADC_CS2, 	GPIO_HIGH );
	GPIO_setOutput( ADC_CONVST,	GPIO_LOW  );

	/* low - hardware mode selected, high - software */
	GPIO_setOutput( ADC_HW_SW, 	GPIO_LOW );

	/* enable internal reference voltage */
	GPIO_setOutput( ADC_WR, 	GPIO_HIGH );

	/* disable reset signal */
	GPIO_setOutput( ADC_RESET, 	GPIO_LOW );

	return;
}

static void ads8568_reset( void )
{

#define RESET_DELAY		(10)

	volatile uint32_t delay = 0;

	GPIO_setOutput( ADC_RESET, GPIO_LOW );

	/* 100ns delay */
	for(delay = 0; delay < RESET_DELAY; delay++);

	GPIO_setOutput( ADC_RESET, GPIO_HIGH );

	/* 100ns delay */
	for(delay = 0; delay < RESET_DELAY; delay++);

	GPIO_setOutput( ADC_RESET, GPIO_LOW );

}
static void ads8568_init_pinmux( void )
{
	SYS_PINMUX9  = PINMUX9_VALUE;
	SYS_PINMUX11 = PINMUX11_VALUE;
	SYS_PINMUX14 = PINMUX14_VALUE;
	SYS_PINMUX15 = PINMUX15_VALUE;
	SYS_PINMUX16 = PINMUX16_VALUE;
	SYS_PINMUX17 = PINMUX17_VALUE;

	return;
}

#ifdef ADS8568_DEBUG
static void adc_gpio_test( adc_config_t *config)
{
	GPIO_setOutput( ADC_CS1, 	GPIO_HIGH );
	GPIO_setOutput( ADC_CS1, 	GPIO_LOW );

	GPIO_setOutput( ADC_CS2, 	GPIO_HIGH );
	GPIO_setOutput( ADC_CS2, 	GPIO_LOW );

	GPIO_setOutput( ADC_CONVST,	GPIO_LOW  );
	GPIO_setOutput( ADC_CONVST,	GPIO_HIGH );

	GPIO_setOutput( ADC_HW_SW, 	GPIO_LOW );
	GPIO_setOutput( ADC_HW_SW, 	GPIO_HIGH );

	return;
}

static void adc_convst_test( void )
{
	GPIO_setOutput( ADC_CONVST,	GPIO_LOW  );
	GPIO_setOutput( ADC_CONVST,	GPIO_HIGH );
	/* delay */
	GPIO_setOutput( ADC_CONVST,	GPIO_HIGH );
	GPIO_setOutput( ADC_CONVST,	GPIO_HIGH );
	GPIO_setOutput( ADC_CONVST,	GPIO_LOW  );

}
#endif

static void adc_set_gpio_data_bus(void)
{
	GPIO_setDir(LCD_D0, GPIO_INPUT);
	GPIO_setDir(LCD_D1, GPIO_INPUT);
	GPIO_setDir(LCD_D2, GPIO_INPUT);
	GPIO_setDir(LCD_D3, GPIO_INPUT);
	GPIO_setDir(LCD_D4, GPIO_INPUT);
	GPIO_setDir(LCD_D5, GPIO_INPUT);
	GPIO_setDir(LCD_D6, GPIO_INPUT);
	GPIO_setDir(LCD_D7, GPIO_INPUT);
	GPIO_setDir(LCD_D8, GPIO_INPUT);
	GPIO_setDir(LCD_D9, GPIO_INPUT);
	GPIO_setDir(LCD_D10, GPIO_INPUT);
	GPIO_setDir(LCD_D11, GPIO_INPUT);
	GPIO_setDir(LCD_D12, GPIO_INPUT);
	GPIO_setDir(LCD_D13, GPIO_INPUT);
	GPIO_setDir(LCD_D14, GPIO_INPUT);
	GPIO_setDir(LCD_D15, GPIO_INPUT);

	GPIO_setDir(ADC_RD,  GPIO_OUTPUT);

	return;
}

static void adc_start_conv( void )
{
	volatile uint32_t delay = 0;

	GPIO_setOutput( ADC_CONVST, GPIO_LOW );

	/* 100ns delay */
	for(delay = 0; delay < 2; delay++);

	GPIO_setOutput( ADC_CONVST, GPIO_HIGH );

	/* 100ns delay */
	// for(delay = 0; delay < 2; delay++);

	GPIO_setOutput( ADC_CONVST, GPIO_LOW );
	return;
}

static uint16_t	adc_gpio_bus_data_convert(uint32_t data)
{
	uint16_t 	out = 0;
	/* TODO: remove IF statments */ 
#if 0 
	out |= ((1 << (16 + PIN7)) & data) << 0;
	out |= ((1 << (16 + PIN6)) & data) << 1;
	out |= ((1 << (16 + PIN5)) & data) << 2;
	out |= ((1 << (16 + PIN4)) & data) << 3;
	out |= ((1 << (16 + PIN14))& data) << 4;
	out |= ((1 << (16 + PIN13))& data) << 5;
	out |= ((1 << (16 + PIN3)) & data) << 6;
	out |= ((1 << (16 + PIN0)) & data) << 7;
#endif
 
	if ((1 << (16 + PIN7))  & data) out  |= (1 << 0);
	if ((1 << (16 + PIN6))  & data) out  |= (1 << 1);
	if ((1 << (16 + PIN5))  & data) out  |= (1 << 2);
	if ((1 << (16 + PIN4))  & data) out  |= (1 << 3);
	if ((1 << (16 + PIN14)) & data) out  |= (1 << 4);
	if ((1 << (16 + PIN13)) & data) out  |= (1 << 5);
	if ((1 << (16 + PIN3))  & data) out  |= (1 << 6);
	if ((1 << (16 + PIN0))  & data) out  |= (1 << 7);

	out |= (uint16_t)(data & 0x0000ff00);

	return out;
}

static int adc_read( uint8_t ch_num, adc_config_t *config )
{
	int 		ch = 0;
	uint32_t	adc_data[8];
	GPIO_PinNumber_t cs;

	if ( ch_num > 8 )
	{
		cs = ADC_CS1;
		ch_num -= 8;
	}
	else
		cs = ADC_CS2;

	adc_start_conv();

	while(GPIO_getInput(ADC_BUSY));

	GPIO_setOutput( cs, GPIO_LOW);

	for(ch = 0; ch < 8; ch++ )
	{
		GPIO_setOutput( ADC_RD, GPIO_LOW );
		adc_data[ch] = GPIO_getBank(GPIO_BANK0);
		GPIO_setOutput( ADC_RD, GPIO_HIGH );
	}
	GPIO_setOutput( cs, GPIO_HIGH);

	return (int16_t)adc_gpio_bus_data_convert(adc_data[ch_num]);
}

int ads8568_init( void )
{
	ads8568_init_pinmux();
	ads8568_init_gpio();
	ads8568_reset();

    return 0;
}

int ads8568_read_ch( uint16_t *data, uint8_t ch, uint8_t range,
		uint8_t mode, uint8_t polarity )
{
    volatile uint8_t cmd;
    adc_config_t conf;

    memset((void*)&conf, 0x0, sizeof(adc_config_t));

    *data =  adc_read( ch, &conf);

    return 0;
}
#endif




