#ifndef _MDAQSTREAM_H_
#define _MDAQSTREAM_H_

void OutStreamInit(unsigned char stream_ch, unsigned char vector_size);
void OutStreamStep(double *data, unsigned char stream_ch, unsigned char vector_size);
void OutStreamTerminate(unsigned char stream_ch);

#endif /* _MDAQSTREAM_H_ */ 

