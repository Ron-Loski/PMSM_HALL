#include "FOC.h"

void FOC_Clark(UVW_Currenttypedef *p1, AlphaBetatypedef *p2)
{
	p2->Alpha = p1->Ia;
	p2->Beta = (p1->Ia + 2.0f * p1->Ib) / sqrtf(3.0f);
}

void FOC_Park(DQtypedef *p1, AlphaBetatypedef *p2, float32_t Elec_theta)
{
	p1->Q = p2->Beta * cosf(Elec_theta) - p2->Alpha * sinf(Elec_theta);
	p1->D = p2->Beta * sinf(Elec_theta) + p2->Alpha * cosf(Elec_theta);
}

void FOC_AntiPark(DQtypedef *p1, AlphaBetatypedef *p2, float32_t Elec_theta)
{	
	p2->Alpha = p1->D * cosf(Elec_theta) - p1->Q * sinf(Elec_theta);
	p2->Beta = p1->D * sinf(Elec_theta) + p1->Q * cosf(Elec_theta);
}

void FOC_AntiClark(AlphaBetatypedef *p1, UVW_Currenttypedef *p2)
{
	p2->Ia = p1->Alpha;
	p2->Ib =  -0.5f * p1->Alpha + (sqrtf(3.0f) / 2.0f) * p1->Beta;
	p2->Ic = -0.5f * p1->Alpha - (sqrtf(3.0f) / 2.0f) * p1->Beta;
}

uint8_t FOC_SectorJudege(float32_t U_alpha, float32_t U_beta)
{
	float32_t A = U_beta;
	float32_t B = sqrt(3) * U_alpha - U_beta;
	float32_t C = -sqrt(3) * U_alpha - U_beta;
	
	uint8_t N = 0;
	if (A > 0.0f){
		N = N + 1;
	}
	if(B > 0.0f){
		N = N + 2;
	}	
	if (C > 0.0f){
		N = N + 4;
	}
	return N;
}

Vector_TCaculatetypedef FOC_VectorCaculate(float32_t U_alpha, float32_t U_beta, uint8_t N, float32_t Udc, float32_t T_pwm)	//此处Tpwm为PWM的周期计数值
{
	Vector_TCaculatetypedef p = {0.0f};
	float32_t X = (sqrt(3) * T_pwm) / Udc * U_beta;
	float32_t Y = (sqrt(3) * T_pwm) / Udc * ((sqrt(3) / 2.0f) * U_alpha - 0.5f * U_beta);
	float32_t Z = (sqrt(3) * T_pwm) / Udc * (-(sqrt(3) / 2.0f) * U_alpha - 0.5f * U_beta);

	if (N == 3){ //{the first vector%}
	   p.Ta = Y;
	   p.Tb = X;
	}
	if (N == 1){ //{the second vector%}
	   p.Ta = -Y;
	   p.Tb = -Z;
	}
	if (N == 5){ //{the third vector%}
	   p.Ta = X;
	   p.Tb = Z;
	}
	if (N == 4){ //{the fourth vector%}
	   p.Ta = -X;
	   p.Tb = -Y;
	}
	if (N == 6){ //{the fifth vector%}
	   p.Ta = Z;
	   p.Tb = Y;
	}
	if (N == 2){ //{the sixth vector%}
	   p.Ta = -Z;
	   p.Tb = -X;
	}
	
	return p;
}

Sector_CCRCaculatetypedef FOC_SectorCCRCaculate(uint8_t N, Vector_TCaculatetypedef p, float32_t T_pwm)
{
	Sector_CCRCaculatetypedef t = {0};
	float32_t Ta = p.Ta;
	float32_t Tb = p.Tb;
	
	float32_t Ttemp = Ta + Tb;
	if (Ttemp > T_pwm){
		Ta = Ta / Ttemp * T_pwm;
		Tb = Tb / Ttemp * T_pwm;
	}

	volatile float32_t value1 = (T_pwm - Ta - Tb) / 4.0;
	volatile float32_t value2 = value1 + Ta / 2.0;
	volatile float32_t value3 = value2 + Tb / 2.0;

	switch(N)       //From top to bottom represents each sector
	{
		case 3:
			t.CCR1 = value1;
			t.CCR2 = value2;
			t.CCR3 = value3;
			break;
		case 1:
			t.CCR1 = value2;
			t.CCR2 = value1;
			t.CCR3 = value3;
			break;
		case 5:
			t.CCR1 = value3;
			t.CCR2 = value1;
			t.CCR3 = value2;
			break;
		case 4:
			t.CCR1 = value3;
			t.CCR2 = value2;
			t.CCR3 = value1;
			break;
		case 6:
			t.CCR1 = value2;
			t.CCR2 = value3;
			t.CCR3 = value1;
			break;
		case 2:
			t.CCR1 = value1;
			t.CCR2 = value3;
			t.CCR3 = value2;
			break;
		default:
			break;
	}
	return t;
}











