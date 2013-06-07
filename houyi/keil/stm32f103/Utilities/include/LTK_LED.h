/**
  ******************************************************************************
  * @file    LTK_LED.h
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
#ifndef __LTK_LED_H
#define __LTK_LED_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_LED
  * @{
  */

/** @defgroup LTK_LED_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_LED_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_LED_Exported_Macros
  * @{
  */
  
/**
  * @}
  */

/** @defgroup LTK_LED_Exported_Functions
  * @{
  */
  
void LTK_LED_Init(void); 
void LTK_LED_Set(uint8_t LED, uint8_t value);
void LTK_LED_Toggle(uint8_t LED);


/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __LTK_LED_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 

/****************************** leitek.taobao.com *****************************/
