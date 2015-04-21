#ifndef __MDAQ_PRU_
#define __MDAQ_PRU_


void PRURegGetStep(unsigned char pru_core, unsigned char pru_reg, unsigned int *reg_value);
void PRURegSetStep(unsigned char pru_core, unsigned char pru_reg, unsigned int reg_value);

#endif /* __MDAQ_PRU_ */