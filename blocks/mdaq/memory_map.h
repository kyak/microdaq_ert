#ifndef MLINK_MEM_MAP
#define MLINK_MEM_MAP
#include <stdint.h>

#define MLINK_MEM_SIZE      (0x1000000)
#define MLINK_MEM_BEGIN     (0xc2000000)
#define MLINK_MEM_END       (MLINK_RAM_BEGIN + MLINK_RAM_SIZE - 1)

#define STREAM_MEM_SIZE     (0x800000)
#define STREAM_MEM_BEGIN    (MLINK_MEM_BEGIN)
#define STREAM_MEM_END      (STREAM_MEM_BEGIN + STREAM_MEM_SIZE - 1)

#endif /* MLINK_MEM_MAP */ 
