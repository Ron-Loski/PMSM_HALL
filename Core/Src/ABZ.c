#include "ABZ.h"

void ABZ_Start(void)
{
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
}

void ABZ_Stop(void)
{
	HAL_TIM_Encoder_Stop(&htim4, TIM_CHANNEL_ALL);
}

float32_t ABZ_GetAngleMech(void)
{
	float32_t ccr = TIM4->CNT;
	float32_t angle = ccr / (TIM4->ARR + 1) * 2 * PI;
	
	while (angle > 2 * PI) {angle -= 2 * PI;}
	while (angle < -2 * PI) {angle += 2 * PI;}
	
	return angle;
}

float32_t ABZ_GetAngleElec(void)
{
	float32_t ccr = TIM4->CNT;
	float32_t elec_angle = (ccr / (TIM4->ARR + 1) * 2 * PI) * Polo_Num;
	
	while (elec_angle > 2 * PI) {elec_angle -= 2 * PI;}
	while (elec_angle < -2 * PI) {elec_angle += 2 * PI;}

	return elec_angle;
}
