/* dac7568.c -- DAC for MicroDAQ device
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */
 
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#include "dac7568_calibrate_data.h"

#include "gpio.h"
#include "spi.h"
#include "utils.h"

#define DAC_LOAD_NONE			(0x0ff00000)
#define DAC_LOAD_ALL			(0x0fffff00)
#define DAC_SOFT_RESET			(0x07000000)
#define DAC_IGNORE_CLR			(0x05000003)
#define DAC_IGNORE_LDAC			(0x060000ff)
#define DAC_POWER_UP			(0x040000ff)
#define	DAC_REF_ON			(0x08000001)
#define	DAC_REF_OFF			(0x08000000)

#define CMD_WR_IN_REG			(0x00000000)
#define CMD_WR_UP_REGS			(0x01000000)
#define CMD_WR_UP_ALL_REGS		(0x02000000)

#define CMD_SYNC_MODE 			(CMD_WR_IN_REG)

#define CMD_WR_CREAR_CODE_REG 		(0x05000000)
#define CMD_SET_INIT_SCALE		(0x05000000)
#define CMD_CLR_TO_MID_SCALE 		(0x05000001)
#define CMD_CLR_TO_FULL_SCALE		(0x05000002)
#define CMD_IGNORE_CLR_PIN		(0x05000003)

#define	CMD_WR_LDAC_REG			(0x06000000)
#define CMD_SOFT_RESET			(0x07000000)
#define CMD_WR_IN_REG_UP_ALL_REGS 	(0x02000000)
#define CMD_WR_IN_REG_AND_UP 		(0x03000000)
#define CMD_PWR_UP_DACS			(0x04000000)

#define CMD_PWR_DOWN_1K			(0x04000100)
#define CMD_PWR_DOWN_100K		(0x04000200)
#define CMD_PWR_DOWN_HIGH_Z		(0x04000300)

#define	CMD_REF_STATIC_OFF		(0x08000000)
#define CMD_REF_STATIC_ON		(0x08000001)
#define CMD_REF_FLEX_ON			(0x09080000)
#define CMD_REF_ON			(0x09A00000)		/* Power up internal reference all the time regardless of state of DACs - flexible mode; */
#define CMD_REF_OFF			(0x09B00000)		/* Power down internal reference all the time regardless of state of DACs */
#define CMD_FLEX_TO_STATIC		(0x09000000)

#define DAC7568_ASYNC_MODE		(1 << 1)
#define DAC7568_SYNC_MODE		(1 << 2)

#define DAC7568_SYNC			GP4_1
#define DAC7568_LDAC			GP4_2
#define DAC7568_CLR			GP4_9
#define DAC7568_EN			GP4_11

#define ANALOG_EN			GP5_11

#define DAC7568_SPI_FREQ		(40000000)
#define DAC7568_SPI_POLARITY		(1)
#define DAC7568_SPI_PHRASE		(1)

#define SPI_XFER_TO_SYNC_DELAY 		(10)
#define LDAC_PULSE_DELAY		(1)

static uint8_t dac7568_mode = DAC7568_ASYNC_MODE;

static inline void dac7568_en( void )
{
	if (GPIO_getOutput(DAC7568_EN) != GPIO_HIGH)
	{
		spi_set_freq(DAC7568_SPI_FREQ);
		spi_set_polarity(DAC7568_SPI_POLARITY);
		spi_set_phrase(DAC7568_SPI_PHRASE);
		GPIO_setOutput(DAC7568_EN, GPIO_HIGH);
	}
}

static void dac7568_setup_cmd(uint32_t *cmd, uint8_t ch, uint16_t data)
{
	uint8_t *cmd_ptr = (uint8_t *)cmd;

	if ( cmd == NULL )
		return;

	cmd_ptr[2] = ((ch << 4) & 0xff)  + ((data >> 8) & 0xf);
	cmd_ptr[1] = 0xff & data;
	return;
}

static int dac7568_write_spi( uint32_t cmd, uint32_t cmd_len)
{
	unsigned long flags = SPI_XFER_BEGIN;
	int ret;
	uint32_t tmp = 0;

	tmp = (cmd << 16) | ((cmd >> 16) & 0xffff);

	flags |= SPI_XFER_END;

	ret = spi_xfer(cmd_len * 8, &tmp, NULL, flags);
	if (ret) {
		return -1;
	}
	return ret;
}

