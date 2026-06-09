#ifndef __HALL_H_
#define __HALL_H_

#include "stm32h7xx_hal.h"
#include "arm_math.h"


typedef struct {
	uint8_t State;
	float32_t Theta;
}HALL_typedef;


void HALL_Init(void);
void HAL_TIM_TriggerCallback(TIM_HandleTypeDef *htim);

extern TIM_HandleTypeDef htim5;
extern HALL_typedef HALL;
extern float32_t Mech_Angle;				//机械角度
extern float32_t Elec_Angle;				//电角度



#endif
