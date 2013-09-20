#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include "mdaq_aout.h"

#endif


void DACInit( unsigned char converter, unsigned char *channels, unsigned char channel_count, unsigned char update_mode, unsigned char update_mode_tirg )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	mdaq_aout_init();
#endif
}

void DACStep(double *dac_data, unsigned char channel_count)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
/*	mdaq_aout_write(Channel, data ); */ 
#endif
}

void DACTerminate(float *dac_data_term, unsigned char channel_count, unsigned short term_all_ch)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
/*	mdaq_aout_write(Channel, data ); */ 
#endif
}




