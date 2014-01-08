/* pru.h -- PRU driver for MicroDAQ device
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#ifndef _PRU_H_
#define _PRU_H_
#include <stdint.h>

#define PRU_DATARAM_BASE	(0x01C30000)

#define SHARED_REG_SIZE         (4)
#define SHARED_REG_COUNT        (16)
#define PRU_DATARAM_SIZE (512)
#define PRU_DATARAM_REG_OFFSET ((PRU_DATARAM_SIZE / 2) - (SHARED_REG_SIZE * SHARED_REG_COUNT))

uint32_t pru_get_reg(uint8_t pru_num, uint8_t reg_num); 
void pru_set_reg(uint8_t pru_num, uint8_t reg_num, uint32_t reg_value); 


#endif /* _PRU_H_ */
