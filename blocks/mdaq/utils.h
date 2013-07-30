/* utils.h -- Utils for MicroDAQ device
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#ifndef UTILS_H
#define UTILS_H
#include <stdint.h>

#define BIT(x) ( 1 << x)

void delay_accurate (uint32_t n);
void delay_us( uint32_t us);

uint8_t raw_read8(uint32_t addr);
uint16_t raw_read16(uint32_t addr);
uint32_t raw_read32(uint32_t addr);

void raw_write8(uint8_t data, uint32_t addr);
void raw_write16(uint16_t data, uint32_t addr);
void raw_write32(uint32_t data, uint32_t addr);

#endif /* UTILS_H */
