#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include "gpio.h"
#include <stdint.h>

#define SET         1
#define RESET       0


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
