#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include "mdaq_pru.h"
#endif


void PRURegGetStep(unsigned char pru_core, unsigned char pru_reg, unsigned int *reg_value)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	*reg_value = mdaq_pru_reg_read(pru_core, pru_reg); 
#endif
}

void PRURegSetStep(unsigned char pru_core, unsigned char pru_reg, unsigned int reg_value)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	mdaq_pru_reg_write(pru_core, pru_reg, reg_value); 
#endif
}
