#ifndef MDAQ_AOUT_H
#define MDAQ_AOUT_H
#include <stdint.h>

#define MDAQ_AOUT_MAX		(8)

#define MDAQ_AOUT_ASYNC_MODE	(0)
#define MDAQ_AOUT_SYNC_MODE		(1)

typedef struct mdaq_aout_config_
{
    int8_t              ch;
    float               gain;
    float               offset;
    float               range_low;
    float               range_high;
    uint16_t			dac_value;
    uint8_t     		mode;
}mdaq_aout_t;

int mdaq_aout_init( void );
int mdaq_aout_write(uint8_t ch, uint16_t data );

#endif /* MDAQ_AOUT_H */
