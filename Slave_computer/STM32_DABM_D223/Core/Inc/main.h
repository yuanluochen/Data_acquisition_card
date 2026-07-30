/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdint.h>
#include 	<ctype.h>
#include "stdio.h"	
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>	
#include <stdbool.h>
#include <stddef.h>

#include <rtthread.h>
#include "userThread.h"
#include "typeDefine.h"

#include "nvmData.h"
#include "userQspiAdc.h"
#include "crc16.h"
#include "fram.h"
#include "adcFunction.h"
#include "msgStruct.h"

#include "usbMsg.h"
#include "userQspi.h"
#include "regFPGA.h"
#include "ddsDAC.h"
#include "dio.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
uint8_t CDC_Transmit_HS(uint8_t* Buf, uint16_t Len);

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define USB_RST_Pin GPIO_PIN_3
#define USB_RST_GPIO_Port GPIOE
#define FPGA_SPI_CS_Pin GPIO_PIN_4
#define FPGA_SPI_CS_GPIO_Port GPIOA
#define AD_RESET_Pin GPIO_PIN_8
#define AD_RESET_GPIO_Port GPIOD
#define AD_RANGE_Pin GPIO_PIN_9
#define AD_RANGE_GPIO_Port GPIOD
#define AD_OS_Pin GPIO_PIN_10
#define AD_OS_GPIO_Port GPIOD
#define DA_CS_Pin GPIO_PIN_10
#define DA_CS_GPIO_Port GPIOA
#define DOUT_1_Pin GPIO_PIN_11
#define DOUT_1_GPIO_Port GPIOA
#define DOUT_2_Pin GPIO_PIN_12
#define DOUT_2_GPIO_Port GPIOA
#define FRAM_CS_Pin GPIO_PIN_15
#define FRAM_CS_GPIO_Port GPIOA
#define BOOT_HIGH_Pin GPIO_PIN_7
#define BOOT_HIGH_GPIO_Port GPIOD
#define LED_USB_Pin GPIO_PIN_7
#define LED_USB_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
