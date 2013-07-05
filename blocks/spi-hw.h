#ifndef _HW_SPI_H_
#define _HW_SPI_H_

#include <stdint.h> 

#define CONFIG_USE_SPI1		(1)

#ifdef CONFIG_USE_SPI0
#define SPI_BASE                0x01c41000
#elif CONFIG_USE_SPI1
#define SPI_BASE                0x01E12000
#endif

#define SPI_SPIGCR0             *( volatile uint32_t* )( SPI_BASE + 0x0 )
#define SPI_SPIGCR1             *( volatile uint32_t* )( SPI_BASE + 0x4 )
#define SPI_SPIINT              *( volatile uint32_t* )( SPI_BASE + 0x8 )
#define SPI_SPILVL              *( volatile uint32_t* )( SPI_BASE + 0xc )
#define SPI_SPIFLG              *( volatile uint32_t* )( SPI_BASE + 0x10 )
#define SPI_SPIPC0              *( volatile uint32_t* )( SPI_BASE + 0x14 )
#define SPI_SPIPC2              *( volatile uint32_t* )( SPI_BASE + 0x1c )
#define SPI_SPIDAT1_TOP         *( volatile uint16_t* )( SPI_BASE + 0x3c )
#define SPI_SPIDAT1             *( volatile uint32_t* )( SPI_BASE + 0x3c )
#define SPI_SPIDAT1_PTR16       *( volatile uint16_t* )( SPI_BASE + 0x3e )
#define SPI_SPIDAT1_PTR8        *( volatile uint8_t* ) ( SPI_BASE + 0x3f )
#define SPI_SPIBUF              *( volatile uint32_t* )( SPI_BASE + 0x40 )
#define SPI_SPIBUF_PTR16        *( volatile uint16_t* )( SPI_BASE + 0x42 )
#define SPI_SPIBUF_PTR8         *( volatile uint8_t* ) ( SPI_BASE + 0x43 )
#define SPI_SPIEMU              *( volatile uint32_t* )( SPI_BASE + 0x44 )
#define SPI_SPIDELAY            *( volatile uint32_t* )( SPI_BASE + 0x48 )
#define SPI_SPIDEF              *( volatile uint32_t* )( SPI_BASE + 0x4c )
#define SPI_SPIFMT0             *( volatile uint32_t* )( SPI_BASE + 0x50 )
#define SPI_SPIFMT1             *( volatile uint32_t* )( SPI_BASE + 0x54 )
#define SPI_SPIFMT2             *( volatile uint32_t* )( SPI_BASE + 0x58 )
#define SPI_SPIFMT3             *( volatile uint32_t* )( SPI_BASE + 0x5c )
#define SPI_INTVEC0             *( volatile uint32_t* )( SPI_BASE + 0x60 )
#define SPI_INTVEC1             *( volatile uint32_t* )( SPI_BASE + 0x64 )

#endif /* _HW_SPI_H_ */ 
