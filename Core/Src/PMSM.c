#include "PMSM.h"

void PMSM_BoadEnable(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);
}

void PMSM_BoadDisable(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);
}

void PMSM_CalibADC(Current_Offsettypedef *p)
{
	uint32_t sum_u = 0;
    uint32_t sum_v = 0;
    uint32_t sum_w = 0;

	HAL_ADCEx_InjectedStart_IT(&hadc1);

	HAL_TIM_Base_Start(&htim1);
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
	
//	p->Iu_Offset = (p->Iu_Offset + p->Iv_Offset + p->Iw_Offset) / 3;
//	p->Iv_Offset = (p->Iu_Offset + p->Iv_Offset + p->Iw_Offset) / 3;
//	p->Iw_Offset = (p->Iu_Offset + p->Iv_Offset + p->Iw_Offset) / 3;

	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_4);

	HAL_ADCEx_InjectedStop(&hadc1);
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
	
	HAL_ADCEx_InjectedStart_IT(&hadc1);
}

void PMSM_MotorSample(void)
{
	Mech_Angle += 0.001f;
	
	if (Mech_Angle > 2.0f * PI){
		Mech_Angle -= (2.0f * PI);
	}else if (Mech_Angle < 0.0f){
		Mech_Angle += (2 * PI);
	}
	
	Elec_Angle = Mech_Angle * Polo_Num;
	
	/*读取JDR注入通道数据寄存器的值*/
	ADCInjectBuff[0] = ADC1->JDR1;
	ADCInjectBuff[1] = ADC1->JDR2;
	ADCInjectBuff[2] = ADC1->JDR3;
	/*转化为实际电流*/
	Curr_Sample.Ia = (ADCInjectBuff[0] - Current_Offset.Iu_Offset) * 3.3f / 65535.0f / 0.08f;
	Curr_Sample.Ib = (ADCInjectBuff[1] - Current_Offset.Iv_Offset) * 3.3f / 65535.0f / 0.08f;
	Curr_Sample.Ic = (ADCInjectBuff[2] - Current_Offset.Iw_Offset) * 3.3f / 65535.0f / 0.08f;
	
	/*一阶互补滤波*/
	StatorI.Ia = (1.0 - Filter_Coeff) * Curr_Sample.Ia + Filter_Coeff * StatorFilter_Ia;
	StatorI.Ib = (1.0 - Filter_Coeff) * Curr_Sample.Ib + Filter_Coeff * StatorFilter_Ib;
	StatorI.Ic = (1.0 - Filter_Coeff) * Curr_Sample.Ic + Filter_Coeff * StatorFilter_Ic;
	
	StatorFilter_Ia = StatorI.Ia;
	StatorFilter_Ib = StatorI.Ib;
	StatorFilter_Ic = StatorI.Ic;
	
//	float32_t Ia_hp = Filter_Coeff * (Ia_hp_prev + Curr_Sample.Ia - Ia_prev);
//	float32_t Ib_hp = Filter_Coeff * (Ib_hp_prev + Curr_Sample.Ib - Ib_prev);
//	float32_t Ic_hp = Filter_Coeff * (Ic_hp_prev + Curr_Sample.Ic - Ic_prev);

//	Ia_hp_prev = Ia_hp;
//	Ib_hp_prev = Ib_hp;
//	Ic_hp_prev = Ic_hp;
//	Ia_prev = Curr_Sample.Ia;
//	Ib_prev = Curr_Sample.Ib;
//	Ic_prev = Curr_Sample.Ic;

//	StatorI.Ia = Ia_hp;
//	StatorI.Ib = Ib_hp;
//	StatorI.Ic = Ic_hp;

	FOC_Clark(&StatorI, &FeedbackCalrk);
	FOC_Park(&FeedbackParkI, &FeedbackCalrk, Elec_Angle);
}



