/* mdaq_trig.h -- Trigger definitions for MicroDAQ device
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#ifndef MDAQ_TRIG_H
#define MDAQ_TRIG_H
#include <stdint.h> 

typedef enum mdaq_ain_trig_type_
{
    MDAQ_TRIG_DEFAULT, 
    MDAQ_TRIG_GPIO, 
    MDAQ_TRIG_LEVEL
}mdaq_trig_type_t;

typedef struct mdaq_trig_
{
    mdaq_trig_type_t    type; 
    float               level; 
    uint8_t             bellow; 
    uint8_t             gpio_bank; 
    uint8_t             gpio_pin; 
    uint8_t             gpio_state; 
}mdaq_trig_t;

#endif /* MDAQ_TRIG_H */ 
