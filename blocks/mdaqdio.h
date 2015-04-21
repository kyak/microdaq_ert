#ifndef __MDAQGPIO_H
#define __MDAQGPIO_H


void DIOConfig(unsigned char func1, unsigned char func2, 
		unsigned char func3, unsigned char func4, 
		unsigned char func5, unsigned char func6, 
		unsigned char dir1, unsigned char dir2, 
		unsigned char dir3, unsigned char dir4);

void DIOInit(unsigned char pin, unsigned char dir, unsigned char init_value);
void DIOSetStep(unsigned char pin, unsigned char value);
void DIOSetTerminate(unsigned char pin, unsigned char value);
void DIOGetStep(unsigned char pin, unsigned char *value);

void DIOFncKeyInit(unsigned char func_key);
void DIOFncKeyStep(unsigned char func_key, unsigned char *value);

#endif
