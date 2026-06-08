#ifndef __FOC_H_
#define __FOC_H_

#include "stm32h7xx_hal.h"
#include "Global_Varibles.h"

void FOC_Clark(UVW_Currenttypedef *p1, AlphaBetatypedef *p2);
void FOC_Park(DQtypedef *p1, AlphaBetatypedef *p2, float32_t Elec_theta);
void FOC_AntiPark(DQtypedef *p1, AlphaBetatypedef *p2, float32_t Elec_theta);
void FOC_AntiClark(AlphaBetatypedef *p1, UVW_Currenttypedef *p2);
uint8_t FOC_SectorJudege(float32_t U_alpha, float32_t U_beta);
Vector_TCaculatetypedef FOC_VectorCaculate(float32_t U_alpha, float32_t U_beta,uint8_t N, float32_t Udc, float32_t T_pwm);	//此处Tpwm为PWM的周期计数;
Sector_CCRCaculatetypedef FOC_SectorCCRCaculate(uint8_t N, Vector_TCaculatetypedef p, float32_t T_pwm);

#endif
