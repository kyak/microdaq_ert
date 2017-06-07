#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include <string.h>
#include "mdaq_ai.h"
#endif 

void ADCInit(unsigned char Converter, unsigned char *Channel, 
        unsigned char ChannelCount, unsigned char Range, 
        unsigned char Polarity, unsigned char Mode)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    uint32_t range, polarity, mode; 

    if( ChannelCount > AI16 )
        return;

	range = 1 << (Range - 1);
    range = (range == 1 ? AI_10V : AI_5V);
    polarity = (Polarity == 2 ? AI_BIPOLAR : AI_UNIPOLAR);
    mode = (Mode == 1 ? AI_SINGLE : AI_DIFF);

    mdaq_ai_init(Converter, range, polarity, mode);

    if (Converter > ADC02 && Converter < ADC06)
        mdaq_ai_config_ch(Channel, ChannelCount);

#endif
}

void ADCStep(unsigned short *adc_value, double *value, 
        unsigned char *Channel, unsigned char ChannelCount)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    int count;
    float data[AI16];

    mdaq_ai_read(Channel, ChannelCount, adc_value, data);	

    for (count = 0; count < ChannelCount; count++)
        value[count] = (double)data[count]; 
#endif
}
#if 0 
int mdaq_ai_init(uint8_t converter, uint32_t range, uint32_t polarity, uint32_t mode);
int mdaq_ai_config_ch(uint8_t ch[], uint8_t ch_count);
int mdaq_ai_read(uint8_t ch[], uint8_t ch_count, uint16_t *adc_value, float *value);
#endif 
