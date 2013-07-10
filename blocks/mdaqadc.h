#ifndef _MDAQADC_H_
#define _MDAQADC_H_

void ADCInit(unsigned char Channel, unsigned char Polarity,
			 unsigned char Range, unsigned char Mode);

void ADCStep(unsigned char Channel, unsigned short *adc_value, float *value );

#endif /* __ADC_H */
