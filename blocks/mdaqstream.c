#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include "mdaq_stream.h"
#endif

void OutStreamInit(unsigned char stream_ch, unsigned char vector_size)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	mdaq_stream_alloc(stream_ch, STREAM_OUT); 
#endif 
}
void OutStreamStep(double *data, unsigned char stream_ch, unsigned char vector_size)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	mdaq_stream_write( stream_ch, (uint8_t *)data, sizeof(double) * vector_size); 	
#endif 
}
void OutStreamTerminate(unsigned char stream_ch)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	mdaq_stream_dealloc(stream_ch); 
#endif 
}

