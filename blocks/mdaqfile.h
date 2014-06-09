#ifndef _MDAQFILE_H_
#define _MDAQFILE_H_

void ToFileInit(char *file_name, unsigned char mode, unsigned long buf_len, unsigned char ch, unsigned char type);
void ToFileStep(double *data, unsigned long buf_len, unsigned char ch, unsigned char type);
void ToFileTerminate(void);

void FromFileInit(char *file_name, unsigned char mode, unsigned long buf_len, unsigned char ch, unsigned char type);
void FromFileStep(double *data, unsigned long buf_len, unsigned char ch, unsigned char type);
void FromFileTerminate(void);

#endif /* _MDAQFILE_H_ */ 

