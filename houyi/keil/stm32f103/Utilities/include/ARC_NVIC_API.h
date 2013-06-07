/**
  ******************************************************************************
  * @file    LTK_NVIC_API.h
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
#ifndef __LTK_NVIC_API_H
#define __LTK_NVIC_API_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_NVIC_API
  * @{
  */

/** @defgroup LTK_NVIC_API_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_NVIC_API_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_NVIC_API_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_NVIC_API_Exported_Functions
  * @{
  */
  
void LTK_NVIC_API_Init(void); 
void LTK_Button_NVIC_Init(void);
void LTK_I2C_NVIC_Init(void);
void LTK_TouchScreen_NVIC_Init(void);
void LTK_USB_NVIC_Init(void);
void LTK_ADC_NVIC_Init(void);

/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __LTK_NVIC_API_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 

/****************************** leitek.taobao.com *****************************/
