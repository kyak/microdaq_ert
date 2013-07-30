/* gpio.c -- GPIO driver for MicroDAQ device
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */
 
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include "gpio.h"
#include <stdint.h>

#define SET         1
#define RESET       0


int16_t GPIO_setDir(GPIO_PinNumber_t pinNumber, GPIO_PortDir_t direction)
{
    /* Get the bank address from upper nibble - divide by 2 - no of banks per 32bit register */
    uint32_t bank_id = (pinNumber >> 5);
    uint32_t* gpio_handle = (uint32_t*) (GPIO_BASE + GPIO_DIR_BASE + (GPIO_BASE_OFFSET * bank_id));
    /* Get the pin */
    uint32_t pin_id  = 1 << (pinNumber & 0x1f);

    if(GPIO_OUTPUT == direction)
    {
        /* Set to OUTPUT */
        *gpio_handle &= ~pin_id;
    }
    else
    {
        /* Set to INPUT */
        *gpio_handle |= pin_id;
    }

    return 0;
}

int16_t GPIO_setOutput(GPIO_PinNumber_t pinNumber, GPIO_PinStatus_t output)
{
    /* Get the bank address from upper nibble - divide by 2 - no of banks per 32bit register */
    uint32_t bank_id = (pinNumber >> 5);
    uint32_t* gpio_handle;
    /* Get the pin */
    uint32_t pin_id  = 1 << (pinNumber & 0x1f);

    if(( output & 1 ) == 0)
    {
        gpio_handle = (uint32_t*) (GPIO_BASE + GPIO_CLR_DATA_BASE + (GPIO_BASE_OFFSET * bank_id));
        /* Set to LOW */
        *gpio_handle = pin_id;
    }
    else
    {
        gpio_handle = (uint32_t*) (GPIO_BASE + GPIO_SET_DATA_BASE + (GPIO_BASE_OFFSET * bank_id));
        /* Set to HIGH */
        *gpio_handle = pin_id;
    }

    return 0;
}

int16_t GPIO_getInput(GPIO_PinNumber_t pinNumber)
{
    uint32_t input;
    /* Get the bank address from upper nibble - divide by 2 - no of banks per 32bit register */
    uint32_t bank_id = (pinNumber >> 5);
    uint32_t* gpio_handle = (uint32_t*) (GPIO_BASE + GPIO_IN_DATA_BASE + (GPIO_BASE_OFFSET * bank_id));
    /* Get the pin */
    uint32_t pin_id  = (pinNumber & 0x1f);

    input = *gpio_handle;
    input = ( input >> pin_id ) & 1;

    return (int16_t)input;
}

int16_t GPIO_getOutput(GPIO_PinNumber_t pinNumber)
{
    uint32_t input;
    /* Get the bank address from upper nibble - divide by 2 - no of banks per 32bit register */
    uint32_t bank_id = (pinNumber >> 5);
    uint32_t* gpio_handle = (uint32_t*) (GPIO_BASE + GPIO_OUT_DATA_BASE + (GPIO_BASE_OFFSET * bank_id));
    /* Get the pin */
    uint32_t pin_id  = (pinNumber & 0x1f);

    input = *gpio_handle;
    input = ( input >> pin_id ) & 1;

    return (int16_t)input;
}

int16_t GPIO_getLastSetOutput(GPIO_PinNumber_t pinNumber)
{
    uint32_t status;
    /* Get the bank address from upper nibble - divide by 2 - no of banks per 32bit register */
    uint32_t bank_id = (pinNumber >> 5);
    uint32_t* gpio_handle = (uint32_t*) (GPIO_BASE + GPIO_OUT_DATA_BASE + (GPIO_BASE_OFFSET * bank_id));
    /* Get the pin */
    uint32_t pin_id  = (pinNumber & 0x1f);

    status = *gpio_handle;
    status = ( status >> pin_id ) & 1;

    return (int16_t)status;
}

int16_t GPIO_setEdgeTrigger(GPIO_PinNumber_t pinNumber, GPIO_EdgeType_t edgeType)
{
    /* Get the bank address from upper nibble - divide by 2 - no of banks per 32bit register */
    uint32_t bank_id = (pinNumber >> 5);
    uint32_t* gpio_handle;
    /* Get the pin */
    uint32_t pin_id  = 1 << (pinNumber & 0x1f);

    if(GPIO_RISING_EDGE == edgeType)
    {
        gpio_handle = (uint32_t*) (GPIO_BASE + GPIO_SET_RIS_TRIG_BASE + (GPIO_BASE_OFFSET * bank_id));
        /* Set to rising edge trigger */
        *gpio_handle = pin_id;
    }
    else
    {
        gpio_handle = (uint32_t*) (GPIO_BASE + GPIO_SET_FAL_TRIG_BASE + (GPIO_BASE_OFFSET * bank_id));
        /* Set to falling edge trigger */
        *gpio_handle = pin_id;
    }

    return 0;
}

int16_t GPIO_clrEdgeTrigger(GPIO_PinNumber_t pinNumber, GPIO_EdgeType_t edgeType)
{
    /* Get the bank address from upper nibble - divide by 2 - no of banks per 32bit register */
    uint32_t bank_id = (pinNumber >> 5);
    uint32_t* gpio_handle;
    /* Get the pin */
    uint32_t pin_id  = 1 << (pinNumber & 0x1f);

    if(GPIO_RISING_EDGE == edgeType)
    {
        gpio_handle = (uint32_t*) (GPIO_BASE + GPIO_CLR_RIS_TRIG_BASE + (GPIO_BASE_OFFSET * bank_id));
        /* Clear to rising edge trigger */
        *gpio_handle = pin_id;
    }
    else
    {
        gpio_handle = (uint32_t*) (GPIO_BASE + GPIO_CLR_FAL_TRIG_BASE + (GPIO_BASE_OFFSET * bank_id));
        /* Clear to falling edge trigger */
        *gpio_handle = pin_id;
    }

    return 0;
}
#endif 