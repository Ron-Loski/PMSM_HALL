#ifndef __SMC_H_
#define __SMC_H_

#include "stm32h7xx_hal.h"
#include "arm_math.h"
#include "tim.h"

typedef struct {
	float32_t  c;		//滑模面系数s=c*e
	float32_t epsilon;	//等速趋近率>0
	float32_t k;			//指数趋近系数
	float32_t J;			//转动惯量
	float32_t Kt;		//转矩常数
	float32_t B;			//粘滞系数
	float32_t Ts;		//采样时间
	float32_t delta;		//饱和函数厚度>0
	
	float32_t iq_max;
	float32_t iq_min;
}SMC_Speedtypedef;

extern SMC_Speedtypedef SMC_Speed;

void SMC_LoopEnable(void);
void SMC_LoopDisable(void);
float32_t SMC_Sat(float32_t s, float32_t delta);
float32_t SMC_Speed_Process(SMC_Speedtypedef *smc, float32_t w_ref, float32_t w_fb);




#endif