static void dac7568_write_cmd(uint32_t cmd)
{
	GPIO_setOutput(DAC7568_SYNC, GPIO_LOW);
	dac7568_write_spi(cmd, sizeof(cmd));

	/* TODO: this delay should be based on cpu frequency */ 
	delay2(SPI_XFER_TO_SYNC_DELAY); 

	GPIO_setOutput(DAC7568_SYNC, GPIO_HIGH);

	return;
}
/* TODO: move to mdaq_aout.c */
/* TODO: do the dac calibration in a proper way */
#if 0 
static uint16_t dac7568_calibrate_data(uint8_t ch, uint16_t data)
{

	float x;
	x = (float)data * 0.00488281;
	x -= 10.0;

	if (ch > 7)
		return data;

	/* Calibration - linear function */
	data += (x * calibrate_data[(ch * 2)]) + calibrate_data[(ch * 2) + 1];

	if (data > 4095)
		data = 4095;

	return data;
}
#endif 
static int dac7568_write(uint32_t cmd, uint8_t ch, uint16_t data)
{
	dac7568_en();

	/* TODO:  */
	// data = dac7568_calibrate_data(ch, data);

	switch(cmd)
	{
		case CMD_WR_IN_REG:
		case CMD_WR_UP_REGS:
		case CMD_WR_IN_REG_UP_ALL_REGS:
		case CMD_WR_IN_REG_AND_UP:
			dac7568_setup_cmd(&cmd, ch, data);
			dac7568_write_cmd(cmd);
		break;

		case CMD_WR_LDAC_REG:
		case CMD_PWR_UP_DACS:
		case CMD_PWR_DOWN_1K:
		case CMD_PWR_DOWN_100K:
		case CMD_PWR_DOWN_HIGH_Z:
			dac7568_write_cmd(cmd);
		break;

		case CMD_WR_CREAR_CODE_REG:
		case CMD_CLR_TO_MID_SCALE:
		case CMD_CLR_TO_FULL_SCALE:
		case CMD_IGNORE_CLR_PIN:
		case CMD_SOFT_RESET:
		case CMD_REF_STATIC_OFF:
		case CMD_REF_STATIC_ON:
		case CMD_REF_FLEX_ON:
 		case CMD_REF_ON:
		case CMD_REF_OFF:
		case CMD_FLEX_TO_STATIC:
			dac7568_write_cmd(cmd);
		break;

		default:
			return -1;
	}
	return 0;
}

int dac7568_write_multi(uint8_t ch[], uint8_t ch_count, uint16_t data[])
{
	int ch_index;
	static int first_time = 1;
	uint32_t cmd = CMD_WR_LDAC_REG;

	if( ch_count > 8)
		return -1;

	if (dac7568_mode & DAC7568_SYNC_MODE)
	{
		/* setup channels for simultaneous update only once */
		if ( first_time )
		{
			cmd |= 0xff;
			for( ch_index = 0; ch_index < ch_count; ch_index++ )
				cmd &=	~(1 <<  ch[ch_index]);

			dac7568_write_cmd(cmd);
			first_time = 0; 
		}

		for( ch_index = 0; ch_index < ch_count; ch_index++ )
			dac7568_write(CMD_SYNC_MODE, ch[ch_index], data[ch_index]);

		GPIO_setOutput(DAC7568_LDAC, GPIO_LOW);
		/* Minor delay to have 80ns pulse */ 
		delay2(LDAC_PULSE_DELAY); 
		GPIO_setOutput(DAC7568_LDAC, GPIO_HIGH);
	}
	else
	{
		for( ch_index = 0; ch_index < ch_count; ch_index++ )
			dac7568_write(CMD_WR_IN_REG, ch[ch_index], data[ch_index]);
	}
	return 0;
}

void dac7568_write_data(uint8_t ch, uint16_t value)
{
	dac7568_write(CMD_WR_IN_REG, ch, value);
}

void dac7568_set_mode( uint8_t mode )
{
	if ( dac7568_mode != mode )
	{
		if ( mode == DAC7568_ASYNC_MODE)
			dac7568_write_cmd( DAC_IGNORE_LDAC );

		dac7568_mode = mode;
	}
}

void dac7568_init(uint8_t mode, uint8_t init_state)
{
	spi_setup_bus(DAC7568_SPI_FREQ, DAC7568_SPI_POLARITY, DAC7568_SPI_PHRASE);

	/* Enable analog section */
	GPIO_setDir(ANALOG_EN,    GPIO_OUTPUT);
	GPIO_setOutput(ANALOG_EN, GPIO_LOW);

	GPIO_setDir(DAC7568_LDAC, GPIO_OUTPUT);
	GPIO_setOutput(DAC7568_LDAC,
			( mode == DAC7568_SYNC_MODE ? GPIO_HIGH : GPIO_LOW) );

	GPIO_setDir(DAC7568_CLR, GPIO_OUTPUT);

	/* Enable DAC7568 converter */
	GPIO_setDir(DAC7568_EN, GPIO_OUTPUT);
	GPIO_setOutput(DAC7568_EN, GPIO_HIGH);

	GPIO_setDir(DAC7568_SYNC, GPIO_OUTPUT);
	GPIO_setOutput(DAC7568_SYNC, GPIO_HIGH);

	dac7568_write_cmd( DAC_SOFT_RESET );

	GPIO_setOutput(DAC7568_CLR, GPIO_HIGH);
	dac7568_write_cmd( CMD_SET_INIT_SCALE |
			(init_state < 4 ? init_state : 0) );
	GPIO_setOutput(DAC7568_CLR, GPIO_LOW);


	dac7568_write_cmd( DAC_POWER_UP );
	dac7568_write_cmd( DAC_REF_ON );

	dac7568_set_mode(mode);
}

#endif
