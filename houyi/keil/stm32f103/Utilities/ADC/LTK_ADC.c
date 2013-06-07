/**
  ******************************************************************************
  * @file    LTK_ADC.c
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
#include "LTK_ADC.h"
#include "LTK_GPIO.h"
#include "LTK_RCC.h"
#include "LTK_NVIC_API.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_ADC
  * @{
  */ 

/** @defgroup LTK_ADC_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_ADC_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup LTK_ADC_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup LTK_ADC_Private_Variables
  * @{
  */ 

/**
  * @}
  */

/** @defgroup LTK_ADC_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_ADC_Private_Functions
  * @{
  */

/**
  * @brief  Configures the ADC parameters.
  * @param  None
  * @retval None
  */
void LTK_ADC_PARAM_Init()
{
    ADC_InitTypeDef ADC_InitStructure;

    /* ADC1 configuration ------------------------------------------------------*/
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);
}

/**
  * @brief  Initialize ADC.
  * @param  None
  * @retval None
  */
void LTK_ADC_Init()
{
    LTK_ADC_RCC_Init();
    LTK_ADC_GPIO_Init();
    LTK_ADC_PARAM_Init();
    LTK_ADC_NVIC_Init();
    /* ADC1 regular channels configuration */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 1, ADC_SampleTime_55Cycles5);
    /* Enable ADC1 EOC interrupt */
    ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
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
    
/******************* leitek.taobao.com **************************/
