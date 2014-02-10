#ifndef _MDAQMOTOR_H
#define _MDAQMOTOR_H

void MOTORInit(unsigned char motor, unsigned char type, unsigned char pwm_freq);
void MOTORStep(unsigned char motor, unsigned char en, unsigned char dir, unsigned int pwm_duty);
void MOTORTerminate(unsigned char motor);

#endif /* _MDAQMOTOR_H */
