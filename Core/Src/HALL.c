#include "HALL.h"

/* 保存最近6次霍尔跳变的定时器计数值 */
static uint32_t HallPeriodBuffer[HALL_SPEED_WINDOW_SIZE] = {0};

/* 窗口内所有计数值之和 */
static uint64_t HallPeriodSum = 0;

/* 下一次写入数组的位置 */
static uint8_t HallPeriodIndex = 0;

/* 当前窗口内已有的有效数据数量 */
static uint8_t HallPeriodCount = 0;

void HALL_Init(void)
{
	HallPeriodSum = 0;
    HallPeriodIndex = 0;
    HallPeriodCount = 0;

    for (uint8_t i = 0; i < HALL_SPEED_WINDOW_SIZE; i++)
    {
        HallPeriodBuffer[i] = 0;
    }

    HALL.Speed_AvgOmega = 0.0f;

    HAL_TIMEx_HallSensor_Start_IT(&htim5);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim5)
	{
		
		HALL.CCR = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
		TIM5->CCR1 = 0;
		TIM5->CNT = 0;
		
		/*滑动窗口更新*/
		HallPeriodSum -= HallPeriodBuffer[HallPeriodIndex];
		HallPeriodBuffer[HallPeriodIndex] = HALL.CCR;
		HallPeriodSum += HallPeriodBuffer[HallPeriodIndex];

		HallPeriodIndex ++;
		
		if (HallPeriodIndex >= HALL_SPEED_WINDOW_SIZE)
		{
			HallPeriodIndex = 0;
		}

		if (HallPeriodCount < HALL_SPEED_WINDOW_SIZE)
		{
			HallPeriodCount ++;
		}
		/*计算电角速度*/
		HALL.Speed_AvgOmega = (PI / 3.0f) / 
							  (((float32_t)HallPeriodSum / (float32_t)HallPeriodCount) * Ttim5);
		
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
			break;
		}
	}
}




