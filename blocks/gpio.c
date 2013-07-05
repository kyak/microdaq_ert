
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include "gpio.h"
#include <stdint.h>

#define SET         1
#define RESET       0

static void InitRisingEdgeInt(void);
static void InitFallingEdgeInt(void);

void MUX_init(void)
{
   /* Setup PINMUX Registers... */
    KICK0R = 0x83e70b13;    /* Kick0 register + data (unlock)       */
    KICK1R = 0x95a4f1e0;    /* Kick1 register + data (unlock)       */
    
    PINMUX0 = \
        ( MUX_FUNC_4 << EMB_WE      ) |
        ( MUX_FUNC_4 << EMB_RAS     ) |
        ( MUX_FUNC_4 << EMB_CAS     ) |
        ( MUX_FUNC_4 << EMB_CS0     ) |
        ( MUX_FUNC_4 << EMB_CLK     ) |
        ( MUX_FUNC_4 << EMB_SDCKE   ) |
        ( MUX_FUNC_1 << EMU0        ) |
        ( MUX_FUNC_1 << RTCK        );

    PINMUX1 = \
        ( MUX_FUNC_4 << EMB_A5      ) |
        ( MUX_FUNC_4 << EMB_A4      ) |
        ( MUX_FUNC_4 << EMB_A3      ) |
        ( MUX_FUNC_4 << EMB_A2      ) |
        ( MUX_FUNC_4 << EMB_A1      ) |
        ( MUX_FUNC_4 << EMB_A0      ) |
        ( MUX_FUNC_4 << EMB_BA0     ) |
        ( MUX_FUNC_4 << EMB_BA1     );

    PINMUX2 = \
        ( MUX_FUNC_4 << EMB_D31     ) |
        ( MUX_FUNC_4 << EMB_A12     ) |
        ( MUX_FUNC_4 << EMB_A11     ) |
        ( MUX_FUNC_4 << EMB_A10     ) |
        ( MUX_FUNC_4 << EMB_A9      ) |
        ( MUX_FUNC_4 << EMB_A8      ) |
        ( MUX_FUNC_4 << EMB_A7      ) |
        ( MUX_FUNC_4 << EMB_A6      );

    PINMUX3 = \
        ( MUX_FUNC_4 << EMB_D23     ) |
        ( MUX_FUNC_4 << EMB_D24     ) |
        ( MUX_FUNC_4 << EMB_D25     ) |
        ( MUX_FUNC_4 << EMB_D26     ) |
        ( MUX_FUNC_4 << EMB_D27     ) |
        ( MUX_FUNC_4 << EMB_D28     ) |
        ( MUX_FUNC_4 << EMB_D29     ) |
        ( MUX_FUNC_4 << EMB_D30     );

    PINMUX4 = \
        ( MUX_FUNC_4 << EMB_WE_DQM3 ) |
        ( MUX_FUNC_4 << EMB_D16     ) |
        ( MUX_FUNC_4 << EMB_D17     ) |
        ( MUX_FUNC_4 << EMB_D18     ) |
        ( MUX_FUNC_4 << EMB_D19     ) |
        ( MUX_FUNC_4 << EMB_D20     ) |
        ( MUX_FUNC_4 << EMB_D21     ) |
        ( MUX_FUNC_4 << EMB_D22     );

    PINMUX5 = \
        ( MUX_FUNC_4 << EMB_D6      ) |
        ( MUX_FUNC_4 << EMB_D5      ) |
        ( MUX_FUNC_4 << EMB_D4      ) |
        ( MUX_FUNC_4 << EMB_D3      ) |
        ( MUX_FUNC_4 << EMB_D2      ) |
        ( MUX_FUNC_4 << EMB_D1      ) |
        ( MUX_FUNC_4 << EMB_D0      ) |
        ( MUX_FUNC_4 << EMB_WE_DQM2 );

    PINMUX6 = \
        ( MUX_FUNC_4 << EMB_D14     ) |
        ( MUX_FUNC_4 << EMB_D13     ) |
        ( MUX_FUNC_4 << EMB_D12     ) |
        ( MUX_FUNC_4 << EMB_D11     ) |
        ( MUX_FUNC_4 << EMB_D10     ) |
        ( MUX_FUNC_4 << EMB_D9      ) |
        ( MUX_FUNC_4 << EMB_D8      ) |
        ( MUX_FUNC_4 << EMB_D7      );

    PINMUX7 = \
        ( MUX_FUNC_4 << SPI0_SCS    ) |
        ( MUX_FUNC_4 << SPI0_ENA    ) |
        ( MUX_FUNC_4 << SPI0_CLK    ) |
        ( MUX_FUNC_4 << SPI0_SIMO0  ) |
        ( MUX_FUNC_1 << SPI0_SOMI0  ) |
        ( MUX_FUNC_4 << EMB_WE_DQM0 ) |
        ( MUX_FUNC_4 << EMB_WE_DQM1 ) |
        ( MUX_FUNC_4 << EMB_D15     );

    PINMUX8 = \
        ( MUX_FUNC_3 << SPI1_ENA    ) |
        ( MUX_FUNC_4 << AXR1_11     ) |
        ( MUX_FUNC_4 << AXR1_10     ) |
        ( MUX_FUNC_3 << UART0_TXD   ) |
        ( MUX_FUNC_3 << UART0_RXD   ) |
        ( MUX_FUNC_4 << SPI1_CLK    ) |
        ( MUX_FUNC_4 << SPI1_SIMO0  ) |
        ( MUX_FUNC_4 << SPI1_SOMI0  );

    PINMUX9 = \
        ( MUX_FUNC_4 << AFSR0       ) |
        ( MUX_FUNC_4 << ACLKR0      ) |
        ( MUX_FUNC_DEFAULT << AHCLKR0) |
        ( MUX_FUNC_4 << AFSX0       ) |
        ( MUX_FUNC_4 << ACLKX0      ) |
        ( MUX_FUNC_4 << AHCLKX0     ) |
        ( MUX_FUNC_4 << USB0_DRVVBUS) |
        ( MUX_FUNC_3 << SPI1_SCS0   );

    PINMUX10 = \
        ( MUX_FUNC_3 << AXR0_6      ) |
        ( MUX_FUNC_3 << AXR0_5      ) |
        ( MUX_FUNC_3 << AXR0_4      ) |
        ( MUX_FUNC_3 << AXR0_3      ) |
        ( MUX_FUNC_3 << AXR0_2      ) |
        ( MUX_FUNC_3 << AXR0_1      ) |
        ( MUX_FUNC_3 << AXR0_0      ) |
        ( MUX_FUNC_4 << AMUTE0      );

    PINMUX11 = \
        ( MUX_FUNC_4 << AFSX1       ) |
        ( MUX_FUNC_4 << ACLKX1      ) |
        ( MUX_FUNC_4 << AHCLKX1     ) |
        ( MUX_FUNC_4 << AXR0_11     ) |
        ( MUX_FUNC_4 << UART1_TXD   ) |
        ( MUX_FUNC_4 << UART1_RXD   ) |
        ( MUX_FUNC_3 << AXR0_8      ) |
        ( MUX_FUNC_3 << AXR0_7      );

    PINMUX12 = \
        ( MUX_FUNC_4 << AXR1_3      ) |
        ( MUX_FUNC_1 << AXR1_2      ) |
        ( MUX_FUNC_1 << AXR1_1      ) |
        ( MUX_FUNC_4 << AXR1_0      ) |
        ( MUX_FUNC_4 << AMUTE1      ) |
        ( MUX_FUNC_4 << AFSR1       ) |
        ( MUX_FUNC_4 << ACLKR1      ) |
        ( MUX_FUNC_4 << AHCLKR1     );

    PINMUX13 = \
        ( MUX_FUNC_3 << EMA_D1      ) |
        ( MUX_FUNC_3 << EMA_D0      ) |
        ( MUX_FUNC_4 << AXR1_9      ) |
        ( MUX_FUNC_4 << AXR1_8      ) |
        ( MUX_FUNC_4 << AXR1_7      ) |
        ( MUX_FUNC_4 << AXR1_6      ) |
        ( MUX_FUNC_4 << AXR1_5      ) |
        ( MUX_FUNC_4 << AXR1_4      );

    PINMUX14 = \
        ( MUX_FUNC_1 << EMA_D9      ) |
        ( MUX_FUNC_1 << EMA_D8      ) |
        ( MUX_FUNC_3 << EMA_D7      ) |
        ( MUX_FUNC_3 << EMA_D6      ) |
        ( MUX_FUNC_3 << EMA_D5      ) |
        ( MUX_FUNC_3 << EMA_D4      ) |
        ( MUX_FUNC_3 << EMA_D3      ) |
        ( MUX_FUNC_3 << EMA_D2      );

    PINMUX15 = \
        ( MUX_FUNC_3 << EMA_A1        ) |
        ( MUX_FUNC_4 << EMA_A0        ) |
        ( MUX_FUNC_1 << EMA_D15 ) |
        ( MUX_FUNC_1 << EMA_D14 ) |
        ( MUX_FUNC_1 << EMA_D13 ) |
        ( MUX_FUNC_1 << EMA_D12 ) |
        ( MUX_FUNC_1 << EMA_D11 ) |
        ( MUX_FUNC_1 << EMA_D10 );

    PINMUX16 = \
        ( MUX_FUNC_4 << EMA_A9      ) |
        ( MUX_FUNC_4 << EMA_A8      ) |
        ( MUX_FUNC_4 << EMA_A7      ) |
        ( MUX_FUNC_4 << EMA_A6      ) |
        ( MUX_FUNC_4 << EMA_A5      ) |
        ( MUX_FUNC_4 << EMA_A4      ) |
        ( MUX_FUNC_4 << EMA_A3      ) |
        ( MUX_FUNC_3 << EMA_A2      );

    PINMUX17 = \
        ( MUX_FUNC_DEFAULT << EMA_CAS   ) |
        ( MUX_FUNC_DEFAULT << EMA_SDCKE ) |
        ( MUX_FUNC_4 << EMA_CLK         ) |
        ( MUX_FUNC_DEFAULT << EMA_BA0   ) |
        ( MUX_FUNC_DEFAULT << EMA_BA1   ) |
        ( MUX_FUNC_4 << EMA_A12         ) |
        ( MUX_FUNC_4 << EMA_A11         ) |
        ( MUX_FUNC_4 << EMA_A10         );

    PINMUX18 = \
        ( MUX_FUNC_4 << EMA_WE_DQM0     ) |
        ( MUX_FUNC_4 << EMA_WE_DQM1     ) |
        ( MUX_FUNC_4 << EMA_OE          ) |
        ( MUX_FUNC_4 << EMA_CS3         ) |
        ( MUX_FUNC_4 << EMA_CS2         ) |
        ( MUX_FUNC_4 << EMA_CS0         ) |
        ( MUX_FUNC_4 << EMA_WE          ) |
        ( MUX_FUNC_4 << EMA_RAS         );

    PINMUX19 = \
        ( MUX_FUNC_DEFAULT << MUX19_RES1  ) |
        ( MUX_FUNC_DEFAULT << MUX19_RES2  ) |
        ( MUX_FUNC_DEFAULT << MUX19_RES3  ) |
        ( MUX_FUNC_DEFAULT << MUX19_RES4  ) |
        ( MUX_FUNC_DEFAULT << MUX19_RES5  ) |
        ( MUX_FUNC_DEFAULT << MUX19_RES6  ) |
        ( MUX_FUNC_DEFAULT << MUX19_RES7  ) |
        ( MUX_FUNC_4 << EMA_WAIT          );

}


