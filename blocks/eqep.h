

#ifndef EQEP_H_
#define EQEP_H_

#include <stdint.h>

#define EQEP0_BASE		(0x01f09000)
#define EQEP1_BASE		(0x01f0A000)

#define EQEP_POSCNT		(0x0)
#define EQEP_POSINIT	(0x4)
#define EQEP_POS_MAX	(0x8)
#define EQEP_CTL		(0x2A)

#define EQEP_CTL_VAL 	(0x1008)

#define EQEP_CNT_INIT_VALUE ( 0x80000000)


int32_t eqep_get( uint8_t eqep_num );
int32_t eqep_init( uint8_t eqep_num);


#endif /* EQEP_H_ */
