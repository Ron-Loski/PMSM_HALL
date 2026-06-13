#include "Global_Varibles.h"

uint16_t ADCInjectBuff[3] = {0.0f};		

float32_t Mech_Angle = 0.0f;
float32_t Elec_Angle = 0.0f;
uint8_t N = 0;

float32_t StatorFilter_Ia = 0.0f;
float32_t StatorFilter_Ib = 0.0f;
float32_t StatorFilter_Ic = 0.0f;


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
	
	.OutMax = 5.0f,
	.OutMin = -5.0f,
};

PID_t CurrentLoopIQ = {
	.Target = 2.0f,
	
	.Kp = 10.0f,
	.Ki = 0.001f,
	.Kd = 0.0f,
	
	.OutMax = 5.0f,
	.OutMin = -5.0f,
};

volatile HALL_typedef HALL = {0};










