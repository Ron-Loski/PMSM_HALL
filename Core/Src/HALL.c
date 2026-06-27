#include "HALL.h"

void HALL_Init(void)
{

	HAL_TIMEx_HallSensor_Start_IT(&htim5);
//	HAL_TIM_Base_Start_IT(&htim7);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim5)
	{
		
		HALL.CCR += HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
		TIM5->CCR1 = 0;
		
	    uint8_t HU = HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_10) ? 1 : 0;
        uint8_t HV = HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_11) ? 1 : 0;
        uint8_t HW = HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_12) ? 1 : 0;

        HALL.State = (HV << 2) | (HW << 1) | HU;
				
		switch (HALL.State){
			case 0x03:
				HALL.Theta[0] = 0.0f;
				HALL.Angle = HALL.Theta[0];
				break;
			case 0x01:
				HALL.Theta[1] =  2.0f * PI * (1.0f / 6.0f);
				HALL.Angle = HALL.Theta[1];
				break;
			case 0x05:
				HALL.Theta[2] = 2.0f * PI * (2.0f / 6.0f); 
				HALL.Angle = HALL.Theta[2];
				break;
			case 0x04:
				HALL.Theta[3] = 2.0f * PI * (3.0f / 6.0f); 
				HALL.Angle = HALL.Theta[3];
				break;
			case 0x06:
				HALL.Theta[4] = 2.0f * PI * (4.0f / 6.0f); 
				HALL.Angle = HALL.Theta[4];
				break;
			case 0x02:
				HALL.Theta[5] = 2.0f * PI * (5.0f / 6.0f); 
				HALL.Angle = HALL.Theta[5];
			/*计算电角速度*/
			HALL.Speed_AvgOmega = 2.0f * PI / ((float32_t)HALL.CCR * Ttim5);	
			HALL.CCR = 0;
			break;
		}	
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim7)
	{
		HALL.Angle += HALL.Speed_AvgOmega * Ttim7;
		Theta_Delta = (Elec_Angle - HALL.Angle) / 20.0f;//(Ttim7 / Ttim1)
		
		
		
	}
}




