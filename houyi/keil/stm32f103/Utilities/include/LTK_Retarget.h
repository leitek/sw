/**
  ******************************************************************************
  * @file    LTK_Retarget.h
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
#ifndef __LTK_RETARGET_H
#define __LTK_RETARGET_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_RETARGET
  * @{
  */

/** @defgroup LTK_RETARGET_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_RETARGET_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_RETARGET_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_RETARGET_Exported_Functions
  * @{
  */
int fputc(int ch, FILE *f);
int fgetc(FILE *f);
int ferror(FILE *f);
void _ttywrch(int ch);
void _sys_exit(int return_code);

/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __LTK_RETARGET_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 

/****************************** leitek.taobao.com *****************************/
