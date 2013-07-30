/* hardware.h -- hardware definitions for MicroDAQ device
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#ifndef HARDWARE_H
#define HARDWARE_H

#include <stdint.h>

#define SYS_CFG_BASE                0x01c14000

#define SYS_KICK0               *( volatile uint32_t* )( SYS_CFG_BASE + 0x38 )
#define SYS_PINMUX0             *( volatile uint32_t* )( SYS_CFG_BASE + 0x120 )
#define SYS_PINMUX1             *( volatile uint32_t* )( SYS_CFG_BASE + 0x124 )
#define SYS_PINMUX2             *( volatile uint32_t* )( SYS_CFG_BASE + 0x128 )
#define SYS_PINMUX3             *( volatile uint32_t* )( SYS_CFG_BASE + 0x12c )
#define SYS_PINMUX4             *( volatile uint32_t* )( SYS_CFG_BASE + 0x130 )
#define SYS_PINMUX5             *( volatile uint32_t* )( SYS_CFG_BASE + 0x134 )
#define SYS_PINMUX6             *( volatile uint32_t* )( SYS_CFG_BASE + 0x138 )
#define SYS_PINMUX7             *( volatile uint32_t* )( SYS_CFG_BASE + 0x13c )
#define SYS_PINMUX8             *( volatile uint32_t* )( SYS_CFG_BASE + 0x140 )
#define SYS_PINMUX9             *( volatile uint32_t* )( SYS_CFG_BASE + 0x144 )
#define SYS_PINMUX10            *( volatile uint32_t* )( SYS_CFG_BASE + 0x148 )
#define SYS_PINMUX11            *( volatile uint32_t* )( SYS_CFG_BASE + 0x14c )
#define SYS_PINMUX12            *( volatile uint32_t* )( SYS_CFG_BASE + 0x150 )
#define SYS_PINMUX13            *( volatile uint32_t* )( SYS_CFG_BASE + 0x154 )
#define SYS_PINMUX14            *( volatile uint32_t* )( SYS_CFG_BASE + 0x158 )
#define SYS_PINMUX15            *( volatile uint32_t* )( SYS_CFG_BASE + 0x15c )
#define SYS_PINMUX16            *( volatile uint32_t* )( SYS_CFG_BASE + 0x160 )
#define SYS_PINMUX17            *( volatile uint32_t* )( SYS_CFG_BASE + 0x164 )
#define SYS_PINMUX18            *( volatile uint32_t* )( SYS_CFG_BASE + 0x168 )
#define SYS_PINMUX19            *( volatile uint32_t* )( SYS_CFG_BASE + 0x16c )
#define SYS_CFGCHIP0            *( volatile uint32_t* )( SYS_CFG_BASE + 0x17c )

#define SYS_CHIPSIG            	( SYS_CFG_BASE + 0x174 )
#define SYS_CHIPSIG_CLR         ( SYS_CFG_BASE + 0x178 )

/* SPI Module Related Registers */
#define CONFIG_USE_SPI1 (1)

#ifdef CONFIG_USE_SPI0
#define SPI_BASE                0x01c41000
#elif CONFIG_USE_SPI1
#define SPI_BASE                0x01E12000
#endif

#define SPI_SPIGCR0             *( volatile Uint32* )( SPI_BASE + 0x0 )
#define SPI_SPIGCR1             *( volatile Uint32* )( SPI_BASE + 0x4 )
#define SPI_SPIINT              *( volatile Uint32* )( SPI_BASE + 0x8 )
#define SPI_SPILVL              *( volatile Uint32* )( SPI_BASE + 0xc )
#define SPI_SPIFLG              *( volatile Uint32* )( SPI_BASE + 0x10 )
#define SPI_SPIPC0              *( volatile Uint32* )( SPI_BASE + 0x14 )
#define SPI_SPIPC2              *( volatile Uint32* )( SPI_BASE + 0x1c )
#define SPI_SPIDAT1_TOP         *( volatile Uint16* )( SPI_BASE + 0x3c )
#define SPI_SPIDAT1             *( volatile Uint32* )( SPI_BASE + 0x3c )
#define SPI_SPIDAT1_PTR16       *( volatile Uint16* )( SPI_BASE + 0x3e )
#define SPI_SPIDAT1_PTR8        *( volatile Uint8* ) ( SPI_BASE + 0x3f )
#define SPI_SPIBUF              *( volatile Uint32* )( SPI_BASE + 0x40 )
#define SPI_SPIBUF_PTR16        *( volatile Uint16* )( SPI_BASE + 0x42 )
#define SPI_SPIBUF_PTR8         *( volatile Uint8* ) ( SPI_BASE + 0x43 )
#define SPI_SPIEMU              *( volatile Uint32* )( SPI_BASE + 0x44 )
#define SPI_SPIDELAY            *( volatile Uint32* )( SPI_BASE + 0x48 )
#define SPI_SPIDEF              *( volatile Uint32* )( SPI_BASE + 0x4c )
#define SPI_SPIFMT0             *( volatile Uint32* )( SPI_BASE + 0x50 )
#define SPI_SPIFMT1             *( volatile Uint32* )( SPI_BASE + 0x54 )
#define SPI_SPIFMT2             *( volatile Uint32* )( SPI_BASE + 0x58 )
#define SPI_SPIFMT3             *( volatile Uint32* )( SPI_BASE + 0x5c )
#define SPI_INTVEC0             *( volatile Uint32* )( SPI_BASE + 0x60 )
#define SPI_INTVEC1             *( volatile Uint32* )( SPI_BASE + 0x64 )

/*PSC Module Related Registers*/
#define S_PSC0_BASE       0x01C10000
#define S_PSC1_BASE       0x01E27000

#define S_PSC0_MDCTL      (S_PSC0_BASE+0xA00)
#define S_PSC0_MDSTAT     (S_PSC0_BASE+0x800)
#define S_PSC0_PTCMD      *(volatile unsigned int*) (S_PSC0_BASE + 0x120)
#define S_PSC0_PTSTAT     *(volatile unsigned int*) (S_PSC0_BASE + 0x128)

#define S_PSC1_MDCTL      (S_PSC1_BASE+0xA00)
#define S_PSC1_MDSTAT     (S_PSC1_BASE+0x800)
#define S_PSC1_PTCMD      *(volatile unsigned int*) (S_PSC1_BASE + 0x120)
#define S_PSC1_PTSTAT     *(volatile unsigned int*) (S_PSC1_BASE + 0x128)

#define PSC_ECAP			(20)
#define PSC_EQEP			(21)

void PSC0_lPSC_enable(unsigned int PD, unsigned int LPSC_num);
void PSC1_lPSC_enable(unsigned int PD, unsigned int LPSC_num);

int set_reg16(uint32_t base, uint8_t reg, uint16_t value);
int set_reg32(uint32_t base, uint8_t reg, uint32_t value);

uint16_t	 get_reg16(uint32_t base, uint8_t reg);
uint32_t	 get_reg32(uint32_t base, uint8_t reg);



#endif /* HARDWARE_H */
