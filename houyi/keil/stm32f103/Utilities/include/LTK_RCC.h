/**
  ******************************************************************************
  * @file    LTK_RCC.h
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
#ifndef __LTK_RCC_H
#define __LTK_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_RCC
  * @{
  */

/** @defgroup LTK_RCC_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_RCC_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_RCC_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_RCC_Exported_Functions
  * @{
  */
  
void LTK_LED_RCC_Init(void);
void LTK_Button_RCC_Init(void);
void LTK_SPI_RCC_Init(void);
void LTK_LCD_RCC_Init(void);
void LTK_I2C_RCC_Init(void);
void LTK_TouchScreen_RCC_Init(void);
void LTK_TIM_PWM_RCC_Init(void);
void LTK_COM_RCC_Init(void);
void LTK_ADC_RCC_Init(void);
void LTK_DMA1_RCC_Init(void);
void LTK_USB_RCC_Init(void);

/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __LTK_RCC_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/****************************** leitek.taobao.com *****************************/
