/**
  ******************************************************************************
  * @file    LTK_IWDG.c
  * @author  leitek (leitek.taobao.com)
  * @version V1.0.0
  * @brief   LTK middleware. 
  *          This file provides IWDG middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * COPYRIGHT leitek.taobao.com
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "LTK_IWDG.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_IWDG
  * @{
  */ 

/** @defgroup LTK_IWDG_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_IWDG_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup LTK_IWDG_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup LTK_IWDG_Private_Variables
  * @{
  */ 

/**
  * @}
  */

/** @defgroup LTK_IWDG_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_IWDG_Private_Functions
  * @{
  */

/**
  * @brief  Initialize IWDG.
  * @param  None
  * @retval None
  */
void LTK_IWDG_Init(uint8_t IWDG_Prescaler, uint16_t Reload)
{
    /* IWDG timeout equal to (Reload / (40KHz(LSI) / IWDG_Prescaler)) ms 
     (the timeout may varies due to LSI frequency dispersion) */
    /* Enable write access to IWDG_PR and IWDG_RLR registers */
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

    /* IWDG counter clock: 40KHz(LSI) / IWDG_Prescaler */
    IWDG_SetPrescaler(IWDG_Prescaler);

    /* Set counter reload value to Reload */
    IWDG_SetReload(Reload);

    /* Reload IWDG counter */
    IWDG_ReloadCounter();
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
