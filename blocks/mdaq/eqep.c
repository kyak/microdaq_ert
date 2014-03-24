/* eqep.c -- Encoder driver for MicroDAQ device
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */
 
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)

#include <stdint.h>
#include "utils.h"
#include "eqep.h"

static inline uint32_t get_eqep_base( uint8_t num )
{
	uint32_t 	base = 0;
	if ( num == 0 )
		base = EQEP0_BASE;
	else if( num == 1)
		base = EQEP1_BASE;

	return base;
}


int eqep_init( uint8_t eqep_num)
{

	uint32_t eqep_base = get_eqep_base( eqep_num );
	if ( eqep_base == 0 )
		return 0;

	/* reset eqep */
	raw_write16( 0x0, eqep_base + EQEP_CTL);
	/* set max position */
	raw_write32( 0xffffffff, eqep_base + EQEP_POS_MAX);
	/* set half of the counter range */
	raw_write32( EQEP_CNT_INIT_VALUE, eqep_base + EQEP_POSINIT);
	/* set initial value */
	raw_write32( EQEP_CNT_INIT_VALUE, eqep_base + EQEP_POSCNT);
	/* release from reset */
	raw_write16( EQEP_CTL_VAL, eqep_base + EQEP_CTL );

	return 0;
}

int32_t eqep_get( uint8_t eqep_num )
{
	uint32_t eqep_base = get_eqep_base( eqep_num );
	if ( eqep_base == 0 )
		return 0;

	uint32_t eqep_cnt = raw_read32(eqep_base + EQEP_POSCNT);
	return (int32_t)(eqep_cnt - EQEP_CNT_INIT_VALUE);
}
#endif 

