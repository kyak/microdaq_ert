#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include "eqep.h"
#endif


void ENCInit( unsigned char Channel )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	eqep_init(Channel);
#endif
}

void ENCStep(unsigned char Channel, int *position)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	*position = eqep_get(Channel);
#endif
}
