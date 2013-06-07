/**
  ******************************************************************************
  * @file    LTK_USBMouse.c
  * @author  MCD Application Team
  * @version V4.3.0
  * @date    10/15/2010
  * @brief   STM32xx-EVAL abstraction layer. 
  *          This file should be added to the main application to use the provided
  *          functions that manage Leds, push-buttons, COM ports and low level 
  *          HW resources initialization of the different modules available on
  *          STM32 evaluation boards from STMicroelectronics.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * COPYRIGHT 2010 STMicroelectronicsCOPYRIGHT
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "LTK_USBMouse.h"
#include "LTK_RCC.h"
#include "LTK_GPIO.h"
#include "LTK_NVIC_API.h"
#include "LTK_EXTI.h"
#include "usb_lib.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_USBMouse
  * @{
  */ 

/** @defgroup LTK_USBMouse_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_USBMouse_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup LTK_USBMouse_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup LTK_USBMouse_Private_Variables
  * @{
  */ 

/**
  * @}
  */

/** @defgroup LTK_USBMouse_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_USBMouse_Private_Functions
  * @{
  */

/**
  * @brief  Initialize USBMouse.
  * @param  None
  * @retval None
  */
void LTK_USBMouse_Init(void)
{
    LTK_USB_NVIC_Init();
    LTK_USB_RCC_Init();
    LTK_USB_EXTI_Init();
    USB_Init();
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
    
/******************* (C) COPYRIGHT 2010 STMicroelectronics ***************************/
