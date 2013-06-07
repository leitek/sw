/**
  ******************************************************************************
  * @file    LTK_SysTick.h
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
#ifndef __LTK_SYSTICK_H
#define __LTK_SYSTICK_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#ifdef LTK_FREERTOS
#include "FreeRTOS.h"
#include "task.h"
#endif
/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_SYSTICK
  * @{
  */

/** @defgroup SYSTICK_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup SYSTICK_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup SYSTICK_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup SYSTICK_Exported_Functions
  * @{
  */
#ifndef LTK_FREERTOS
void LTK_SysTick_Delay(__IO uint32_t nTime);
void LTK_SysTick_Init(void);
void LTK_Set_TimingDelay(uint32_t __IO timing_Delay);
uint32_t LTK_Get_TimingDelay(void);
void LTK_Decrease_TimingDelay(void);
#else
#define LTK_SysTick_Delay vTaskDelay
#endif
/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __LTK_SYSTICK_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 

/****************************** leitek.taobao.com *****************************/
