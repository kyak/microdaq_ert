#ifndef _MDAQENC_H
#define _MDAQENC_H

void ENCInit(unsigned char Channel);
void ENCStep(unsigned char Channel, int *position, unsigned char *dir, unsigned char reset);

void ENC2Init( unsigned char pru_core );
void ENC2Step(unsigned char pru_core, unsigned char reset_ch1, 
        unsigned char reset_ch2, 
        unsigned char reset_ch3, 
        unsigned char reset_ch4,  
        int *pos_ch1, unsigned char *dir_ch1, 
        int *pos_ch2, unsigned char *dir_ch2, 
        int *pos_ch3, unsigned char *dir_ch3, 
        int *pos_ch4, unsigned char *dir_ch4);

#endif /* _MDAQENC_H */
