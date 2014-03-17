#include "mdaqled.h"

/* Initialize LEDs */
void mdaqled_init(void)
{
#ifndef MATLAB_MEX_FILE
#endif
}

/* Set LED status */
/* led: 1/2 (D1/D2); state: 0/1 (on/off) */
void mdaqled_set(unsigned char led, unsigned char state)
{
#ifndef MATLAB_MEX_FILE
    if (led == 1)
        /* D1 */
        if (state == 1)
            /* ON */
            GPIO_setOutput(GP2_6, GPIO_LOW);
        else
            GPIO_setOutput(GP2_6, GPIO_HIGH);
    else if (led == 2)
        /* D2 */
        if (state == 1)
            /* ON */
            GPIO_setOutput(GP2_7, GPIO_LOW);
        else
            GPIO_setOutput(GP2_7, GPIO_HIGH);
    else
    {
        /* Shouldn't get here, but switch off LEDs for good */
        GPIO_setOutput(GP2_7, GPIO_HIGH);
        GPIO_setOutput(GP2_6, GPIO_HIGH);
    }
#endif
}
