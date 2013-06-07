/**
  ******************************************************************************
  * @file    LTK_USART.c
  * @author  leitek (leitek.taobao.com)
  * @version V1.0.0
  * @brief   LTK middleware. 
  *          This file provides USART middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * COPYRIGHT leitek.taobao.com
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "LTK_USART.h"
#include "LTK_RCC.h"
#include "LTK_GPIO.h"
#include <stdio.h>

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_USART
  * @{
  */ 

/** @defgroup LTK_USART_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_USART_Private_Defines
  * @{
  */
 
/**
  * @}
  */ 

/** @defgroup LTK_USART_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup LTK_USART_Private_Variables
  * @{
  */ 
  
/**
  * @}
  */

/** @defgroup LTK_USART_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_USART_Private_Functions
  * @{
  */
 
/**
  * @brief  Configures COM port parameters.
  * @param  None 
  * @retval None
  */
void LTK_COM_PARAM_Init()
{
    /* USART1 configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
    */
    USART_InitTypeDef USART_InitStructure;

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    /* USART configuration */
    USART_Init(USART1, &USART_InitStructure);
}

/**
  * @brief  Initialize COM port.
  * @param  None 
  * @retval None
  */
void LTK_COM_Init()
{
    LTK_COM_RCC_Init();
    LTK_COM_GPIO_Init();
    LTK_COM_PARAM_Init();
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
