/**
  ******************************************************************************
  * @file    LTK_Device.c
  * @author  leitek (leitek.taobao.com)
  * @version V1.0.0
  * @brief   LTK middleware. 
  *          This file provides ADC middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * COPYRIGHT leitek.taobao.com
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "LTK_Device.h"
#include <stdio.h>

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_DEVICE
  * @{
  */ 

/** @defgroup LTK_DEVICE_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_DEVICE_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup LTK_DEVICE_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup LTK_DEVICE_Private_Variables
  * @{
  */ 

/**
  * @}
  */

/** @defgroup LTK_DEVICE_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_DEVICE_Private_Functions
  * @{
  */
  
/**
  * @brief  Get the unique serial number of the chip.
  * @param  None
  * @retval None
  */
void LTK_Get_SerialNum(void)
{
    uint32_t Device_Serial0, Device_Serial1, Device_Serial2;

    Device_Serial0 = *(__I uint32_t*)(0x1FFFF7E8);
    Device_Serial1 = *(__I uint32_t*)(0x1FFFF7EC);
    Device_Serial2 = *(__I uint32_t*)(0x1FFFF7F0);
    printf("ST device ID: 0x%08X", Device_Serial0);
    printf("%08X", Device_Serial1);
    printf("%08X\n", Device_Serial2);
}

/**
  * @}
  */

/**
  * @}
  */
  
/**
  * @}
  */  
/****************************** leitek.taobao.com *****************************/
