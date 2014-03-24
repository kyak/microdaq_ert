#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include "eqep.h"
#include "pru.h"
#include "mdaq_dio.h"
#include "pru_encoder_bin.h"
#endif


void ENCInit( unsigned char Channel )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	eqep_init(Channel);
#endif
}

void ENCStep(unsigned char Channel, int *position, unsigned char *dir, unsigned char reset)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	static int pos_prev; 
	if ( reset != 0 ) 
	{
		eqep_init(Channel);
		*dir = 0; 
		*position = 0; 
		pos_prev = 0; 
		return;
	}

	*position = eqep_get(Channel);
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

void ENC2Init( void )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)

	dio_set_pinmux(8); 
	dio_set_pinmux(9); 
	dio_set_pinmux(10); 
	dio_set_pinmux(11); 
	dio_set_pinmux(12); 
	dio_set_pinmux(13); 
	dio_set_pinmux(14); 
	dio_set_pinmux(15); 

	dio_set_dir(DIO9, 1); 
	dio_set_dir(DIO10, 1); 
	dio_set_dir(DIO11, 1); 
	dio_set_dir(DIO12, 1); 
	dio_set_dir(DIO13, 1); 
	dio_set_dir(DIO14, 1); 
	dio_set_dir(DIO15, 1); 
	dio_set_dir(DIO16, 1); 

	pru_stop(0); 
	pru_load(0, (const uint32_t *)pru_encoder, sizeof(pru_encoder) / 4 ); 
	pru_run(0); 
#endif
}

void ENC2Step(unsigned char reset_ch1, 
        unsigned char reset_ch2, 
        unsigned char reset_ch3, 
        unsigned char reset_ch4,  
        int *pos_ch1, unsigned char *dir_ch1, 
        int *pos_ch2, unsigned char *dir_ch2, 
        int *pos_ch3, unsigned char *dir_ch3, 
        int *pos_ch4, unsigned char *dir_ch4)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
	pru_set_reg(0, 0, 0xffffffff); 
	*pos_ch1 = pru_get_reg(0, 1); 
	*pos_ch2 = pru_get_reg(0, 2); 
	*pos_ch3 = pru_get_reg(0, 3); 
	*pos_ch4 = pru_get_reg(0, 4); 
#endif
}
