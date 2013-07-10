#ifndef _MDAQENC_H
#define _MDAQENC_H

void ENCInit(unsigned char Channel);
void ENCStep(unsigned char Channel, int *position);

#endif /* _MDAQENC_H */
