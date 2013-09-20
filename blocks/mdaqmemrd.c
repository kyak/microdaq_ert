#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include "mdaq_aout.h"
#endif


static float *memwr_ptr; 

void MEMRDInit( unsigned int Address, unsigned char ch_count, unsigned char *desc )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	memwr_ptr = (float *)Address; 

#endif
}

void MEMRDStep(float out1[], int ch_count)
{
	static int ptr_index = 0; 
	int count = 0; 
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	for ( count = 0; count < ch_count; count++)
		out1[count] = *(memwr_ptr + count);	
#endif
}

void MEMRDTerminate(unsigned char Channel, unsigned short data)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	
#endif
}