void GPIO_init(void)
{


/*
PCR register:
bit 1 SOFT - Soft bit enable mode bit. This bit is used in conjunction with FREE 
bit to determine the emulation suspend mode. FREE = 1, so this bit has no effect.

bit 0 FREE - Free-running enable mode bit. The FREE bit is fixed at 1, so the 
GPIO is free-running in emulation suspend mode.
*/
    GPIO_PCR = 1;                           /* Free GPIO from emulation */

/***********************************/
/* Initialize direction of IO pins */
/***********************************/

    /* Initialize Bank 0 ports */
    GPIO_01_DIR = \
              (GPIO_OUTPUT << PIN0)  |
              (GPIO_INPUT << PIN1)  |
              (GPIO_INPUT << PIN2)  |
              (GPIO_INPUT << PIN3)  |
              (GPIO_INPUT << PIN4)  |
              (GPIO_INPUT << PIN5)  |
              (GPIO_INPUT << PIN6)  |
              (GPIO_INPUT << PIN7)  |
              (GPIO_INPUT << PIN8)  |
              (GPIO_INPUT << PIN9)  |
              (GPIO_INPUT << PIN10) |
              (GPIO_INPUT << PIN11) |
              (GPIO_INPUT << PIN12) |
              (GPIO_INPUT << PIN13) |
              (GPIO_OUTPUT << PIN14)|
              (GPIO_OUTPUT << PIN15)|
    /* Initialize Bank 1 ports */
            (((GPIO_INPUT << PIN0)  |
              (GPIO_INPUT << PIN1)  |
              (GPIO_INPUT << PIN2)  |
              (GPIO_INPUT << PIN3)  |
              (GPIO_INPUT << PIN4)  |
              (GPIO_INPUT << PIN5)  |
              (GPIO_INPUT << PIN6)  |
              (GPIO_INPUT << PIN7)  |
              (GPIO_INPUT << PIN8)  |
              (GPIO_INPUT << PIN9)  |
              (GPIO_INPUT << PIN10) |
              (GPIO_INPUT << PIN11) |
              (GPIO_INPUT << PIN12) |
              (GPIO_INPUT << PIN13) |
              (GPIO_OUTPUT << PIN14)|
              (GPIO_OUTPUT << PIN15)) << 16);

    /* Initialize Bank 2 ports */
    GPIO_23_DIR = \
              (GPIO_OUTPUT << PIN0)  |
              (GPIO_INPUT << PIN1)  |
              (GPIO_INPUT << PIN2)  |
              (GPIO_INPUT << PIN3)  |
              (GPIO_INPUT << PIN4)  |
              (GPIO_INPUT << PIN5)  |
              (GPIO_INPUT << PIN6)  |
              (GPIO_INPUT << PIN7)  |
              (GPIO_INPUT << PIN8)  |
              (GPIO_INPUT << PIN9)  |
              (GPIO_INPUT << PIN10) |
              (GPIO_INPUT << PIN11) |
              (GPIO_INPUT << PIN12) |
              (GPIO_INPUT << PIN13) |
              (GPIO_OUTPUT << PIN14)|
              (GPIO_OUTPUT << PIN15)|
    /* Initialize Bank 3 ports */
            (((GPIO_INPUT << PIN0)  |
              (GPIO_INPUT << PIN1)  |
              (GPIO_INPUT << PIN2)  |
              (GPIO_INPUT << PIN3)  |
              (GPIO_INPUT << PIN4)  |
              (GPIO_INPUT << PIN5)  |
              (GPIO_INPUT << PIN6)  |
              (GPIO_INPUT << PIN7)  |
              (GPIO_INPUT << PIN8)  |
              (GPIO_INPUT << PIN9)  |
              (GPIO_INPUT << PIN10) |
              (GPIO_INPUT << PIN11) |
              (GPIO_INPUT << PIN12) |
              (GPIO_INPUT << PIN13) |
              (GPIO_OUTPUT << PIN14)|
              (GPIO_OUTPUT << PIN15)) << 16);

    /* Initialize Bank 4 ports */
    GPIO_45_DIR = \
              (GPIO_OUTPUT << PIN0)  |
              (GPIO_INPUT << PIN1)  |
              (GPIO_INPUT << PIN2)  |
              (GPIO_INPUT << PIN3)  |
              (GPIO_INPUT << PIN4)  |
              (GPIO_INPUT << PIN5)  |
              (GPIO_INPUT << PIN6)  |
              (GPIO_INPUT << PIN7)  |
              (GPIO_INPUT << PIN8)  |
              (GPIO_INPUT << PIN9)  |
              (GPIO_INPUT << PIN10) |
              (GPIO_INPUT << PIN11) |
              (GPIO_INPUT << PIN12) |
              (GPIO_INPUT << PIN13) |
              (GPIO_OUTPUT << PIN14)|
              (GPIO_OUTPUT << PIN15)|
    /* Initialize Bank 5 ports */
            (((GPIO_INPUT << PIN0)  |
              (GPIO_INPUT << PIN1)  |
              (GPIO_INPUT << PIN2)  |
              (GPIO_INPUT << PIN3)  |
              (GPIO_INPUT << PIN4)  |
              (GPIO_INPUT << PIN5)  |
              (GPIO_INPUT << PIN6)  |
              (GPIO_INPUT << PIN7)  |
              (GPIO_INPUT << PIN8)  |
              (GPIO_INPUT << PIN9)  |
              (GPIO_INPUT << PIN10) |
              (GPIO_INPUT << PIN11) |
              (GPIO_INPUT << PIN12) |
              (GPIO_INPUT << PIN13) |
              (GPIO_OUTPUT << PIN14)|
              (GPIO_OUTPUT << PIN15)) << 16);

    /* Initialize Bank 6 ports */
    GPIO_67_DIR = \
              (GPIO_OUTPUT << PIN0)  |
              (GPIO_INPUT << PIN1)  |
              (GPIO_INPUT << PIN2)  |
              (GPIO_INPUT << PIN3)  |
              (GPIO_INPUT << PIN4)  |
              (GPIO_INPUT << PIN5)  |
              (GPIO_INPUT << PIN6)  |
              (GPIO_INPUT << PIN7)  |
              (GPIO_INPUT << PIN8)  |
              (GPIO_INPUT << PIN9)  |
              (GPIO_INPUT << PIN10) |
              (GPIO_INPUT << PIN11) |
              (GPIO_INPUT << PIN12) |
              (GPIO_INPUT << PIN13) |
              (GPIO_OUTPUT << PIN14)|
              (GPIO_OUTPUT << PIN15)|
    /* Initialize Bank 7 ports */
            (((GPIO_INPUT << PIN0)  |
              (GPIO_INPUT << PIN1)  |
              (GPIO_INPUT << PIN2)  |
              (GPIO_INPUT << PIN3)  |
              (GPIO_INPUT << PIN4)  |
              (GPIO_INPUT << PIN5)  |
              (GPIO_INPUT << PIN6)  |
              (GPIO_INPUT << PIN7)  |
              (GPIO_INPUT << PIN8)  |
              (GPIO_INPUT << PIN9)  |
              (GPIO_INPUT << PIN10) |
              (GPIO_INPUT << PIN11) |
              (GPIO_INPUT << PIN12) |
              (GPIO_INPUT << PIN13) |
              (GPIO_OUTPUT << PIN14)|
              (GPIO_OUTPUT << PIN15)) << 16);

    InitRisingEdgeInt();
    InitFallingEdgeInt();
}

