#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "utils.h"
#include "spi-hw.h"
#include "spi.h"

#define SPI_CLOCK_FREQUENCY		(150000000)

void spi_set_freq( uint32_t freq)
{
	uint32_t scalar = ((SPI_CLOCK_FREQUENCY / freq) - 1 ) & 0xFF;
	uint32_t reg = SPI_SPIFMT0;

	if ( freq > SPI_MAX_FREQUENCY)
		return;

	reg &= ~0xFF00;
	reg |= scalar << 8;
	SPI_SPIFMT0 = reg;

	return;
}

void spi_set_polarity(uint8_t polarity)
{
	uint32_t reg = SPI_SPIFMT0;

	if(polarity)
		reg |= 1 << 17;
	else
		reg &= ~(1 << 17);

	SPI_SPIFMT0 = reg;

	return;
}

void spi_set_phrase(uint8_t phrase)
{
	uint32_t reg = SPI_SPIFMT0;

	if(phrase)
		reg |= 1 << 16;
	else
		reg &= ~(1 << 16);

	SPI_SPIFMT0 = reg;

	return;
}

int spi_setup_bus(uint32_t freq, uint8_t polarity, uint8_t phrase)
{
	uint32_t scalar;
	volatile uint32_t data1_reg = 0;

	/* Enable the SPI hardware */
	SPI_SPIGCR0 = 0;
	delay_us(1000);
	SPI_SPIGCR0 = 1;

	/* Set master mode, powered up and not activated */
	SPI_SPIGCR1 = 3;

	/* CS, CLK, SIMO and SOMI are functional pins */
	SPI_SPIPC0 = (1 << 0) | (1 << 9) | (1 << 10) | (1 << 11);

	/* setup format */
	scalar = ((SPI_CLOCK_FREQUENCY / freq) - 1 ) & 0xFF;

	SPI_SPIFMT0 = 16 | (scalar << 8) | ((phrase & 0x1) << 16) | ((polarity & 0x1) << 17) | (0 << 20);

	/* hold cs active at end of transfer until explicitly de-asserted */
	data1_reg = (1 << 28) | (0 << 16);
	SPI_SPIDAT1 = data1_reg;

	/* including a minor delay. No science here. Should be good even with
	 * no delay
	 */
	//SPI_SPIDELAY = (1 << 24) | (1 << 16);

	/* default chip select register */
	SPI_SPIDEF = 1;

	/* no interrupts */
	SPI_SPIINT = 0;
	SPI_SPILVL = 0;

	/* enable SPI */
	SPI_SPIGCR1 |= ( 1 << 24 );

	return 0;
}

void spi_release_bus( void )
{
	/* Disable the SPI hardware */
	SPI_SPIGCR0 = 0;
}

int spi_xfer(uint8_t bitlen, const void *dout,
		void *din, uint32_t flags)
{
	static unsigned int data1_reg_val;
	volatile unsigned int	len;
	volatile int		i;
	volatile const uint16_t	*txp = dout;
	volatile uint16_t		*rxp = din;



	len = bitlen / 16;

	/* do an empty read to clear the current contents */
	SPI_SPIBUF;

	/* keep writing and reading 1 byte until done */
	for (i = 0; i < len; i++) {

		/* wait till TXFULL is asserted */
		while( SPI_SPIBUF & 0x20000000 );

		/* write the data */
		data1_reg_val &= ~0xFFFF;
		if(txp) {
			data1_reg_val |= *txp & 0xFFFF;
			txp++;
		}

		/* write to DAT1 is required to keep the serial transfer going */
		/* we just terminate when we reach the end */
		if((i == (len -1)) && (flags & SPI_XFER_END)) {
			SPI_SPIDAT1 = data1_reg_val & ~(1 << 28);
		} else {
			SPI_SPIDAT1 = data1_reg_val;
		}


		/* read the data - wait for data availability */
		while ( SPI_SPIBUF & ( 0x80000000 ) );

		if(rxp) {
			*rxp = SPI_SPIBUF & 0xFFFF;
			rxp++;
		} else {
			SPI_SPIBUF;
		}

	}

	return 0;

out:
	if (flags & SPI_XFER_END) {
		SPI_SPIDAT1 = data1_reg_val & ~(1 << 28);
	}

	return 0;
}
#endif
