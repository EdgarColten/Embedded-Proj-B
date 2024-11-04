/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32l4xx_hal.h"
#include "stm32l4xx_ll_system.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_exti.h"
#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_cortex.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_utils.h"
#include "stm32l4xx_ll_pwr.h"
#include "stm32l4xx_ll_dma.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MCO_Pin LL_GPIO_PIN_0
#define MCO_GPIO_Port GPIOA
#define VCP_TX_Pin LL_GPIO_PIN_2
#define VCP_TX_GPIO_Port GPIOA
#define SSD1306_DC_Pin LL_GPIO_PIN_3
#define SSD1306_DC_GPIO_Port GPIOA
#define SPI_CS_Pin LL_GPIO_PIN_6
#define SPI_CS_GPIO_Port GPIOA
#define Freq_knob_B_Pin LL_GPIO_PIN_0
#define Freq_knob_B_GPIO_Port GPIOB
#define Delay_knob_A_Pin LL_GPIO_PIN_1
#define Delay_knob_A_GPIO_Port GPIOB
#define SPI_RST_Pin LL_GPIO_PIN_8
#define SPI_RST_GPIO_Port GPIOA
#define channel_select_sw_Pin LL_GPIO_PIN_9
#define channel_select_sw_GPIO_Port GPIOA
#define shape_btn_Pin LL_GPIO_PIN_10
#define shape_btn_GPIO_Port GPIOA
#define Delay_knob_B_Pin LL_GPIO_PIN_11
#define Delay_knob_B_GPIO_Port GPIOA
#define Freq_knob_A_Pin LL_GPIO_PIN_12
#define Freq_knob_A_GPIO_Port GPIOA
#define SWDIO_Pin LL_GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin LL_GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define VCP_RX_Pin LL_GPIO_PIN_15
#define VCP_RX_GPIO_Port GPIOA
#define LD3_Pin LL_GPIO_PIN_3
#define LD3_GPIO_Port GPIOB
#define Signal_Pass_LED_Pin LL_GPIO_PIN_4
#define Signal_Pass_LED_GPIO_Port GPIOB
#define Signal_Fail_LED_Pin LL_GPIO_PIN_5
#define Signal_Fail_LED_GPIO_Port GPIOB
#define Amp_knob_B_Pin LL_GPIO_PIN_6
#define Amp_knob_B_GPIO_Port GPIOB
#define Amp_knob_A_Pin LL_GPIO_PIN_7
#define Amp_knob_A_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
