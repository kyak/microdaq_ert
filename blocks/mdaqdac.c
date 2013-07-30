#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include "mdaq_aout.h"

#endif

void DACInit( void )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	mdaq_aout_init();
#endif
}

void DACStep(unsigned char Channel, unsigned short data)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	mdaq_aout_write(Channel, data );
#endif
}

void DACTerminate(unsigned char Channel, unsigned short data)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	mdaq_aout_write(Channel, data );
#endif
}




