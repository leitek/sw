/**
  ******************************************************************************
  * @file    LTK_DAM.h
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
#ifndef __LTK_DAM_H
#define __LTK_DAM_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_DAM
  * @{
  */

/** @defgroup LTK_DAM_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_DAM_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_DAM_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_DAM_Exported_Functions
  * @{
  */
void LTK_DMA1_Ch2_Param_Init(const uint8_t *MemoryBaseAddr, uint32_t BufferSize);
void LTK_DMA1_Ch3_Param_Init(const uint8_t *MemoryBaseAddr, uint32_t BufferSize, uint32_t memIncEnable);
void LTK_DMA1_Ch4_Param_Init(const uint8_t *MemoryBaseAddr, uint32_t BufferSize);

/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __LTK_DAM_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 
/****************************** leitek.taobao.com *****************************/