static void InitRisingEdgeInt(void)
{
/************************************************/
/* Initialize rising edge interrupts of IO pins */
/************************************************/

    /* Initialize Bank 0 ports */
    GPIO_01_SET_RIS_TRIG = \
              (RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15) |
    /* Initialize Bank 1 ports */
            (((RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15)) << 16);

    /* Initialize Bank 2 ports */
    GPIO_23_SET_RIS_TRIG = \
              (RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15) |
    /* Initialize Bank 3 ports */
            (((RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15)) << 16);

    /* Initialize Bank 4 ports */
    GPIO_45_SET_RIS_TRIG = \
              (RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15) |
    /* Initialize Bank 5 ports */
            (((RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15)) << 16);

    /* Initialize Bank 6 ports */
    GPIO_67_SET_RIS_TRIG = \
              (RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15) |
    /* Initialize Bank 7 ports */
            (((RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15)) << 16);

/************************************************/
/* Initialize rising edge interrupts of IO pins */
/************************************************/

    /* Initialize Bank 0 ports */
    GPIO_01_CLR_RIS_TRIG = \
              (RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15) |
    /* Initialize Bank 1 ports */
            (((RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15)) << 16);

    /* Initialize Bank 2 ports */
    GPIO_23_CLR_RIS_TRIG = \
              (RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15) |
    /* Initialize Bank 3 ports */
            (((RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15)) << 16);

    /* Initialize Bank 4 ports */
    GPIO_45_CLR_RIS_TRIG = \
              (RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15) |
    /* Initialize Bank 5 ports */
            (((RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15)) << 16);

    /* Initialize Bank 6 ports */
    GPIO_67_CLR_RIS_TRIG = \
              (RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15) |
    /* Initialize Bank 7 ports */
            (((RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15)) << 16);

}

