#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include <string.h>
#include "mdaq_ai.h"
#endif 

void ADCInit(unsigned char Converter, unsigned char *Channel, 
        unsigned char ChannelCount, unsigned char Range, 
        unsigned char Polarity, unsigned char Mode)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    uint32_t range = Range, polarity = Polarity, mode = Mode; 

    if( ChannelCount > AI16 )
        return;

    range = (range == 1 ? AI_10V : AI_5V);
    polarity = (polarity == 2 ? AI_BIPOLAR : AI_UNIPOLAR);

    /* TODO: support for differential mode */
    mode = (mode == 1 ? AI_SINGLE : AI_SINGLE);

    mdaq_ai_init(Converter, range, polarity, mode);
#if 0 
    if (Converter > ADC02)
        mdaq_ai_config_ch(Channel, ChannelCount);
#endif 
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
