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

static int32_t mem_idx[MAX_MEM_READ_BLK];
static int32_t mem_start_idx[MAX_MEM_READ_BLK];
static int block_num = 0; 
#endif

void MEMRDInit( unsigned int start_idx )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    mem_idx[block_num] = start_idx * sizeof(float);
    mem_start_idx[block_num] = start_idx * sizeof(float);
    block_num++; 
#endif
}

void MEMRDStep(float data[], unsigned int start_idx, unsigned int vector_size, 
	     unsigned int periodic, unsigned int data_size )
{
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
    int block_index = 0; 
    if (block_num >= MAX_MEM_READ_BLK)
        return;

    for (block_index = 0; block_index < block_num; block_index++)
        if(mem_start_idx[block_index] == start_idx * sizeof(float))
            break; 

    if(block_index == block_num)
	return;

    if (periodic && (mem_idx[block_index]) >= (start_idx + data_size) * sizeof(float) )
        mem_idx[block_index] = start_idx * sizeof(float);

    memcpy((void *)data, (void *)(MEM_DATA_ADDR + mem_idx[block_index]), data_size * sizeof(float)); 

    // data = (float *)(MEM_DATA_ADDR + mem_idx[block_index]);

    if ( mem_idx[block_index] < (start_idx + data_size) * sizeof(float) )
        mem_idx[block_index] += vector_size * sizeof(float);
#endif
}

