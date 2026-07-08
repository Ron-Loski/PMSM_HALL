#include "Global_Varibles.h"

uint16_t ADCInjectBuff[3] = {0.0f};		
uint16_t ADC_EMFBuff[3] = {0.0f};

float32_t Mech_Angle = 0.0f;
float32_t Elec_Angle = 0.0f;
uint8_t N = 0;

float32_t StatorFilter_Ia = 0.0f;
float32_t StatorFilter_Ib = 0.0f;
float32_t StatorFilter_Ic = 0.0f;

float32_t Theta_Delta = 0.0f;

Current_Offsettypedef Current_Offset = {0.0f};

Vector_TCaculatetypedef Vector_Dura = {0.0f};


Curr_Sampletypedef Curr_Sample = {0.0};

DQtypedef OpenLoopUdq = {
	.D = 0.0f,
	.Q = 2.0f,
};

AlphaBetatypedef OpenLoopUalbe = {0.0f};

Sector_CCRCaculatetypedef Sector_CCR = {0};

AlphaBetatypedef FeedbackCalrk = {0.0f};

DQtypedef FeedbackParkI = {0.0f};

UVW_Currenttypedef StatorI = {0.0f};

PID_t CurrentLoopID = {
	.Target = 0,
	
	.Kp = 8.0f,
	.Ki = 0.01f,
	.Kd = 0.0f,
	
	.OutMax = 30.0f / SQRT_3,
	.OutMin = -30.0f / SQRT_3,
};

PID_t CurrentLoopIQ = {
	.Target = 2.0f,
	
	.Kp = 8.0f,
	.Ki = 0.001f,
	.Kd = 0.0f,
	
	.OutMax = 30.0f / SQRT_3,
	.OutMin = -30.0f / SQRT_3,
};

PID_t SpeedLoop = {
	.Target = 500,
	
	.Kp = 0.009f,
	.Ki = 0.004f,
	.Kd = 0.0f,
	
	.OutMax = 1.5,
	.OutMin = 0.0f,
};

SMC_Speedtypedef SMC_Speed = {
	.c = 1.0f,
	.epsilon = 500.0f,
	.k = 20.0f,
	.J = 1.85e-5f,
	.Kt = 0.042f,
	.B = 0.0f,
	.Ts = 0.0005f,
	.delta = 20.0f,
	
	.iq_max = 4.5,
	.iq_min = -4.5,
};

volatile HALL_typedef HALL = {0};
volatile Motor_Statetypedef Motor_State = MOTOR_OPEN_CURRENT;

float32_t MotorTarget_rpm = 1000;		//电机转速
float32_t MotorNow_rpm = 0.0f;			//电机当前转速

float32_t volatile SMC_Iq = 0.0f;		//速度滑膜控制计算的Iq
uint8_t State = 1;						//速度环调控标志位

volatile uint32_t ControlTick = 0;		//上电初始化HALL,偏移量,强拖和转入闭环标志位
volatile uint16_t SpeedLoopCnt = 0;		//速度调控计数值

float32_t ABZ_AngleMech = 0.0f;			//ABZ编码器机械角度读数
float32_t ABZ_AngleElec = 0.0f;			//ABZ编码器电角度读数



