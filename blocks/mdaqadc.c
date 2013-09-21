#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include "mdaq_ain.h"

static mdaq_ain_t ch_config[MDAQ_AIN_MAX];
#endif 

void ADCInit(unsigned char Converter, unsigned char *Channel, 
		unsigned char ChannelCount, unsigned char Range, 
		unsigned char Polarity, unsigned char Mode)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	if( Channel > MDAQ_AIN_MAX )
		return;

	mdaq_ain_init();
#if 0 
	mdaq_ain_config_init(&ch_config[Channel]);

	ch_config[Channel].ch = Channel;
	ch_config[Channel].polarity = (mdaq_ain_pol_t)Polarity;
	ch_config[Channel].range = (mdaq_ain_range_t)Range;
	ch_config[Channel].mode = (mdaq_ain_mode_t)Mode;
#endif 

#endif
}

void ADCStep(unsigned short *adc_value, double *value, unsigned char ChannelCount)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	if( Channel > MDAQ_AIN_MAX )
		return;
#if 0 
	mdaq_ain_read(&ch_config[Channel]);

	*adc_value = ch_config[Channel].adc_value;
	*value = ch_config[Channel].value_raw;
#endif 
#endif
}