static void InitFallingEdgeInt(void)
{
/*************************************************/
/* Initialize falling edge interrupts of IO pins */
/*************************************************/

    /* Initialize Bank 0 ports */
    GPIO_01_SET_FAL_TRIG = \
              (RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15) |
    /* Initialize Bank 1 ports */
            (((RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15)) << 16);

    /* Initialize Bank 2 ports */
    GPIO_23_SET_FAL_TRIG = \
              (RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15) |
    /* Initialize Bank 3 ports */
            (((RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15)) << 16);

    /* Initialize Bank 4 ports */
    GPIO_45_SET_FAL_TRIG = \
              (RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15) |
    /* Initialize Bank 5 ports */
            (((RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15)) << 16);

    /* Initialize Bank 6 ports */
    GPIO_67_SET_FAL_TRIG = \
              (RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15) |
    /* Initialize Bank 7 ports */
            (((RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15)) << 16);



/*************************************************/
/* Initialize falling edge interrupts of IO pins */
/*************************************************/

    /* Initialize Bank 0 ports */
    GPIO_01_CLR_FAL_TRIG = \
              (RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15) |
    /* Initialize Bank 1 ports */
            (((RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15)) << 16);

    /* Initialize Bank 2 ports */
    GPIO_23_CLR_FAL_TRIG = \
              (RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15) |
    /* Initialize Bank 3 ports */
            (((RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15)) << 16);

    /* Initialize Bank 4 ports */
    GPIO_45_CLR_FAL_TRIG = \
              (RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15) |
    /* Initialize Bank 5 ports */
            (((RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15)) << 16);

    /* Initialize Bank 6 ports */
    GPIO_67_CLR_FAL_TRIG = \
              (RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15) |
    /* Initialize Bank 7 ports */
            (((RESET << PIN0)  |
              (RESET << PIN1)  |
              (RESET << PIN2)  |
              (RESET << PIN3)  |
              (RESET << PIN4)  |
              (RESET << PIN5)  |
              (RESET << PIN6)  |
              (RESET << PIN7)  |
              (RESET << PIN8)  |
              (RESET << PIN9)  |
              (RESET << PIN10) |
              (RESET << PIN11) |
              (RESET << PIN12) |
              (RESET << PIN13) |
              (RESET << PIN14) |
              (RESET << PIN15)) << 16);

}


