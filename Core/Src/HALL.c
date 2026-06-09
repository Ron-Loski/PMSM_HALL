#include "HALL.h"

void HALL_Init(void)
{

	HAL_TIMEx_HallSensor_Start_IT(&htim5);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim5)
	{
	    uint8_t HU = HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_10) ? 1 : 0;
        uint8_t HV = HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_11) ? 1 : 0;
        uint8_t HW = HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_12) ? 1 : 0;

        HALL.State = (HV << 2) | (HW << 1) | HU;
		HALL.Theta = Mech_Angle;
	}

}



