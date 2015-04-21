#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include "mdaq_enc.h"
#endif

void ENCInit( unsigned char Channel )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    /* TODO: add initial posistion in ENC block */ 
    mdaq_enc_init(Channel, 0);
#endif
}

void ENCStep(unsigned char Channel, int *position, unsigned char *dir, unsigned char reset)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    static int pos_prev; 
    if ( reset != 0 ) 
    {
        mdaq_enc_init(Channel, 0);
        *dir = 0; 
        *position = 0; 
        pos_prev = 0; 
        return;
    }

    *position = mdaq_enc_read(Channel);
    if ( pos_prev < *position )  
    {
        *dir = 1; 
    }
    else if (pos_prev > *position ) 
    {
        *dir = 2; 
    }
    else 
        *dir = 0; 

    pos_prev = *position; 
#endif
}

