/* pru.c -- PRU driver for MicroDAQ device
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */
 
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT) 
#include <stdint.h>
#include "pru.h"

uint32_t pru_get_reg(uint8_t pru_num, uint8_t reg_num)
{
	if(reg_num >= SHARED_REG_COUNT || pru_num > 1 )
		return 0; 

	uint32_t *base_addr = (uint32_t *)(PRU_DATARAM_BASE + PRU_DATARAM_REG_OFFSET + (0x2000 * pru_num)); 
	return *(base_addr + reg_num); 
}

void pru_set_reg(uint8_t pru_num, uint8_t reg_num, uint32_t reg_value)
{
	if(reg_num >= SHARED_REG_COUNT || pru_num > 1 )
		return;  

	uint32_t *base_addr = (uint32_t *)(PRU_DATARAM_BASE + PRU_DATARAM_REG_OFFSET + (0x2000 * pru_num)); 
	*(base_addr + reg_num) = reg_value; 

	return; 
}

#endif
