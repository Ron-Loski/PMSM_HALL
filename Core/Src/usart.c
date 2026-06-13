/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
#include <string.h>
/* USER CODE END 0 */

UART_HandleTypeDef huart1;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 1000000;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1;
    PeriphClkInitStruct.Usart16ClockSelection = RCC_USART16CLKSOURCE_D2PCLK2;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PB14     ------> USART1_TX
    PB15     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF4_USART1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PB14     ------> USART1_TX
    PB15     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_14|GPIO_PIN_15);

  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
#define VOFA_CH_COUNT 1U

void VOFA_JustFloat_Send1(float ch0)
{
    uint8_t tx_buf[VOFA_CH_COUNT * sizeof(float) + 4U];
    float data[VOFA_CH_COUNT] = {ch0};

    memcpy(tx_buf, data, sizeof(data));

    tx_buf[sizeof(data) + 0U] = 0x00U;
    tx_buf[sizeof(data) + 1U] = 0x00U;
    tx_buf[sizeof(data) + 2U] = 0x80U;
    tx_buf[sizeof(data) + 3U] = 0x7FU;

    HAL_UART_Transmit(&huart1, tx_buf, (uint16_t)sizeof(tx_buf), 10U);
}

#define VOFA_CH_COUNT2 2U

void VOFA_JustFloat_Send2(float ch0, float ch1)
{
    uint8_t tx_buf[VOFA_CH_COUNT2 * sizeof(float) + 4U];
    float data[VOFA_CH_COUNT2] = {ch0, ch1};

    memcpy(tx_buf, data, sizeof(data));

    tx_buf[sizeof(data) + 0U] = 0x00U;
    tx_buf[sizeof(data) + 1U] = 0x00U;
    tx_buf[sizeof(data) + 2U] = 0x80U;
    tx_buf[sizeof(data) + 3U] = 0x7FU;

    HAL_UART_Transmit(&huart1, tx_buf, (uint16_t)sizeof(tx_buf), 10U);
}

#define VOFA_CH_COUNT3 3U

void VOFA_JustFloat_Send3(float ch0, float ch1, float ch2)
{
    uint8_t tx_buf[VOFA_CH_COUNT3 * sizeof(float) + 4U];
    float data[VOFA_CH_COUNT3] = {ch0, ch1, ch2};

    memcpy(tx_buf, data, sizeof(data));

    tx_buf[sizeof(data) + 0U] = 0x00U;
    tx_buf[sizeof(data) + 1U] = 0x00U;
    tx_buf[sizeof(data) + 2U] = 0x80U;
    tx_buf[sizeof(data) + 3U] = 0x7FU;

    HAL_UART_Transmit(&huart1, tx_buf, (uint16_t)sizeof(tx_buf), 10U);
}

#define VOFA_CH_COUNT4 4U

void VOFA_JustFloat_Send4(float ch0, float ch1, float ch2, float ch3)
{
    uint8_t tx_buf[VOFA_CH_COUNT4 * sizeof(float) + 4U];
    float data[VOFA_CH_COUNT4] = {ch0, ch1, ch2, ch3};

    memcpy(tx_buf, data, sizeof(data));

    tx_buf[sizeof(data) + 0U] = 0x00U;
    tx_buf[sizeof(data) + 1U] = 0x00U;
    tx_buf[sizeof(data) + 2U] = 0x80U;
    tx_buf[sizeof(data) + 3U] = 0x7FU;

    HAL_UART_Transmit(&huart1, tx_buf, (uint16_t)sizeof(tx_buf), 10U);
}

#define VOFA_CH_COUNT5 5U

void VOFA_JustFloat_Send5(float ch0, float ch1, float ch2, float ch3, float ch4)
{
    uint8_t tx_buf[VOFA_CH_COUNT5 * sizeof(float) + 4U];
    float data[VOFA_CH_COUNT5] = {ch0, ch1, ch2, ch3, ch4};

    memcpy(tx_buf, data, sizeof(data));

    tx_buf[sizeof(data) + 0U] = 0x00U;
    tx_buf[sizeof(data) + 1U] = 0x00U;
    tx_buf[sizeof(data) + 2U] = 0x80U;
    tx_buf[sizeof(data) + 3U] = 0x7FU;

    HAL_UART_Transmit(&huart1, tx_buf, (uint16_t)sizeof(tx_buf), 10U);
}

