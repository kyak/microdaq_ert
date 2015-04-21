#ifndef __MDAQMEM_H
#define __MDAQMEM_H

void MEMRDInit( unsigned int start_idx );
void MEMRDStep(float data[], unsigned int start_idx, unsigned int vector_size, 
	     unsigned int periodic, unsigned int data_size );


void MEMWRInit( unsigned int start_idx, unsigned int data_size );
void MEMWRStep(float data[], unsigned int start_idx, unsigned int vector_size, 
	     unsigned int overwrite, unsigned int data_size );

#endif /* __MDAQMEM_H */
