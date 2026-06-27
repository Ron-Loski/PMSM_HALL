#ifndef _PMSM_H_
#define _PMSM_H_

#include "stm32h7xx_hal.h"
#include "tim.h"
#include "Global_Varibles.h"
#include "adc.h"
#include "FOC.h"

void PMSM_BoadEnable(void);
void PMSM_BoadDisable(void);
uint8_t PMSM_CalibADC(Current_Offsettypedef *p);
void PMSM_Init(void);
void PMSM_MotorSample(void);


#endif
