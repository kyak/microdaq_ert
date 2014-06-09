#include <string.h>
#include "mdaq_stream.h"
#include "memory_map.h"

#define STREAM_MAX_CH   (16)
#define STREAM_CH_SIZE  (STREAM_MEM_SIZE >> 4)

#define STREAM_BUF_IN_USE   (1 << 0)
#define STREAM_FIRST_RUN    (1 << 1)
#define STREAM_ALLOC_BIT    (1 << 2)
#define STREAM_BUF0_FULL    (1 << 3)
#define STREAM_BUF1_FULL    (1 << 4)
#define STREAM_BUSY         (1 << 5)

#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
struct stream_mem
{
    uint32_t status[STREAM_MAX_CH]; 
    uint32_t size0[STREAM_MAX_CH]; 
    uint32_t size1[STREAM_MAX_CH]; 
    uint8_t channel[STREAM_MAX_CH][STREAM_CH_SIZE];
};
    
static struct stream_mem *stream_mem_ptr = (struct stream_mem *)STREAM_MEM_BEGIN; 
#endif 

void switch_buffer( uint8_t ch )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    stream_mem_ptr->status[ch] = 
        (stream_mem_ptr->status[ch] & STREAM_BUF_IN_USE) ? 
        (stream_mem_ptr->status[ch] & (~STREAM_BUF_IN_USE)) : 
        (stream_mem_ptr->status[ch] | STREAM_BUF_IN_USE); 
#endif 
}


int mdaq_stream_alloc( int8_t ch, uint8_t stream_dir )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    int ch_index; 
    static int first_time = 1; 

    if(first_time)
    {
        for(ch_index = 0; ch_index < STREAM_MAX_CH; ch_index++)
        {
            stream_mem_ptr->status[ch_index] = 0; 
            stream_mem_ptr->size0[ch_index] = 0; 
            stream_mem_ptr->size1[ch_index] = 0;
        }
        first_time = 0;
    }

    if ( ch < 0 ) 
    {
	    for (ch_index = 0; ch_index < STREAM_MAX_CH; ch_index++)
	    {
		    if(stream_mem_ptr->status[ch_index] == 0)
		    {
			    stream_mem_ptr->status[ch_index] |= 
				    STREAM_ALLOC_BIT | STREAM_FIRST_RUN; 

			    return ch_index; 
		    }
	    }
	}
	else
	{
			if( ch < STREAM_MAX_CH)
			{
					stream_mem_ptr->status[ch] |= 
							STREAM_ALLOC_BIT | STREAM_FIRST_RUN; 
					return ch; 
			}
			return -1;
	}

#endif 
    return -1; 
}

int mdaq_stream_dealloc( uint8_t ch )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    if ( ch < STREAM_MAX_CH )
    {
        stream_mem_ptr->status[ch] = 0; 
        stream_mem_ptr->size0[ch] = 0; 
        stream_mem_ptr->size1[ch] = 0;
    }
#endif 
    return 0;  
}

int mdaq_stream_read( uint8_t ch, uint32_t *data, size_t *size)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    uint8_t buf_in_use = stream_mem_ptr->status[ch] & STREAM_BUF_IN_USE; 

    /* If DSP is processing data wait until done */ 
    while( stream_mem_ptr->status[ch] & STREAM_BUSY );
    
    switch_buffer(ch); 

    *data = (uint32_t)&(stream_mem_ptr->channel[ch][0]) + (buf_in_use *  STREAM_CH_SIZE / 2);
    *size = (size_t)(buf_in_use ? stream_mem_ptr->size1[ch] : stream_mem_ptr->size0[ch]); 

    if ( buf_in_use )
        stream_mem_ptr->size1[ch] = 0; 
    else
        stream_mem_ptr->size0[ch] = 0; 

#endif 
    return 0; 
}

int mdaq_stream_write( uint8_t ch, uint8_t *stream_data, size_t size)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    uint8_t buf_in_use = stream_mem_ptr->status[ch] & STREAM_BUF_IN_USE; 
    
    if ( (buf_in_use ? stream_mem_ptr->size1[ch] : stream_mem_ptr->size0[ch]) + size > STREAM_CH_SIZE / 2 )
    {
        stream_mem_ptr->status[ch] |= buf_in_use ? STREAM_BUF1_FULL : STREAM_BUF0_FULL;  
        buf_in_use = (~buf_in_use) & 0x1;
    }

    if ( ch < STREAM_MAX_CH || stream_mem_ptr->status[ch] & STREAM_ALLOC_BIT)
    {
        stream_mem_ptr->status[ch] |= STREAM_BUSY;  

        memcpy( (void *) ((uint32_t)&(stream_mem_ptr->channel[ch][0]) + (buf_in_use * STREAM_CH_SIZE / 2) +
				(buf_in_use ? stream_mem_ptr->size1[ch] : stream_mem_ptr->size0[ch])),
                (void *) stream_data, 
                size); 
        

        if ( buf_in_use )
            stream_mem_ptr->size1[ch] += size; 
        else
            stream_mem_ptr->size0[ch] += size; 

        stream_mem_ptr->status[ch] &= ~STREAM_BUSY;  
            
     } 

#endif 
    return 0; 
}

