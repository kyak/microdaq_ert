#ifndef _MDAQDAC_H
#define _MDAQDAC_H

void DACInit( unsigned char converter, unsigned char *channels, unsigned char channel_count, unsigned char update_mode, unsigned char update_mode_tirg );
void DACStep(double *dac_data, unsigned char *channels, unsigned char channel_count); 
void DACTerminate(float *dac_data_term, unsigned char channel_count, unsigned short term_all_ch); 

#endif /* _MDAQDAC_H */
