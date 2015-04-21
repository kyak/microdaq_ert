#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include <stdint.h>
#include <string.h>

#define BLOCK_MEM_BEGIN         (0xc2000000)

struct mdaq_blk_mem_
{
    int32_t start;
    int32_t index;
    int32_t overwrite;
    int32_t size;
};

#define MAX_MEM_READ_BLK        (16)
#define MAX_MEM_WRITE_BLK       (16)
#define MEM_DATA_ADDR           (BLOCK_MEM_BEGIN + sizeof(struct mdaq_blk_mem_) * MAX_MEM_WRITE_BLK)

static struct mdaq_blk_mem_ *mem_idx;
static int block_num = 0; 
#endif

void MEMWRInit( unsigned int start_idx, unsigned int data_size )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    if (block_num >= MAX_MEM_WRITE_BLK)
        return;

    mem_idx = (struct mdaq_blk_mem_ *)BLOCK_MEM_BEGIN;

    float *data_ptr = (float *)(MEM_DATA_ADDR + mem_idx[block_num].index);
    memset((void *)data_ptr, 0x0, data_size * sizeof(float));

    memset((char *)mem_idx, 0x0, sizeof(struct mdaq_blk_mem_) * MAX_MEM_WRITE_BLK);
    mem_idx[block_num].start = start_idx * sizeof(float);
    mem_idx[block_num].index = start_idx * sizeof(float);
    mem_idx[block_num].size = data_size;
    block_num++; 
#endif
}

void MEMWRStep(float data[], unsigned int start_idx, unsigned int vector_size, 
	     unsigned int overwrite, unsigned int data_size )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    int block_index; 	
    float *data_ptr;
    
    if (block_num >= MAX_MEM_WRITE_BLK)
        return;
    
    for (block_index = 0; block_index < block_num; block_index++)
        if(mem_idx[block_index].start == start_idx * sizeof(float))
            break; 

    if(block_index == block_num)
	return;

    if (overwrite && mem_idx[block_index].index >= (start_idx + data_size) * sizeof(float))
    {
        mem_idx[block_index].index = start_idx * sizeof(float);
        mem_idx[block_index].overwrite = overwrite ? 1 : 0;
    }

    data_ptr = (float *)(MEM_DATA_ADDR + mem_idx[block_index].index);

    memcpy((void *)data_ptr, (void *)data, vector_size * sizeof(float)); 

    if ( mem_idx[block_index].index < (start_idx + data_size) * sizeof(float) )
        mem_idx[block_index].index += vector_size * sizeof(float);
#endif
}

void MEMWRTerminate(unsigned char Channel, unsigned short data)
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)

#endif
}

