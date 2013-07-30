#ifndef _MDAQ_AIN_CAP_
#define _MDAQ_AIN_CAP_

typedef enum mdaq_ain_range_
{
    AIN_RANGE_DEFAULT = 0,
    AIN_RANGE_10V = 0,
    AIN_RANGE_5V,
    AIN_RANGE_CUSTOM
}mdaq_ain_range_t; 

typedef enum mdaq_ain_mode_
{
    AIN_MODE_DEFAULT = 0,
    AIN_MODE_SINGLE  = 0,
    AIN_MODE_DIFF = 1
}mdaq_ain_mode_t; 

typedef enum mdaq_ain_pol_
{
    AIN_POL_DEFAULT = 0,
    AIN_POL_BIPOLAR = 0,
    AIN_POL_UNIPOLAR = 1
}mdaq_ain_pol_t;

#endif /* _MDAQ_AIN_CAP_ */ 
