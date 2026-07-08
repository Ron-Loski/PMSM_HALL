#ifndef __ABZ_H_
#define __ABZ_H_

#include "stm32h7xx_hal.h"
#include "arm_math.h"
#include "Global_Varibles.h"

extern TIM_HandleTypeDef htim4;

void ABZ_Start(void);
void ABZ_Stop(void);
float32_t ABZ_GetAngleMech(void);
float32_t ABZ_GetAngleElec(void);


#endif
