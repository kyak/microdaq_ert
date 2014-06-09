#ifndef STREAM_H
#define STREAM_H

#include <stdint.h>
#include <stdio.h>

#define STREAM_OUT      (1)
#define STREAM_IN       (0)

int mdaq_stream_alloc(int8_t ch, uint8_t stream_dir);
int mdaq_stream_dealloc(uint8_t ch); 
int mdaq_stream_read(uint8_t ch, uint32_t *data, size_t *size);
int mdaq_stream_write(uint8_t ch, uint8_t *stream_data, size_t size);

#endif /* STREAM_H */ 
