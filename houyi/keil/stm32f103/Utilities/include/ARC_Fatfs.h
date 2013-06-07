/**
  ******************************************************************************
  * @file    LTK_Fatfs.h
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
#ifndef __LTK_FATFS_H
#define __LTK_FATFS_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_FATFS
  * @{
  */

/** @defgroup LTK_FATFS_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_FATFS_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_FATFS_Exported_Macros
  * @{
  */
#define FI 1
#define DI 2
/**
  * @}
  */

/** @defgroup LTK_FATFS_Exported_Functions
  * @{
  */

void LTK_fat_menu_init(void);

void LTK_Sys_Soft_Reset(void);

void LTK_format_disk(void);
void LTK_creat_file(void);
void LTK_delete_file(void);
void LTK_list_file(void);
void LTK_get_disk_info(void);
void LTK_creat_dir(void);
void LTK_edit_file(void);
void LTK_read_file(void);

/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __LTK_FATFS_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/****************************** leitek.taobao.com *****************************/
