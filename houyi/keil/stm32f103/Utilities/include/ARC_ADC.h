/**
  ******************************************************************************
  * @file    LTK_ADC.h
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
#ifndef __LTK_ADC_H
#define __LTK_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_ADC
  * @{
  */

/** @defgroup LTK_ADC_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_ADC_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_ADC_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_ADC_Exported_Functions
  * @{
  */
void LTK_ADC_Init(void); 
void LTK_ADC_DMA_Init(uint16_t *MemoryBaseAddr, uint32_t BufferSize);

/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __LTK_ADC_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 
/****************************** leitek.taobao.com *****************************/
