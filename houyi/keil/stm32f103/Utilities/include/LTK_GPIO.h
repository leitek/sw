/**
  ******************************************************************************
  * @file    LTK_GPIO.h
  * @author  leitek (leitek.taobao.com)
  * @version V1.0.0
  * @brief   Header files for middleware.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * COPYRIGHT leitek.taobao.com
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LTK_GPIO_H
#define __LTK_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "LTK_LED.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_GPIO
  * @{
  */

/** @defgroup LTK_GPIO_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_GPIO_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_GPIO_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_GPIO_Exported_Functions
  * @{
  */

void LTK_LED_GPIO_Init(void);
void LTK_Button_GPIO_Init(void);
void LTK_SPI_GPIO_Init(void);
void LTK_LCD_GPIO_Init(void);
void LTK_I2C_GPIO_Init(void);
void LTK_TouchScreen_GPIO_Init(void);
void LTK_COM_GPIO_Init(void);
void LTK_SD_GPIO_Init(void);
void LTK_ADC_GPIO_Init(void);
void LTK_TIM_PWM_GPIO_Init(void);

/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __LTK_GPIO_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 

/****************************** leitek.taobao.com *****************************/
