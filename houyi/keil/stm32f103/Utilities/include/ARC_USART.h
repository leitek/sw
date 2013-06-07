/**
  ******************************************************************************
  * @file    LTK_USART.h
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
#ifndef __LTK_USART_H
#define __LTK_USART_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
//#include <stdio.h>

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_USART
  * @{
  */

/** @defgroup LTK_USART_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_USART_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_USART_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_USART_Exported_Functions
  * @{
  */
void LTK_COM_Init(void);
#ifdef USART1_IRQ
void LTK_COM_NVIC_Init(void);
#endif
/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __LTK_USART_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 
/****************************** leitek.taobao.com *****************************/
