/**
  ******************************************************************************
  * @file    LTK_NVIC_API.c
  * @author  leitek (leitek.taobao.com)
  * @version V1.0.0
  * @brief   LTK middleware. 
  *          This file provides NVIC API middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * COPYRIGHT leitek.taobao.com
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "LTK_NVIC_API.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_NVIC_API
  * @{
  */ 

/** @defgroup LTK_NVIC_API_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_NVIC_API_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup LTK_NVIC_API_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup LTK_NVIC_API_Private_Variables
  * @{
  */ 

/**
  * @}
  */

/** @defgroup LTK_NVIC_API_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_NVIC_API_Private_Functions
  * @{
  */

/**
  * @brief  Initialize NVIC of push button.
  * @param  None
  * @retval None
  */

void LTK_Button_NVIC_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* 2 bit for pre-emption priority, 2 bits for subpriority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); 

    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_Init(&NVIC_InitStructure); 
}

/**
  * @brief  Initialize NVIC of I2C.
  * @param  None
  * @retval None
  */
void LTK_I2C_NVIC_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    
    /* 2 bit for pre-emption priority, 2 bits for subpriority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitStructure.NVIC_IRQChannel = I2C1_EV_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); 

    NVIC_InitStructure.NVIC_IRQChannel = I2C1_ER_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); 
}

/**
  * @brief  Initialize NVIC of pen of touch screen.
  * @param  None
  * @retval None
  */
void LTK_TouchScreen_NVIC_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    
    /* 2 bit for pre-emption priority, 2 bits for subpriority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); 
}

/**
  * @brief  Initialize NVIC of USB mouse.
  * @param  None
  * @retval None
  */
void LTK_USB_NVIC_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* 2 bit for pre-emption priority, 2 bits for subpriority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable the USB Wake-up interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USBWakeUp_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_Init(&NVIC_InitStructure);   
}

/**
  * @brief  Initialize ADC NVIC.
  * @param  None
  * @retval None
  */
void LTK_ADC_NVIC_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    
    /* 2 bit for pre-emption priority, 2 bits for subpriority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /* Configure and enable ADC interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
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