int16_t GPIO_setDir(GPIO_PinNumber_t pinNumber, GPIO_PortDir_t direction)
{
    /* Get the bank address from upper nibble - divide by 2 - no of banks per 32bit register */
    uint32_t bank_id = (pinNumber >> 5);
    uint32_t* gpio_handle = (uint32_t*) (GPIO_BASE + GPIO_DIR_BASE + (GPIO_BASE_OFFSET * bank_id));
    /* Get the pin */
    uint32_t pin_id  = 1 << (pinNumber & 0x1f);

    if(GPIO_OUTPUT == direction)
    {
        /* Set to OUTPUT */
        *gpio_handle &= ~pin_id;
    }
    else
    {
        /* Set to INPUT */
        *gpio_handle |= pin_id;
    }

    return 0;
}

int16_t GPIO_setOutput(GPIO_PinNumber_t pinNumber, GPIO_PinStatus_t output)
{
    /* Get the bank address from upper nibble - divide by 2 - no of banks per 32bit register */
    uint32_t bank_id = (pinNumber >> 5);
    uint32_t* gpio_handle;
    /* Get the pin */
    uint32_t pin_id  = 1 << (pinNumber & 0x1f);

    if(( output & 1 ) == 0)
    {
        gpio_handle = (uint32_t*) (GPIO_BASE + GPIO_CLR_DATA_BASE + (GPIO_BASE_OFFSET * bank_id));
        /* Set to LOW */
        *gpio_handle = pin_id;
    }
    else
    {
        gpio_handle = (uint32_t*) (GPIO_BASE + GPIO_SET_DATA_BASE + (GPIO_BASE_OFFSET * bank_id));
        /* Set to HIGH */
        *gpio_handle = pin_id;
    }

    return 0;
}

