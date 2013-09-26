#ifndef _MDAQADC_H_
#define _MDAQADC_H_

void ADCInit(unsigned char Converter, unsigned char *Channel, 
		unsigned char ChannelCount, unsigned char Range, 
		unsigned char Polarity, unsigned char Mode);

void ADCStep(unsigned short *adc_value, double *value, 
		unsigned char *Channel, unsigned char ChannelCount);

#endif /* __ADC_H */
