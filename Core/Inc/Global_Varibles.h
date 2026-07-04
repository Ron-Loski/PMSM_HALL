#ifndef __GLOBAL_BARIBLES_H_
#define __GLOBAL_BARIBLES_H_	

#include "stm32h7xx_hal.h"
#include "stdint.h"
#include "arm_math.h"
#include "PID.h"
#include "HALL.h"
#include "SMC.h"

#define	U_dc	30.0
#define	Tpwm	24000		//此处为TIM计数值周期
#define Polo_Num		4.0f	//极对数
#define Filter_Coeff		0.1f	//电流环滤波

typedef struct {
	float32_t Ia;
	float32_t Ib;
	float32_t Ic;
}Curr_Sampletypedef;

typedef struct {
	float32_t Ia;
	float32_t Ib;
	float32_t Ic;
}UVW_Currenttypedef;

typedef struct {
	float32_t Q;
	float32_t D;
}DQtypedef;

typedef struct {
	float32_t Alpha;
	float32_t Beta;
}AlphaBetatypedef;

typedef struct {
	uint32_t CCR1;
	uint32_t CCR2;
	uint32_t CCR3;
}Sector_CCRCaculatetypedef;

typedef struct {
	float32_t Ta;
	float32_t Tb;
}Vector_TCaculatetypedef;

typedef struct {
	float32_t Iu_Offset;
	float32_t Iv_Offset;
	float32_t Iw_Offset;
}Current_Offsettypedef;

typedef enum {
	MOTOR_ALIGN = 0,        //预定位
    MOTOR_OPEN_CURRENT,     // 开环角度 + 电流闭环强拖
    MOTOR_HALL_CURRENT,     // 霍尔角度 + 固定Iq电流闭环
    MOTOR_SMC_SPEED         // 霍尔角度 + 滑模速度环 + 电流闭环
}Motor_Statetypedef;

extern uint16_t ADCInjectBuff[];			//ADC采集三相电流原始数据
extern float32_t Mech_Angle;				//机械角度
extern float32_t Elec_Angle;				//电角度
extern uint8_t N;						//扇区判断
extern float32_t Theta_Delta;
extern float32_t StatorFilter_Ia;		//
extern float32_t StatorFilter_Ib;		//定子三相电流滤波
extern float32_t StatorFilter_Ic;		//

extern float32_t MotorTarget_rpm;				//电机目标转速
extern float32_t MotorNow_rpm;					//电机当前转速

extern volatile HALL_typedef HALL;		//HALL传感器状态
extern uint8_t State;					//速度环标志位
extern float32_t volatile SMC_Iq;					//滑膜速度计算的Iq
extern volatile Motor_Statetypedef Motor_State;		//电机运动状态enum类型

extern volatile uint32_t ControlTick;					//状态切换计数值
extern volatile uint16_t SpeedLoopCnt;				//速度滑膜计数值

extern Current_Offsettypedef Current_Offset;			//采样偏移
extern Curr_Sampletypedef Curr_Sample;				//ADC采集三相电流实际数据
extern DQtypedef OpenLoopUdq;						//开环U_DQQ
extern AlphaBetatypedef OpenLoopUalbe;				//开环U_alphabeta
extern Sector_CCRCaculatetypedef Sector_CCR;			//扇区CCR
extern Vector_TCaculatetypedef Vector_Dura ;			//扇区作用时间
extern UVW_Currenttypedef StatorI;					//定子三相电流,等于ADC采样的电流
extern AlphaBetatypedef FeedbackCalrk ;				//定子电流clark变换abc---alpha&beta
extern DQtypedef FeedbackParkI;						//定子电流park变换alphbeta---dq
extern PID_t CurrentLoopID;							//电流环---Id
extern PID_t CurrentLoopIQ;							//电流环---Iq
extern SMC_Speedtypedef SMC_Speed;					//滑膜速度环

#endif