int16_t GPIO_getInput(GPIO_PinNumber_t pinNumber)
{
    uint32_t input;
    /* Get the bank address from upper nibble - divide by 2 - no of banks per 32bit register */
    uint32_t bank_id = (pinNumber >> 5);
    uint32_t* gpio_handle = (uint32_t*) (GPIO_BASE + GPIO_IN_DATA_BASE + (GPIO_BASE_OFFSET * bank_id));
    /* Get the pin */
    uint32_t pin_id  = (pinNumber & 0x1f);

    input = *gpio_handle;
    input = ( input >> pin_id ) & 1;

    return (int16_t)input;
}

int16_t GPIO_getOutput(GPIO_PinNumber_t pinNumber)
{
    uint32_t input;
    /* Get the bank address from upper nibble - divide by 2 - no of banks per 32bit register */
    uint32_t bank_id = (pinNumber >> 5);
    uint32_t* gpio_handle = (uint32_t*) (GPIO_BASE + GPIO_OUT_DATA_BASE + (GPIO_BASE_OFFSET * bank_id));
    /* Get the pin */
    uint32_t pin_id  = (pinNumber & 0x1f);

    input = *gpio_handle;
    input = ( input >> pin_id ) & 1;

    return (int16_t)input;
}

/*****************************************************************************
*
*   FUNCTION NAME:  int16_t GPIO_getLastSetOutput(GPIO_PinNumber_t pinNumber)
*
*   DESCRIPTION:   Read last set output pin state (it may differ from output
*                   state due to possible capacitance on pin or 
*                   pull up/down condition).
*                   Warning: there is no check if it is output, user must 
*                   know that before using the function.
*
******************************************************************************/
int16_t GPIO_getLastSetOutput(GPIO_PinNumber_t pinNumber)
{
    uint32_t status;
    /* Get the bank address from upper nibble - divide by 2 - no of banks per 32bit register */
    uint32_t bank_id = (pinNumber >> 5);
    uint32_t* gpio_handle = (uint32_t*) (GPIO_BASE + GPIO_OUT_DATA_BASE + (GPIO_BASE_OFFSET * bank_id));
    /* Get the pin */
    uint32_t pin_id  = (pinNumber & 0x1f);

    status = *gpio_handle;
    status = ( status >> pin_id ) & 1;

    return (int16_t)status;
}

