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

#define RESET_DELAY		(100)

#ifdef 	   LIDD_MODE
#include "pinmux_config_lidd.h"
#else
#include "pinmux_config_gpio.h"
#endif

static void adc_set_gpio_data_bus(void);
static inline void adc_delay( int delay);
static uint16_t	adc_gpio_bus_data_convert(uint32_t data);

static inline void adc_delay( int delay)
{
    volatile int c, d = delay;

    for(c = 0; c < d; c++ );
}

static inline uint8_t max_array( uint8_t a[], int num_elements)
{
    int i, max = -1; 

    for(i = 0; i < num_elements; i++)
    {
        if(a[i] > max)
            max = a[i];
    }
    return max; 
}

static inline void ads8568_read_bus( uint16_t *data)
{
    GPIO_setOutput( ADC_RD, GPIO_LOW );
    adc_delay(1);
    *data =  adc_gpio_bus_data_convert(GPIO_getBank(GPIO_BANK0));
    GPIO_setOutput( ADC_RD, GPIO_HIGH );
}

static void ads8568_init_gpio( void )
{
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

static inline void ads8568_start_conv( void )
{
    volatile uint32_t delay = 0;

    GPIO_setOutput( ADC_CONVST, GPIO_LOW );

    /* 100ns delay */
    for(delay = 0; delay < 5; delay++);

    GPIO_setOutput( ADC_CONVST, GPIO_HIGH );

    /* 100ns delay */
    for(delay = 0; delay < 1; delay++);

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
    /* TODO: add support for range, mode and polarity */

    uint16_t    tmp; 
    int 		ch_index = 0;
    volatile int delay = 10;

    GPIO_PinNumber_t cs;
    
    if( ch > ADS8568_CH_MAX )
        return -1; 

    /* conversion start */  
    ads8568_start_conv();

    if ( ch > 8 )
    {
        cs = ADC_CS1;
        ch -= 8;
    }
    else
        cs = ADC_CS2;

    while(GPIO_getInput(ADC_BUSY));
    /* conversion end */  

    GPIO_setOutput( cs, GPIO_LOW);
    for(ch_index = 0; ch_index < 8; ch_index++ )
    {
        if ( ch_index == ch ) 
            ads8568_read_bus(data);  
        else 
            /* dummy read */ 
            ads8568_read_bus(&tmp);  
    }
    GPIO_setOutput( cs, GPIO_HIGH);

    return 0; 
}

int ads8568_scan_ch( uint16_t *data, uint8_t *ch, uint8_t ch_count, 
        uint8_t range, uint8_t mode, uint8_t polarity )
{
    uint8_t     ch_max = 0;
    uint8_t     data_index = 0;
    uint8_t     ch_to_read[ADS8568_CH_MAX];
    uint8_t 	ch_index = 0;
    uint16_t    tmp; 
    volatile    GPIO_PinNumber_t cs;
    
    /* check parameters */ 
    if ( !ch_count || 
          ch_count > ADS8568_CH_MAX ||
          data == NULL ||
          ch == NULL )
        return -1;             

    /* start analog-to-digital conversion */
    ads8568_start_conv();

    /* find max channel */ 
    ch_max = max_array(ch, ch_count);
    if ( ch_max > ADS8568_CH_MAX )
        return -1; 

    memset((void *)ch_to_read, 0x0, sizeof(ch_to_read));    
    for ( ch_index = 0; ch_index < ch_count; ch_index++)
    {
    	if (ch[ch_index] <  ADS8568_CH_MAX)
    		ch_to_read[ch[ch_index]] = 1;
    }

    /* Wait for conversion end */
    while(GPIO_getInput(ADC_BUSY));

    /* Set CS to active*/
    GPIO_setOutput(ADC_CS2, GPIO_LOW);
    for(ch_index = 0; ch_index < ch_max; ch_index++)
    {
        if ( ch_index == 8 )
        {
            GPIO_setOutput(ADC_CS2, GPIO_HIGH);
            GPIO_setOutput(ADC_CS1, GPIO_LOW);
        }

        if( ch_to_read[ch_index] )
        {
            ads8568_read_bus(&data[data_index]); 
            data_index++; 
        }
        else 
        {
            /* dummy read */ 
            ads8568_read_bus(&tmp); 
        }
   } 

    GPIO_setOutput(ADC_CS1, GPIO_HIGH);
    GPIO_setOutput(ADC_CS2, GPIO_HIGH);

    return data_index;
}
#endif

