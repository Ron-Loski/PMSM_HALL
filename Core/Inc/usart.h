/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void VOFA_JustFloat_Send3(float ch0, float ch1, float ch2);
void VOFA_JustFloat_Send2(float ch0, float ch1);
void VOFA_JustFloat_Send1(float ch0);
void VOFA_JustFloat_Send4(float ch0, float ch1, float ch2, float ch3);
void VOFA_JustFloat_Send5(float ch0, float ch1, float ch2, float ch3, float ch4);
void VOFA_JustFloat_Send6(float ch0, float ch1, float ch2, float ch3, float ch4, float ch5);
void VOFA_JustFloat_Send7(float ch0, float ch1, float ch2, float ch3, float ch4, float ch5, float ch6);
void VOFA_JustFloat_Send8(float ch0, float ch1, float ch2, float ch3, float ch4, float ch5, float ch6, float ch7);
void VOFA_JustFloat_Send9(float ch0, float ch1, float ch2, float ch3, float ch4, float ch5, float ch6, float ch7, float ch8);
void VOFA_JustFloat_Send10(float ch0, float ch1, float ch2, float ch3, float ch4, float ch5, float ch6, float ch7, float ch8, float ch9);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

