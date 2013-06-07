/**
  ******************************************************************************
  * @file    LTK_EEPROM.h
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
#ifndef __LTK_EEPROM_H
#define __LTK_EEPROM_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_EEPROM
  * @{
  */

/** @defgroup LTK_EEPROM_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_EEPROM_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_EEPROM_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_EEPROM_Exported_Functions
  * @{
  */
  
void LTK_EEPROM_Write(uint8_t *EEPBuff, uint32_t SubAdd, uint32_t EEPSize);
void LTK_EEPROM_Read(uint8_t *RXEEPBuff, uint32_t SubAdd, uint32_t EEPSize);
/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __LTK_EEPROM_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 
/****************************** leitek.taobao.com *****************************/
