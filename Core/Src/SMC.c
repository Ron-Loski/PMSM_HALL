#include "SMC.h"

void SMC_LoopEnable(void)
{
    HAL_TIM_Base_Start_IT(&htim7);
}

void SMC_LoopDisable(void)
{
    HAL_TIM_Base_Stop(&htim7);
}

float32_t SMC_Sat(float32_t s, float32_t delta)
{
	if (s > delta){
		return 1.0f;
	}
	else if (s < -delta){
		return -1.0f;
	}
	else{
		return s / delta;
	}
}

/*
	iq = (smc->J / (smc->c * smc->Kt)) * (smc->epsilon * sat + smc->k * s) 
			+ (smc->B / smc->Kt) * w_fb;
*/
float32_t SMC_Speed_Process(SMC_Speedtypedef *smc, float32_t w_ref, float32_t w_fb)
{
	float32_t e = w_ref - w_fb;
	
	float32_t s = smc->c * e;
	
	float32_t sat = SMC_Sat(s, smc->delta);					//饱和函数代替符号函数
	
	float32_t reaching = smc->epsilon * sat + smc->k * s;	//指数趋近律：ε·sat(s) + k·s
	
	float iq = (smc->J / (smc->c * smc->Kt)) * reaching
               + (smc->B / smc->Kt) * w_fb;   				//iq = (J / (c * Kt)) * reaching + (B / Kt) * w_fb

	if (iq > smc->iq_max){
        iq = smc->iq_max;
	}
    else if (iq < smc->iq_min){
        iq = smc->iq_min;
	}
	 
	 return iq;
}


















