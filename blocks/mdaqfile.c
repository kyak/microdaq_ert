#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include <string.h>
#include <stdio.h>
#include "mdaq_file.h"
#endif

#define OUT_BUFFER_SIZE		(0x4000)
static char out_buffer[OUT_BUFFER_SIZE];

void ToFileInit(char *file_name, unsigned char mode, unsigned long buf_len, unsigned char ch, unsigned char type)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    mdaq_file_init();
    mdaq_file_open(file_name,  O_CREAT | (mode == 1 ? O_TRUNC : O_APPEND ) | O_WRONLY | O_DIRECT);
    memset((void *)out_buffer, 0, sizeof(out_buffer)); 
#endif 
}

void ToFileStep(double *data, unsigned long buf_len, unsigned char ch, unsigned char type)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    int vector_idx = 0; 
    static int out_buffer_index = 0;
    static int buf_idx = 0; 

    if ( type == 1 )
    {	
        for(vector_idx = 0; vector_idx < ch - 1; vector_idx++)
            out_buffer_index += sprintf(out_buffer + out_buffer_index, "%f\t", data[vector_idx] );

        out_buffer_index += sprintf(out_buffer + out_buffer_index, "%f\n", data[vector_idx] );
        buf_idx++; 

        if ( buf_idx >= buf_len ) 
        {
            out_buffer[out_buffer_index + 1] = 0x0; 

            mdaq_file_write(1, out_buffer, out_buffer_index);
            out_buffer_index = 0;
            buf_idx = 0;
        }
    }
    else
    {
        memcpy((void *)(out_buffer + out_buffer_index), (void *)data, sizeof(double) * ch);

        out_buffer_index += sizeof(double) * ch;
        buf_idx++; 

        if ( buf_idx >= buf_len ) 
        {
            mdaq_file_write(1, out_buffer, out_buffer_index);
            out_buffer_index = 0;
            buf_idx = 0;
        }
    }
#endif 
}

void ToFileTerminate(void)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    mdaq_file_close(1);
#endif 
}

void FromFileInit(char *file_name, unsigned char mode, unsigned long buf_len, unsigned char ch, unsigned char type)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#endif 
}

void FromFileStep(double *data, unsigned long buf_len, unsigned char ch, unsigned char type)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#endif 
}

void FromFileTerminate(void)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#endif 
}

