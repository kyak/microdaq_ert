
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include "utils.h"

// Accurate n = ((t us * f MHz) - 5) / 1.65

void delay_accurate (uint32_t n)
{
#if defined(_TMS320C6X)
  asm ("      STW     B0, *+B15[2]    ");
  asm ("      SUB     A4, 24, A4      ");          // Total cycles taken by this function, with n = 0, including clocks taken to jump to this function
  asm ("      CMPGT   A4, 0, B0       ");
  asm ("loop:                         ");
  asm (" [B0] B       loop            ");
  asm (" [B0] SUB     A4, 6, A4       ");          // Cycles taken by loop
  asm ("      CMPGT   A4, 0, B0       ");
  asm ("      NOP     3               ");
  asm ("      LDW     *+B15[2], B0    ");
#endif
}

void delay_us( uint32_t us)
{
	delay_accurate(us * 182);
}


inline uint8_t raw_read8(uint32_t addr)
{
	return *(uint8_t *)(addr);
}

inline uint16_t raw_read16(uint32_t addr)
{
	return *(uint16_t *)(addr);
}

uint32_t raw_read32(uint32_t addr)
{
	return *(uint32_t *)(addr);
}



inline void raw_write8(uint8_t data, uint32_t addr)
{
	*(uint8_t *)(addr) = data;
}

void raw_write16(uint16_t data, uint32_t addr)
{
	*(uint16_t *)(addr) = data;
}

void raw_write32(uint32_t data, uint32_t addr)
{
	*(uint32_t *)(addr) = data;
}
#endif
