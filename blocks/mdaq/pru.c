/* pru.c -- PRU driver for MicroDAQ device
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT) 
#include <stdint.h>
#include "pru.h"

#define PRU_DATARAM_BASE	(0x01C30000)
#define PRU0_DATARAM		(0x01C30000)
#define PRU0_PROGRAM	  	(0x01C38000)

#define PRU1_DATARAM		(0x01C32000)
#define PRU1_PROGRAM		(0x01C3C000)

#define PRU0_REGS               (0x01C37000u)
#define PRU1_REGS               (0x01C37800u)

#define PRU_PROGRAM_SIZE    	(0x1000)

#define SHARED_REG_SIZE         (4)
#define SHARED_REG_COUNT        (16)
#define PRU_DATARAM_SIZE (512)
#define PRU_DATARAM_REG_OFFSET ((PRU_DATARAM_SIZE / 2) - (SHARED_REG_SIZE * SHARED_REG_COUNT))

typedef struct  {
    volatile uint32_t CONTROL;
    volatile uint32_t STATUS;
    volatile uint32_t WAKEUP;
    volatile uint32_t CYCLECNT;
    volatile uint32_t STALLCNT;
    volatile uint8_t RSVD0[12];
    volatile uint32_t CONTABBLKIDX0;
    volatile uint32_t CONTABBLKIDX1;
    volatile uint32_t CONTABPROPTR0;
    volatile uint32_t CONTABPROPTR1;
    volatile uint8_t RSVD1[976];
    volatile uint32_t INTGPR0;
    volatile uint32_t INTGPR1;
    volatile uint32_t INTGPR2;
    volatile uint32_t INTGPR3;
    volatile uint32_t INTGPR4;
    volatile uint32_t INTGPR5;
    volatile uint32_t INTGPR6;
    volatile uint32_t INTGPR7;
    volatile uint32_t INTGPR8;
    volatile uint32_t INTGPR9;
    volatile uint32_t INTGPR10;
    volatile uint32_t INTGPR11;
    volatile uint32_t INTGPR12;
    volatile uint32_t INTGPR13;
    volatile uint32_t INTGPR14;
    volatile uint32_t INTGPR15;
    volatile uint32_t INTGPR16;
    volatile uint32_t INTGPR17;
    volatile uint32_t INTGPR18;
    volatile uint32_t INTGPR19;
    volatile uint32_t INTGPR20;
    volatile uint32_t INTGPR21;
    volatile uint32_t INTGPR22;
    volatile uint32_t INTGPR23;
    volatile uint32_t INTGPR24;
    volatile uint32_t INTGPR25;
    volatile uint32_t INTGPR26;
    volatile uint32_t INTGPR27;
    volatile uint32_t INTGPR28;
    volatile uint32_t INTGPR29;
    volatile uint32_t INTGPR30;
    volatile uint32_t INTGPR31;
    volatile uint32_t INTCTER0;
    volatile uint32_t INTCTER1;
    volatile uint32_t INTCTER2;
    volatile uint32_t INTCTER3;
    volatile uint32_t INTCTER4;
    volatile uint32_t INTCTER5;
    volatile uint32_t INTCTER6;
    volatile uint32_t INTCTER7;
    volatile uint32_t INTCTER8;
    volatile uint32_t INTCTER9;
    volatile uint32_t INTCTER10;
    volatile uint32_t INTCTER11;
    volatile uint32_t INTCTER12;
    volatile uint32_t INTCTER13;
    volatile uint32_t INTCTER14;
    volatile uint32_t INTCTER15;
    volatile uint32_t INTCTER16;
    volatile uint32_t INTCTER17;
    volatile uint32_t INTCTER18;
    volatile uint32_t INTCTER19;
    volatile uint32_t INTCTER20;
    volatile uint32_t INTCTER21;
    volatile uint32_t INTCTER22;
    volatile uint32_t INTCTER23;
    volatile uint32_t INTCTER24;
    volatile uint32_t INTCTER25;
    volatile uint32_t INTCTER26;
    volatile uint32_t INTCTER27;
    volatile uint32_t INTCTER28;
    volatile uint32_t INTCTER29;
    volatile uint32_t INTCTER30;
    volatile uint32_t INTCTER31;
} pru_regs_t;

int pru_load(uint8_t pru_num, const uint32_t *pru_code, uint32_t code_size)
{
    uint32_t *pru_program; 
    uint32_t i;

    if (pru_num == 0)
    {
        pru_program = (uint32_t *) PRU0_PROGRAM;
    }
    else if (pru_num == 1)
    {
        pru_program = (uint32_t *) PRU1_PROGRAM;
    }
    else
    {
        return -1;
    }

    for(i=0; i< code_size; i++)
    {
        pru_program[i] = pru_code[i];
    }
    return 0;
}

int pru_run(uint8_t pru_num)
{
    pru_regs_t *pru_regs;

    if (pru_num == 0)
    {
        pru_regs = (pru_regs_t *)PRU0_REGS;
    }
    else if (pru_num == 1)
    {
        pru_regs = (pru_regs_t *)PRU1_REGS;
    }
    else
    {
        return -1;
    }

    pru_regs->CONTROL = 2; 
    return 0;  
}

int pru_stop (uint8_t pru_num)
{
    pru_regs_t *pru_regs;

    if (pru_num == 0)
    {
        pru_regs = (pru_regs_t *)PRU0_REGS;
    }
    else if (pru_num == 1)
    {
        pru_regs = (pru_regs_t *)PRU1_REGS;
    }
    else
    {
        return -1;
    }

    pru_regs->CONTROL = 1; 
    return 0;  
}

uint32_t pru_get_reg(uint8_t pru_num, uint8_t reg_num)
{
    if(reg_num >= SHARED_REG_COUNT || pru_num > 1 )
        return 0; 

    uint32_t *base_addr = (uint32_t *)(PRU_DATARAM_BASE + PRU_DATARAM_REG_OFFSET + (0x2000 * pru_num)); 
    return *(base_addr + reg_num); 
}

void pru_set_reg(uint8_t pru_num, uint8_t reg_num, uint32_t reg_value)
{
    if(reg_num >= SHARED_REG_COUNT || pru_num > 1 )
        return;  

    uint32_t *base_addr = (uint32_t *)(PRU_DATARAM_BASE + PRU_DATARAM_REG_OFFSET + (0x2000 * pru_num)); 
    *(base_addr + reg_num) = reg_value; 

    return; 
}

#endif
