/**
  ******************************************************************************
  * @file    LTK_Button_EXTI.c
  * @author  leitek (leitek.taobao.com)
  * @version V1.0.0
  * @brief   LTK middleware. 
  *          This file provides button EXTI middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * COPYRIGHT leitek.taobao.com
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "LTK_Button_EXTI.h"
#include "LTK_GPIO.h"
#include "LTK_RCC.h"
#include "LTK_EXTI.h"
#include "LTK_NVIC_API.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_Button_EXTI
  * @{
  */ 

/** @defgroup LTK_Button_EXTI_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_Button_EXTI_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup LTK_Button_EXTI_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup LTK_Button_EXTI_Private_Variables
  * @{
  */ 

/**
  * @}
  */

/** @defgroup LTK_Button_EXTI_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_Button_EXTI_Private_Functions
  * @{
  */
  
/**
  * @brief  Initialize Button_EXTI. 
  * @param  None
  * @retval None
  */
void LTK_Button_Init()
{
    LTK_Button_RCC_Init();
    LTK_Button_GPIO_Init();
    LTK_Button_NVIC_Init();
    LTK_Button_EXTI_Init();
}

/**
  * @brief  get the state of button. 
  * @param  Button: the button which you want to get the state from.
  * @retval the state of the button.
  */
uint8_t LTK_Button_State(uint8_t Button)
{
    if (Button == 0)
        return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1);
    else
        return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2);
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
