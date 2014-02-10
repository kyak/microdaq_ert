#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include "pru.h"
#endif

void PRUInit( void )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#endif
}

void PRURegGetStep(unsigned char pru_reg, unsigned int *reg_value)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	*reg_value = pru_get_reg(1, pru_reg); 
#endif
}

void PRURegSetStep(unsigned char pru_reg, unsigned int reg_value)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	pru_set_reg(1, pru_reg, reg_value); 
#endif
}
