#include "PMSM.h"

void PMSM_BoadEnable(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);
}

void PMSM_BoadDisable(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);
}

uint8_t PMSM_CalibADC(Current_Offsettypedef *p)
{	
	uint32_t sum_u = 0;
    uint32_t sum_v = 0;
    uint32_t sum_w = 0;

	HAL_ADCEx_InjectedStart(&hadc1);

	HAL_TIM_Base_Start(&htim1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
	HAL_Delay(2000);
	
    for (uint16_t i = 0; i < 100; i++)
    {
        // 启动注入转换
		HAL_ADCEx_InjectedStart(&hadc1);
		
		// 等待注入转换完成
		HAL_ADCEx_InjectedPollForConversion(&hadc1, HAL_MAX_DELAY);
		
		// 读取三个注入通道
	    sum_u += ADC1->JDR1;
        sum_v += ADC1->JDR2;
        sum_w += ADC1->JDR3;
    }

    p->Iu_Offset = sum_u / 100.0f;
    p->Iv_Offset = sum_v / 100.0f;
    p->Iw_Offset = sum_w / 100.0f;
	
	
	HAL_TIM_Base_Stop(&htim1);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_4);

	HAL_ADCEx_InjectedStop(&hadc1);
	
	return 1;
  }

void PMSM_Init(void)
{	
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);
	
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
	HAL_ADCEx_InjectedStart_IT(&hadc1);
}

void PMSM_MotorSample(void)
{
	if (Motor_State == MOTOR_OPEN_CURRENT)
	{
		Mech_Angle += 2.0f * PI * 50.0f / (10000.0f * Polo_Num);		//PWM频率为10k
		Elec_Angle = Mech_Angle * Polo_Num;
	}
	else
	{
		HALL.Angle += HALL.Speed_AvgOmega * Ttim1;	
		Elec_Angle = HALL.Angle;		
	}

	
	while (Mech_Angle > 2 * PI) { Mech_Angle -= 2 * PI; }
	while (Elec_Angle > 2 * PI) { Elec_Angle -= 2 * PI; }
	while (HALL.Angle > 2 * PI) { HALL.Angle -= 2 * PI; }

		
		
	/*读取JDR注入通道数据寄存器*/
	ADCInjectBuff[0] = ADC1->JDR1;
	ADCInjectBuff[1] = ADC1->JDR2;
	ADCInjectBuff[2] = ADC1->JDR3;
	
	/*转化为实际电流*/
	Curr_Sample.Ia = (ADCInjectBuff[0] - Current_Offset.Iu_Offset) * 3.3f / 65535.0f / 0.08f;
	Curr_Sample.Ib = (ADCInjectBuff[1] - Current_Offset.Iv_Offset) * 3.3f / 65535.0f / 0.08f;
	Curr_Sample.Ic = (ADCInjectBuff[2] - Current_Offset.Iw_Offset) * 3.3f / 65535.0f / 0.08f;

	// 去除零序分量
	float32_t I_zero = (Curr_Sample.Ia + Curr_Sample.Ib + Curr_Sample.Ic) / 3.0f;
	Curr_Sample.Ia -= I_zero;
	Curr_Sample.Ib -= I_zero;
	Curr_Sample.Ic -= I_zero;
	
	const float32_t alpha = 0.1f;
	/*一阶低通滤波*/
    StatorFilter_Ia = StatorFilter_Ia + alpha * (Curr_Sample.Ia - StatorFilter_Ia);
    StatorFilter_Ib = StatorFilter_Ib + alpha * (Curr_Sample.Ib - StatorFilter_Ib);
    StatorFilter_Ic = StatorFilter_Ic + alpha * (Curr_Sample.Ic - StatorFilter_Ic);	
	/*赋值给定子电流结构体*/
	StatorI.Ia = StatorFilter_Ia;
	StatorI.Ib = StatorFilter_Ib;
	StatorI.Ic = StatorFilter_Ic;
	
	FOC_Clark(&StatorI, &FeedbackCalrk);
	FOC_Park(&FeedbackParkI, &FeedbackCalrk, Elec_Angle);
}



