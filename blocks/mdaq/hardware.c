/* hardware.c -- hardware definitions for MicroDAQ device
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */
 
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include <stdint.h>
#include "hardware.h"

void PSC0_lPSC_enable(unsigned int PD, unsigned int LPSC_num)
{
	*(unsigned int*) (S_PSC0_MDCTL+4*LPSC_num) = (*(unsigned int*) (S_PSC0_MDCTL+4*LPSC_num) & 0xFFFFFFE0) | 0x0003;
	S_PSC0_PTCMD = 0x1<<PD;
	while( (S_PSC0_PTSTAT & (0x1<<PD) ) !=0) ; /* Wait for power state transition to finish */
	while( (*(unsigned int*)(S_PSC0_MDSTAT+4 * LPSC_num) & 0x1F) !=0x3);
}

void PSC1_lPSC_enable(unsigned int PD, unsigned int LPSC_num)
{
	*(unsigned int*) (S_PSC1_MDCTL+4*LPSC_num) = (*(unsigned int*) (S_PSC1_MDCTL+4*LPSC_num) & 0xFFFFFFE0) | 0x0003;
	S_PSC1_PTCMD = 0x1<<PD;
	while( (S_PSC1_PTSTAT & (0x1<<PD) ) !=0) ; /*Wait for power state transition to finish*/
	while( (*(unsigned int*)(S_PSC1_MDSTAT+4 * LPSC_num) & 0x1F) !=0x3);
}




int set_reg16(uint32_t base, uint8_t reg, uint16_t value)
{
	if ( base == 0 )
		return -1;

	*(uint16_t *)(base + reg) = value;
	return 0;
}

int set_reg32(uint32_t base, uint8_t reg, uint32_t value)
{

	if ( base == 0 )
		return -1;

	*(uint32_t *)(base + reg) = value;
	return 0;
}

uint16_t	 get_reg16(uint32_t base, uint8_t reg)
{

	if ( base == 0 )
		return 0;

	return *(uint16_t *)(base + reg);
}

uint32_t	 get_reg32(uint32_t base, uint8_t reg)
{
	if ( base == 0 )
		return 0;

	return *(uint32_t *)(base + reg);
}
#endif