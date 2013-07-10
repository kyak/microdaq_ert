#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include <stdint.h>

#include "ltc185x.h"
#include "gpio.h"
#include "spi.h"
#include "utils.h"

#define LTC185X_CMD_DIFF_SGL_BIT    (1 << 7)
#define LTC185X_CMD_ODD_SIGN_BIT    (1 << 6)
#define LTC185X_CMD_SELECT1_BIT     (1 << 5)
#define LTC185X_CMD_SELECT0_BIT     (1 << 4)

#define LTC185X_CMD_UNI_BIT         (1 << 3)
#define LTC185X_CMD_GAIN_BIT        (1 << 2)

#define LTC185X_CMD_NAP_BIT         (1 << 1)
#define LTC185X_CMD_SLEEP_BIT       (1 << 0)

/* pins used for ltc185x converter */
#define LTC185X_CONV_START          GP4_0
#define LTC185X_BUSY                GP5_10
#define LTC185X_EN                  GP4_11

#define ANALOG_EN					GP5_11

#define LTC185X_SPI_FREQ			(15000000)
#define LTC185X_SPI_POLARITY		(0)
#define LTC185X_SPI_PHRASE			(0)

static inline void ltc185x_en( void )
{
	if (GPIO_getOutput(LTC185X_EN) != GPIO_LOW)
	{
		GPIO_setOutput(LTC185X_EN, GPIO_LOW);
		spi_set_freq(LTC185X_SPI_FREQ);
		spi_set_polarity(LTC185X_SPI_POLARITY);
		spi_set_phrase(LTC185X_SPI_PHRASE);
	}
}

static inline uint8_t ltc185x_create_cmd(uint8_t ch, uint8_t range, uint8_t mode, uint8_t polarity)
{
    uint8_t cmd = 0; 
    
    if ( ch & 0x1 ) 
        cmd |= LTC185X_CMD_ODD_SIGN_BIT; 

    cmd |= ( (ch & 0x7) >> 1) << 4; 

    if ( range == AIN_RANGE_10V )
        cmd |= LTC185X_CMD_GAIN_BIT;

    if ( mode != AIN_MODE_DIFF )
        cmd |= LTC185X_CMD_DIFF_SGL_BIT; 
    
    if ( polarity != AIN_POL_BIPOLAR )
        cmd |= LTC185X_CMD_UNI_BIT; 

    return cmd; 
}

static inline void ltc185x_start_conv( void )
{
    GPIO_setOutput(LTC185X_CONV_START, GPIO_HIGH);  

    /* High state on CONV_START should be min 40ns */
    delay_accurate(1);
    GPIO_setOutput(LTC185X_CONV_START, GPIO_LOW);

    while(!GPIO_getInput( LTC185X_BUSY ));
} 

static int ltc185x_xfer(uint8_t cmd, uint16_t *data)
{
    int ret = -1;
    volatile uint16_t tmp_cmd = 0;

    tmp_cmd |= ( cmd << 8);

    ret = spi_xfer( 16, (void*)&tmp_cmd, data, SPI_XFER_END);
    if (ret)
    {
       return -1;
    }

    return 0;
}

int ltc185x_init( void )
{
	/* Configure SPI bus for analog */
	spi_setup_bus(LTC185X_SPI_FREQ, LTC185X_SPI_POLARITY, LTC185X_SPI_PHRASE);

	/* Enable analog section */
	GPIO_setDir(ANALOG_EN,    GPIO_OUTPUT);
	GPIO_setOutput(ANALOG_EN, GPIO_LOW);

	/* Enable LTC185x converter */
	GPIO_setDir(LTC185X_EN, GPIO_OUTPUT);
	GPIO_setOutput(LTC185X_EN, GPIO_LOW);

	/* Set CONVST line to low */
	GPIO_setDir(LTC185X_CONV_START, GPIO_OUTPUT);
    GPIO_setOutput(LTC185X_CONV_START, GPIO_LOW);

    return 0;
}

int ltc185x_read_ch( uint16_t *data, uint8_t ch, uint8_t range,
		uint8_t mode, uint8_t polarity )
{
    volatile uint8_t cmd;

    /* enable ltc185x converter */
    ltc185x_en();

    /* prepare command for converter */ 
    cmd = ltc185x_create_cmd(ch, range, mode, polarity);

    ltc185x_xfer(cmd, 0);

     /* trigger conversion start and wait for busy line */
    ltc185x_start_conv();

    /* read data from converter */
    return ltc185x_xfer(cmd, data);
}
#endif
