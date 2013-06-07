/**
  ******************************************************************************
  * @file    LTK_RTC.h
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
#ifndef __LTK_RTC_H
#define __LTK_RTC_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_RTC
  * @{
  */

/** @defgroup LTK_RTC_Exported_Types
  * @{
  */
typedef struct 
{
    uint16_t year;  /* 1..4095 */
    uint8_t  month; /* 1..12 */
    uint8_t  mday;  /* 1..31 */
    uint8_t  wday;  /* 0..6, Sunday = 0*/
    uint8_t  hour;  /* 0..23 */
    uint8_t  min;   /* 0..59 */
    uint8_t  sec;   /* 0..59 */
    //uint8_t  dst;   /* 0 Winter, !=0 Summer */
} RTC_t;

/**
  * @}
  */

/** @defgroup LTK_RTC_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_RTC_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_RTC_Exported_Functions
  * @{
  */
void LTK_RTC_Init(void); 
void LTK_RTC_gettime (RTC_t*);              /* Get time */
void LTK_RTC_settime (const RTC_t*);        /* Set time */

 
/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __LTK_RTC_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 
/****************************** leitek.taobao.com *****************************/
