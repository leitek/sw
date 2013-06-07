/**
  ******************************************************************************
  * @file    LTK_IWDG.h
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
#ifndef __LTK_IWDG_H
#define __LTK_IWDG_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_IWDG
  * @{
  */

/** @defgroup LTK_IWDG_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_IWDG_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_IWDG_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_IWDG_Exported_Functions
  * @{
  */
void LTK_IWDG_Init(uint8_t IWDG_Prescaler, uint16_t Reload);
 
/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __LTK_IWDG_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 
/****************************** leitek.taobao.com *****************************/
