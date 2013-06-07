/**
  ******************************************************************************
  * @file    LTK_RCC.c
  * @author  leitek (leitek.taobao.com)
  * @version V1.0.0
  * @brief   LTK middleware. 
  *          This file provides RCC middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * COPYRIGHT leitek.taobao.com
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "LTK_RCC.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_RCC
  * @{
  */ 

/** @defgroup LTK_RCC_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_RCC_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup LTK_RCC_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup LTK_RCC_Private_Variables
  * @{
  */ 

/**
  * @}
  */

/** @defgroup LTK_RCC_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_RCC_Private_Functions
  * @{
  */

/**
  * @brief  Configures LED clocks.
  * @param  None
  * @retval None
  */
void LTK_LED_RCC_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   
}

/**
  * @brief  Configures Button clocks.
  * @param  None
  * @retval None
  */
void LTK_Button_RCC_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);    
}

/**
  * @brief  Configures SPI Flash clocks.
  * @param  None
  * @retval None
  */
void LTK_SPI_RCC_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);

    /*!< FLASH_SPI Periph clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
}

/**
  * @brief  Configures LCD clocks.
  * @param  None
  * @retval None
  */
void LTK_LCD_RCC_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | 
                           RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);
}

/**
  * @brief  Configures I2C clocks.
  * @param  None
  * @retval None
  */
void LTK_I2C_RCC_Init(void)
{  
    /* Enable I2C and I2C_PORT & Alternate Function clocks */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
}

/**
  * @brief  Configures Touch screen clocks.
  * @param  None
  * @retval None
  */
void LTK_TouchScreen_RCC_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
}

/**
  * @brief  Configures TIM PWM clocks.
  * @param  None
  * @retval None
  */
void LTK_TIM_PWM_RCC_Init(void)
{
    /* TIM3 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    /* GPIOA clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
}

/**
  * @brief  Configures COM clocks.
  * @param  None
  * @retval None
  */
void LTK_COM_RCC_Init(void)
{
    /* Enable GPIO clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
}

/**
  * @brief  Configures ADC clocks.
  * @param  None
  * @retval None
  */
void LTK_ADC_RCC_Init(void)
{
    /* ADCCLK = PCLK2/4 */
    RCC_ADCCLKConfig(RCC_PCLK2_Div4); 

    /* Enable ADC1 and GPIOC clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC, ENABLE);
}

/**
  * @brief  Configures DMA clocks.
  * @param  None
  * @retval None
  */
void LTK_DMA1_RCC_Init(void)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
}

/**
  * @brief  Configures USB clocks.
  * @param  None
  * @retval None
  */
void LTK_USB_RCC_Init(void)
{
    /* Select USBCLK source */
    RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);

    /* Enable the USB clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
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