/*****************************************************************************
*
*   FUNCTION NAME:  int16_t MUX_setPinFunc(GPIO_PinNumber_t pinNumber, 
*                                                    GPIO_PortDir_t direction)
*
*   DESCRIPTION:   Setup IO pin function in MUX
*                   pinOffset - value from MUX_MuxXXCtrlNibble_t enum where XX 
*                               stands for MUX number
*
******************************************************************************/

int16_t MUX_setPinFunc(MUX_Mux_t muxReg, uint8_t pinOffset, MUX_PinFunc_t newFunc)
{
    /* MUX registers are located one by one */
    volatile uint32_t* pinMux = (uint32_t*) (&PINMUX0 + muxReg);
    volatile uint32_t temp = *pinMux;

    KICK0R = 0x83e70b13;    /* Kick0 register + data (unlock) */
    KICK1R = 0x95a4f1e0;    /* Kick1 register + data (unlock) */

    /* Clean up previous value - whole nibble */
    temp &= ~(0x0f << pinOffset);
    /* Set new value */
    temp |= (newFunc << pinOffset);
    *pinMux = temp;

    return 0;
}

/*****************************************************************************
*
*   FUNCTION NAME:  int16_t GPIO_setEdgeTrigger(GPIO_PinNumber_t pinNumber,
*                                               GPIO_EdgeType_t edgeType)
*
*   DESCRIPTION:   Set pin to trigger either rising or falling edge interrupt
*
*
******************************************************************************/
int16_t GPIO_setEdgeTrigger(GPIO_PinNumber_t pinNumber, GPIO_EdgeType_t edgeType)
{
    /* Get the bank address from upper nibble - divide by 2 - no of banks per 32bit register */
    uint32_t bank_id = (pinNumber >> 5);
    uint32_t* gpio_handle;
    /* Get the pin */
    uint32_t pin_id  = 1 << (pinNumber & 0x1f);

    if(GPIO_RISING_EDGE == edgeType)
    {
        gpio_handle = (uint32_t*) (GPIO_BASE + GPIO_SET_RIS_TRIG_BASE + (GPIO_BASE_OFFSET * bank_id));
        /* Set to rising edge trigger */
        *gpio_handle = pin_id;
    }
    else
    {
        gpio_handle = (uint32_t*) (GPIO_BASE + GPIO_SET_FAL_TRIG_BASE + (GPIO_BASE_OFFSET * bank_id));
        /* Set to falling edge trigger */
        *gpio_handle = pin_id;
    }

    return 0;
}

