#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include "mdaq_aout.h"
static unsigned char aout_channels[MDAQ_AOUT_MAX]; 
#endif


void DACInit( unsigned char converter, unsigned char *channels, unsigned char channel_count, unsigned char update_mode, unsigned char update_mode_tirg )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	mdaq_aout_init(converter, AOUT_SYNC);

	if ( channel_count > MDAQ_AOUT_MAX )
		channel_count = MDAQ_AOUT_MAX; 

	memcpy((void *)aout_channels, (void *)channels, channel_count); 
	return; 
#endif
}

void DACStep(double *dac_data, unsigned char channel_count)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)

{
	int count; 
	float data[MDAQ_AOUT_MAX]; 
	
	if ( channel_count > MDAQ_AOUT_MAX)
		return; 

	for( count = 0; count < channel_count; count++)
		data[count] = dac_data[count]; 

	mdaq_aout_write_multi( aout_channels, channel_count, data, AOUT_SYNC );
	
	return;
}
#endif
}

void DACTerminate(float *dac_data_term, unsigned char channel_count, unsigned short term_all_ch)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	int count; 
	float term_voltage[] = {0, 0, 0, 0, 0, 0, 0, 0};
	unsigned char ch_config[] = {0, 1, 2, 3, 4, 5, 6, 7};
	
	if ( term_all_ch )
	{
		if ( dac_data_term[0] != 0 )
		{
			for(count = 0; count < MDAQ_AOUT_MAX; count++ ) 
			{
				term_voltage[count] = dac_data_term[0]; 
			}
		}
		mdaq_aout_write_multi(ch_config, sizeof(ch_config), term_voltage, AOUT_SYNC );
	}
	else
	{
		mdaq_aout_write_multi(ch_config, channel_count, dac_data_term, AOUT_SYNC );
	}
	return; 
#endif
}

