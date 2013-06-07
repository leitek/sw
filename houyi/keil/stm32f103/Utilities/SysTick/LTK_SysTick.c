/**
  ******************************************************************************
  * @file    LTK_SysTick.c
  * @author  leitek (leitek.taobao.com)
  * @version V1.0.0
  * @brief   LTK middleware. 
  *          This file provides SysTick middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * COPYRIGHT leitek.taobao.com
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "LTK_SysTick.h"
#ifdef LTK_FREERTOS
#include "FreeRTOS.h"
#include "task.h"
#endif

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_SYSTICK
  * @{
  */ 
      
/** @defgroup SYSTICK_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup SYSTICK_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup SYSTICK_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup SYSTICK_Private_Variables
  * @{
  */ 

static uint32_t __IO TimingDelay;
  
/**
  * @}
  */

/** @defgroup SYSTICK_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup SYSTICK_Private_Functions
  * @{
  */

#ifndef LTK_FREERTOS
/**
  * @brief  Setup SysTick Timer as 1 msec interrupts
  * @param  None
  * @retval None
  */
void LTK_SysTick_Init()
{
    if (SysTick_Config(SystemCoreClock / 1000))
    { 
        /* Capture error */ 
        while (1);
    }
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void LTK_SysTick_Delay(__IO uint32_t nTime)
{ 
    LTK_Set_TimingDelay( nTime );

    while(LTK_Get_TimingDelay() != 0);
}

/**
  * @brief  This function sets the static timingDelay variable.
  * @param  timing_Delay
  * @retval None
  */
void LTK_Set_TimingDelay(uint32_t __IO timing_Delay)
{
    TimingDelay = timing_Delay;
}

/**
  * @brief  This function gets the static timingDelay variable.
  * @param  None
  * @retval Current TimingDelay
  */
uint32_t LTK_Get_TimingDelay()
{
    return TimingDelay;
}

/**
  * @brief  This function gets the static timingDelay variable.
  * @param  None
  * @retval Current TimingDelay
  */
void LTK_Decrease_TimingDelay()
{
    TimingDelay--;
}

#endif
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
