/* spi.h -- SPI driver for MicroDAQ device
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#ifndef _SPI_H_
#define _SPI_H_

#include <stdint.h>

#define SPI_XFER_BEGIN  0x01
#define SPI_XFER_END    0x02

#define SPI_MAX_FREQUENCY	(50000000)

int spi_xfer(uint8_t bitlen, const void *dout,
		void *din, uint32_t flags);

void spi_set_freq(uint32_t freq);
void spi_set_polarity(uint8_t polarity);
void spi_set_phrase(uint8_t phrase);
int spi_setup_bus(uint32_t freq, uint8_t polarity, uint8_t phrase);


#endif /* _SPI_H_ */
