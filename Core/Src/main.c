/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include "PMSM.h"
#include "Global_Varibles.h"
#include "FOC.h"
#include "PMSM.h"
#include "HALL.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint32_t Count = 0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  MX_TIM5_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  PMSM_BoadEnable();
//  PMSM_CalibADC(&Current_Offset);
  PMSM_Init();
  HALL_Init();
  
  
  
  while (1)
  {
//	  printf("%d,%d,%d\r\n", ADCInjectBuff[0], ADCInjectBuff[1], ADCInjectBuff[2]);
//	  printf("%f,%f,%f\r\n", Curr_Sample.Ia, Curr_Sample.Ib, Curr_Sample.Ic);
//	  printf("%d,%d,%d\r\n", Sector_CCR.CCR1, Sector_CCR.CCR2, Sector_CCR.CCR3);
//	  printf("%f,%f\r\n", HALL.Theta_fit, Mech_Angle);
	  
//	  VOFA_JustFloat_Send1(HALL.State);
//	  VOFA_JustFloat_Send2(HALL.State, Mech_Angle);
//	  VOFA_JustFloat_Send2(HALL.Theta_fit, Mech_Angle);
//	  VOFA_JustFloat_Send2(FeedbackCalrk.Alpha, FeedbackCalrk.Beta);	  
//	  VOFA_JustFloat_Send3(HALL.State, Mech_Angle, HALL.Theta[0]);
//	  VOFA_JustFloat_Send3( Current_Offset.Iu_Offset, Current_Offset.Iv_Offset, Current_Offset.Iw_Offset);
//	  VOFA_JustFloat_Send3( ADCInjectBuff[0], ADCInjectBuff[1], ADCInjectBuff[2]);
//	  VOFA_JustFloat_Send3(Curr_Sample.Ia, Curr_Sample.Ib, Curr_Sample.Ic);
//	  VOFA_JustFloat_Send3(StatorI.Ia, StatorI.Ib, StatorI.Ic);
//	  VOFA_JustFloat_Send3(CurrentLoopID.Actual, CurrentLoopID.Target, CurrentLoopID.Error0);
//	  VOFA_JustFloat_Send3(CurrentLoopIQ.Actual, CurrentLoopIQ.Target, CurrentLoopIQ.Error0);
//	  VOFA_JustFloat_Send3(Sector_CCR.CCR1, Sector_CCR.CCR2, Sector_CCR.CCR3);
	  VOFA_JustFloat_Send3(HALL.State, Mech_Angle, HALL.Speed_AvgOmega);
	  
//	  VOFA_JustFloat_Send4(FeedbackCalrk.Alpha, FeedbackCalrk.Beta, FeedbackParkI.D, FeedbackParkI.Q);
//	  VOFA_JustFloat_Send4(CurrentLoopID.Actual, CurrentLoopID.Target, CurrentLoopIQ.Actual, CurrentLoopIQ.Target);
//	  VOFA_JustFloat_Send8(FeedbackParkI.D, FeedbackParkI.Q, CurrentLoopID.Actual, CurrentLoopID.Target, CurrentLoopID.Error0, CurrentLoopIQ.Actual, CurrentLoopIQ.Target, CurrentLoopIQ.Error0);	 

//	  VOFA_JustFloat_Send9(HALL.State, Mech_Angle, Elec_Angle, HALL.Count[0], HALL.Count[1], HALL.Count[2], HALL.Count[3], HALL.Count[4], HALL.Count[5]);
	  
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	if (hadc == &hadc1)
	{
		PMSM_MotorSample();
		
		/*电流环Id---PI控制*/
		CurrentLoopID.Actual = FeedbackParkI.D;
		PID_Update(&CurrentLoopID);
		OpenLoopUdq.D = CurrentLoopID.Out;
		
		/*电流环Iq---PI控制*/
		CurrentLoopIQ.Actual = FeedbackParkI.Q;
		PID_Update(&CurrentLoopIQ);
		OpenLoopUdq.Q = CurrentLoopIQ.Out;
		
		FOC_AntiPark(&OpenLoopUdq, &OpenLoopUalbe,Elec_Angle);
		/*扇区判断*/
		N = FOC_SectorJudege(OpenLoopUalbe.Alpha, OpenLoopUalbe.Beta);
		/*矢量作用时间*/
		Vector_Dura = FOC_VectorCaculate(OpenLoopUalbe.Alpha,  OpenLoopUalbe.Beta, N, 24, Tpwm);
		Sector_CCR = FOC_SectorCCRCaculate(N, Vector_Dura, Tpwm);
		TIM1->CCR1 = Sector_CCR.CCR1;
		TIM1->CCR2 = Sector_CCR.CCR2;
		TIM1->CCR3 = Sector_CCR.CCR3;
	}
}





int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}
/* USER CODE END 4 */

 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
