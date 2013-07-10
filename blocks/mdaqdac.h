#ifndef _MDAQDAC_H
#define _MDAQDAC_H

void DACInit( void );
void DACStep(unsigned char Channel, unsigned short data);
void DACTerminate(unsigned char Channel, unsigned short data);
#endif /* _MDAQDAC_H */