#define VOFA_CH_COUNT6 6U

void VOFA_JustFloat_Send6(float ch0, float ch1, float ch2, float ch3, float ch4, float ch5)
{
    uint8_t tx_buf[VOFA_CH_COUNT6 * sizeof(float) + 4U];
    float data[VOFA_CH_COUNT6] = {ch0, ch1, ch2, ch3, ch4, ch5};

    memcpy(tx_buf, data, sizeof(data));

    tx_buf[sizeof(data) + 0U] = 0x00U;
    tx_buf[sizeof(data) + 1U] = 0x00U;
    tx_buf[sizeof(data) + 2U] = 0x80U;
    tx_buf[sizeof(data) + 3U] = 0x7FU;

    HAL_UART_Transmit(&huart1, tx_buf, (uint16_t)sizeof(tx_buf), 10U);
}

#define VOFA_CH_COUNT7 7U

void VOFA_JustFloat_Send7(float ch0, float ch1, float ch2, float ch3, float ch4, float ch5, float ch6)
{
    uint8_t tx_buf[VOFA_CH_COUNT7 * sizeof(float) + 4U];
    float data[VOFA_CH_COUNT7] = {ch0, ch1, ch2, ch3, ch4, ch5, ch6};

    memcpy(tx_buf, data, sizeof(data));

    tx_buf[sizeof(data) + 0U] = 0x00U;
    tx_buf[sizeof(data) + 1U] = 0x00U;
    tx_buf[sizeof(data) + 2U] = 0x80U;
    tx_buf[sizeof(data) + 3U] = 0x7FU;

    HAL_UART_Transmit(&huart1, tx_buf, (uint16_t)sizeof(tx_buf), 10U);
}

#define VOFA_CH_COUNT8 8U

void VOFA_JustFloat_Send8(float ch0, float ch1, float ch2, float ch3, float ch4, float ch5, float ch6, float ch7)
{
    uint8_t tx_buf[VOFA_CH_COUNT8 * sizeof(float) + 4U];
    float data[VOFA_CH_COUNT8] = {ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7};

    memcpy(tx_buf, data, sizeof(data));

    tx_buf[sizeof(data) + 0U] = 0x00U;
    tx_buf[sizeof(data) + 1U] = 0x00U;
    tx_buf[sizeof(data) + 2U] = 0x80U;
    tx_buf[sizeof(data) + 3U] = 0x7FU;

    HAL_UART_Transmit(&huart1, tx_buf, (uint16_t)sizeof(tx_buf), 10U);
}

#define VOFA_CH_COUNT9 9U

void VOFA_JustFloat_Send9(float ch0, float ch1, float ch2, float ch3, float ch4, float ch5, float ch6, float ch7, float ch8)
{
    uint8_t tx_buf[VOFA_CH_COUNT9 * sizeof(float) + 4U];
    float data[VOFA_CH_COUNT9] = {ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8};

    memcpy(tx_buf, data, sizeof(data));

    tx_buf[sizeof(data) + 0U] = 0x00U;
    tx_buf[sizeof(data) + 1U] = 0x00U;
    tx_buf[sizeof(data) + 2U] = 0x80U;
    tx_buf[sizeof(data) + 3U] = 0x7FU;

    HAL_UART_Transmit(&huart1, tx_buf, (uint16_t)sizeof(tx_buf), 10U);
}

#define VOFA_CH_COUNT10 10U

void VOFA_JustFloat_Send10(float ch0, float ch1, float ch2, float ch3, float ch4, float ch5, float ch6, float ch7, float ch8, float ch9)
{
    uint8_t tx_buf[VOFA_CH_COUNT10 * sizeof(float) + 4U];
    float data[VOFA_CH_COUNT10] = {ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9};

    memcpy(tx_buf, data, sizeof(data));

    tx_buf[sizeof(data) + 0U] = 0x00U;
    tx_buf[sizeof(data) + 1U] = 0x00U;
    tx_buf[sizeof(data) + 2U] = 0x80U;
    tx_buf[sizeof(data) + 3U] = 0x7FU;

    HAL_UART_Transmit(&huart1, tx_buf, (uint16_t)sizeof(tx_buf), 10U);
}
/* USER CODE END 1 */
