/**
  ******************************************************************************
  * @file    LTK_LED.c
  * @author  leitek (leitek.taobao.com)
  * @version V1.0.0
  * @brief   LTK middleware. 
  *          This file provides LED middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * COPYRIGHT leitek.taobao.com
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "LTK_LED.h"
#include "LTK_RCC.h"
#include "LTK_GPIO.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_LED
  * @{
  */ 

/** @defgroup LTK_LED_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_LED_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup LTK_LED_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup LTK_LED_Private_Variables
  * @{
  */ 

/**
  * @}
  */

/** @defgroup LTK_LED_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_LED_Private_Functions
  * @{
  */
  
/**
  * @brief  Initialize LED.
  * @param  None
  * @retval None
  */
void LTK_LED_Init()
{
    LTK_LED_RCC_Init();
    LTK_LED_GPIO_Init();
}

/**
  * @brief  set/reset LED0/LED1.
  * @param  LED: Indicate the LED number, either 0 or 1.
  * @param  value: the output of LED0/LED1, either 0 or 1.
  * @retval None
  */
void LTK_LED_Set(uint8_t LED, uint8_t value)
{
    if (LED == 0)
    {
        if (value == 0)
            GPIO_ResetBits(GPIOA, GPIO_Pin_1);
        else if (value == 1)
            GPIO_SetBits(GPIOA, GPIO_Pin_1);
    }
    else if (LED == 1)
    {
        if (value == 0)
            GPIO_ResetBits(GPIOA, GPIO_Pin_2);
        else if (value == 1)
            GPIO_SetBits(GPIOA, GPIO_Pin_2);
    }
}

/**
  * @brief  Toggle LED0/LED1.
  * @param  LED: Indicate the LED number, either 0 or 1.
  * @retval None
  */
void LTK_LED_Toggle(uint8_t LED)
{
    if(LED == 0)
        GPIOA->ODR ^= GPIO_Pin_1;
    else if (LED == 1)
        GPIOA->ODR ^= GPIO_Pin_2;
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
