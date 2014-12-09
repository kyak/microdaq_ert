/* microdaq_timer.c -- timestamp facility
*
* Copyright (C) 2013 Embedded Solutions
* All rights reserved.
*
* This software may be modified and distributed under the terms
* of the BSD license. See the LICENSE file for details.
*/

#include <c6x.h>

unsigned long long profileTimerRead64(void)
{

	/* Read 64bit internal DSP cycle counter */
    static int first_time = 1;
    static unsigned long long start = 0;
    unsigned long long tmp = TSCH;

    if (first_time)
    {
    	start = TSCL + (tmp << 32);
    	first_time = 0;
    	return 0;
    }
    return (TSCL + (tmp << 32)) - start;
}

unsigned long profileTimerRead(void)
{
	/* Read 64bit internal DSP cycle counter */
    static int first_time = 1;
    static unsigned long start = 0;

    if (first_time)
    {
    	start = TSCL;
    	first_time = 0;
    	return 0;
    }
    return TSCL - start;
}
