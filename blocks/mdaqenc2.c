#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include "mdaq_pru.h"
#include "pru_encoder_bin.h"
#endif


void ENC2Init( unsigned char pru_core )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    /* TODO: add pru core selection option */ 
    mdaq_pru_stop(pru_core); 
    mdaq_pru_load(pru_core, (const uint32_t *)pru_encoder, sizeof(pru_encoder) / 4 ); 
    mdaq_pru_start(pru_core); 

    /* enable all channels */
    mdaq_pru_reg_write(0, 0, 0xffffffff); 
#endif
}

void ENC2Step( unsigned char pru_core, unsigned char reset_ch1, 
        unsigned char reset_ch2, 
        unsigned char reset_ch3, 
        unsigned char reset_ch4,  
        int *pos_ch1, unsigned char *dir_ch1, 
        int *pos_ch2, unsigned char *dir_ch2, 
        int *pos_ch3, unsigned char *dir_ch3, 
        int *pos_ch4, unsigned char *dir_ch4)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    static int prev_pos_ch1, prev_pos_ch2, prev_pos_ch3, prev_pos_ch4;

    if ( reset_ch1 != 0 ) 
    {
        mdaq_pru_reg_write(pru_core, 1, 0); 
        *dir_ch1 = 0; 
        *pos_ch1 = 0; 
        prev_pos_ch1 = 0; 
        return;
    }

    if ( reset_ch2 != 0 ) 
    {
        mdaq_pru_reg_write(pru_core, 2, 0); 
        *dir_ch2 = 0; 
        *pos_ch2 = 0; 
        prev_pos_ch2 = 0; 
        return;
    }

    if ( reset_ch3 != 0 ) 
    {
        mdaq_pru_reg_write(pru_core, 3, 0); 
        *dir_ch3 = 0; 
        *pos_ch3 = 0; 
        prev_pos_ch3 = 0; 
        return;
    }

    if ( reset_ch4 != 0 ) 
    {
        mdaq_pru_reg_write(pru_core, 4, 0); 
        *dir_ch4 = 0; 
        *pos_ch4 = 0; 
        prev_pos_ch4 = 0; 
        return;
    }

    *pos_ch1 = mdaq_pru_reg_read(pru_core, 1); 
    if ( prev_pos_ch1 < *pos_ch1 )  
    {
        *dir_ch1 = 1; 
    }
    else if (prev_pos_ch1 > *pos_ch1) 
    {
        *dir_ch1 = 2; 
    }
    else 
        *dir_ch1 = 0; 

    *pos_ch2 = mdaq_pru_reg_read(pru_core, 2); 
    if ( prev_pos_ch2 < *pos_ch2 )  
    {
        *dir_ch2 = 1; 
    }
    else if (prev_pos_ch2 > *pos_ch2) 
    {
        *dir_ch2 = 2; 
    }
    else 
        *dir_ch2 = 0; 

    *pos_ch3 = mdaq_pru_reg_read(pru_core, 3); 
    if ( prev_pos_ch3 < *pos_ch3 )  
    {
        *dir_ch3 = 1; 
    }
    else if (prev_pos_ch3 > *pos_ch3) 
    {
        *dir_ch3 = 2; 
    }
    else 
        *dir_ch3 = 0; 

    *pos_ch4 = mdaq_pru_reg_read(pru_core, 4); 
    if ( prev_pos_ch4 < *pos_ch4 )  
    {
        *dir_ch4 = 1; 
    }
    else if (prev_pos_ch4 > *pos_ch4) 
    {
        *dir_ch4 = 2; 
    }
    else 
        *dir_ch4 = 0; 

#endif
}