/*****************************************************************************
*
*   FUNCTION NAME:  int16_t GPIO_clrEdgeTrigger(GPIO_PinNumber_t pinNumber,
*                                               GPIO_EdgeType_t edgeType)
*
*   DESCRIPTION:   Clear edge pin trigger interrupt
*
******************************************************************************/
int16_t GPIO_clrEdgeTrigger(GPIO_PinNumber_t pinNumber, GPIO_EdgeType_t edgeType)
{
    /* Get the bank address from upper nibble - divide by 2 - no of banks per 32bit register */
    uint32_t bank_id = (pinNumber >> 5);
    uint32_t* gpio_handle;
    /* Get the pin */
    uint32_t pin_id  = 1 << (pinNumber & 0x1f);

    if(GPIO_RISING_EDGE == edgeType)
    {
        gpio_handle = (uint32_t*) (GPIO_BASE + GPIO_CLR_RIS_TRIG_BASE + (GPIO_BASE_OFFSET * bank_id));
        /* Clear to rising edge trigger */
        *gpio_handle = pin_id;
    }
    else
    {
        gpio_handle = (uint32_t*) (GPIO_BASE + GPIO_CLR_FAL_TRIG_BASE + (GPIO_BASE_OFFSET * bank_id));
        /* Clear to falling edge trigger */
        *gpio_handle = pin_id;
    }

    return 0;
}
#endif

