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

int pru_load(uint8_t pru_num, const uint32_t *pru_code, uint32_t code_size);
int pru_run(uint8_t pru_num);
int pru_stop (uint8_t pru_num);

uint32_t pru_get_reg(uint8_t pru_num, uint8_t reg_num); 
void pru_set_reg(uint8_t pru_num, uint8_t reg_num, uint32_t reg_value); 

#endif /* _PRU_H_ */

