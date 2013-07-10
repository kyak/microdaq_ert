#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include "dac7568.h"
#include "mdaq-aout.h"

/* TODO: sync/async mode */
/* TODO: differential mode */
/* TODO: CLR and LDAC */

int mdaq_aout_init( void )
{
    dac7568_init( MDAQ_AOUT_ASYNC_MODE );
    return 0;
}

int mdaq_aout_write(uint8_t ch, uint16_t data )
{
	dac7568_write_ch(ch, data);

	return 0;
}
#endif

