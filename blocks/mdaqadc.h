#ifndef __ADC_H
#define __ADC_H

void ADCInit(unsigned char Channel, unsigned char Polarity,
			 unsigned char Range, unsigned char Mode);

void ADCStep(unsigned char Channel, unsigned short *adc_value, float *value );

#endif /* __ADC_H */
