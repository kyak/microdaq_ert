#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include "mdaq_ain.h"

static mdaq_ain_t ch_config;
#endif 

void ADCInit(unsigned char Converter, unsigned char *Channel, 
		unsigned char ChannelCount, unsigned char Range, 
		unsigned char Polarity, unsigned char Mode)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)

	if( ChannelCount > MDAQ_AIN_MAX )
		return;

	mdaq_ain_init(Converter);

	mdaq_ain_config_init(&ch_config);

	ch_config.polarity = (mdaq_ain_pol_t)Polarity;
	ch_config.range = (mdaq_ain_range_t)Range;
	ch_config.mode = (mdaq_ain_mode_t)Mode;
#endif
}

void ADCStep(unsigned short *adc_value, double *value, 
		unsigned char *Channel, unsigned char ChannelCount)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	int count;
	float data[MDAQ_AIN_MAX];
	if( ChannelCount > MDAQ_AIN_MAX )
		return;
	
	mdaq_ain_scan(&ch_config, Channel, ChannelCount, adc_value, data);  

	for (count = 0; count < ChannelCount; count++)
		value[count] = (double)data[count]; 
#endif
}

