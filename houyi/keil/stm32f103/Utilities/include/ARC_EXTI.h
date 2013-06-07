/**
  ******************************************************************************
  * @file    LTK_EXTI.h
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
#ifndef __LTK_EXTI_H
#define __LTK_EXTI_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_EXTI
  * @{
  */

/** @defgroup LTK_EXTI_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_EXTI_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_EXTI_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_EXTI_Exported_Functions
  * @{
  */
  
void LTK_Button_EXTI_Init(void);
void LTK_TouchScreen_EXTI_Init(void);
void LTK_USB_EXTI_Init(void);

/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __LTK_EXTI_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 
/****************************** leitek.taobao.com *****************************/
