/**
  ******************************************************************************
  * @file    LTK_SPI.c
  * @author  leitek (leitek.taobao.com)
  * @version V1.0.0
  * @brief   LTK middleware. 
  *          This file provides SPI middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * COPYRIGHT leitek.taobao.com
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "LTK_SPI.h"
#include "LTK_GPIO.h"
#include "LTK_RCC.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_SPI
  * @{
  */ 

/** @defgroup LTK_SPI_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_SPI_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup LTK_SPI_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup LTK_SPI_Private_Variables
  * @{
  */ 

/**
  * @}
  */

/** @defgroup LTK_SPI_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_SPI_Private_Functions
  * @{
  */
  
/**
  * @brief  Initialize SPI parameters
  * @param  *SPIx: the SPI device ID.
  * @retval None
  */
void LTK_SPI_PARAM_Init(SPI_TypeDef *SPIx)
{
    SPI_InitTypeDef  SPI_InitStructure;
    SPI_I2S_DeInit(SPI1);

    /*!< SPI configuration */
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = LTK_SPI_DEFAULT_SPEED;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPIx, &SPI_InitStructure);
    
    SPI_CalculateCRC(SPI1, DISABLE);
}

/**
  * @brief  Initialize SPI.
  * @param  None
  * @retval None.
  */
void LTK_SPI_Init(void)
{
    LTK_SPI_RCC_Init();
    LTK_SPI_GPIO_Init();
    LTK_SPI_PARAM_Init(SPI1);
    LTK_FLASH_CS_HIGH();
    LTK_SD_CS_HIGH();
    LTK_TS_CS_HIGH();
}


/**
  * @brief  Sends a byte through the SPI interface and return the byte received
  *         from the SPI bus.
  * @param  *SPIx: the SPI device ID.
  * @param  byte: byte to send.
  * @retval The value of the received byte.
  */
uint8_t LTK_SPI_SendByte(SPI_TypeDef *SPIx, uint8_t byte)
{
    /*!< Loop while DR register in not empty */
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);

    /*!< Send byte through the SPI1 peripheral */
    SPI_I2S_SendData(SPIx, byte);

    /*!< Wait to receive a byte */
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);

    /*!< Return the byte read from the SPI bus */
    return SPI_I2S_ReceiveData(SPIx);
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
