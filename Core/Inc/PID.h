#ifndef __PID_H_
#define __PID_H_

#include "stm32h7xx_hal.h"

typedef struct{
	float Target;
	float Actual;
	float Out;
	
	float Kp;
	float Ki;
	float Kd;
	
	float Error0;
	float Error1;
	float ErrorInt;
	
	float OutMax;
	float OutMin;
}PID_t;

void PID_Init(PID_t *p);
void PID_Update(PID_t *p);

#endif
