#ifndef __HALL_H_
#define __HALL_H_

#include "stm32h7xx_hal.h"
#include "arm_math.h"
#include "tim.h"
#include "usart.h"

/*霍尔角度滑动窗口*/
#define HALL_SPEED_WINDOW_SIZE    4U


/*低频霍尔传感器周期*/
#define Ttim5	(1.0f / (240000000.0f / 240.0f))
/*中频更新周期*/
#define Ttim7	(1.0f / (240000000.0f / 240.0f / 1000.0f))	//由DS修改
/* TIM1 center-aligned PWM/control period: 2 * ARR / timer clock = 100 us */
#define	Ttim1	(2.0f * 12000.0f / 240000000.0f)
#define Ctrl_Num		(10000 / 1000)	

typedef struct {
	uint8_t State;			//霍尔当前状态位
	uint32_t CCR;			//霍尔对应定时器的累加值
	float32_t Theta[6];		//每个霍尔传感器对应的角度值
	float32_t Speed_AvgOmega;	//拟合电角速度
	float32_t Angle;			//霍尔扇区矫正角度
}HALL_typedef;


void HALL_Init(void);
void HAL_TIM_TriggerCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);


extern TIM_HandleTypeDef htim5;
extern volatile HALL_typedef HALL;
extern float32_t Mech_Angle;				//机械角度
extern float32_t Elec_Angle;				//电角度
extern float32_t Theta_Delta;			//高频电角度差值


#endif
