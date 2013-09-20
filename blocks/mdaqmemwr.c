#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include "mdaq_aout.h"
#endif


static float *memwr_ptr; 

void MEMWRInit( unsigned int Address, unsigned char ch_count, unsigned char *desc )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	memwr_ptr = (float *)Address; 
#endif
}

void MEMWRStep(float in1[], int ch_count)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	int count = 0; 
	for ( count = 0; count < ch_count; count++)
		*memwr_ptr++ = in1[count];	
#endif
}

void MEMWRTerminate(unsigned char Channel, unsigned short data)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	
#endif
}




