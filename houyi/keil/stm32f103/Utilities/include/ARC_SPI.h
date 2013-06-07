/**
  ******************************************************************************
  * @file    LTK_SPI.h
  * @author  leitek (leitek.taobao.com)
  * @version V1.0.0
  * @brief   Header files for middleware.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * COPYRIGHT leitek.taobao.com
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LTK_SPI_H
#define __LTK_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_SPI
  * @{
  */

/** @defgroup LTK_SPI_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_SPI_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_SPI_Exported_Macros
  * @{
  */  
/* Select SD card: Chip Select pin low */
#define LTK_SD_CS_LOW()  GPIO_ResetBits(GPIOA, GPIO_Pin_8)
/* Deselect SD card: Chip Select pin high */
#define LTK_SD_CS_HIGH() GPIO_SetBits(GPIOA, GPIO_Pin_8)

/* Select FLASH: Chip Select pin low */
#define LTK_FLASH_CS_LOW()  GPIO_ResetBits(GPIOA, GPIO_Pin_4)
/* Deselect FLASH: Chip Select pin high */
#define LTK_FLASH_CS_HIGH() GPIO_SetBits(GPIOA, GPIO_Pin_4)   

/* Select FLASH: Chip Select pin low */
#define LTK_TS_CS_LOW()  GPIO_ResetBits(GPIOC, GPIO_Pin_7)
/* Deselect FLASH: Chip Select pin high */
#define LTK_TS_CS_HIGH() GPIO_SetBits(GPIOC, GPIO_Pin_7)

#define LTK_SPI_FLASH_SPEED     SPI_BaudRatePrescaler_4
#define LTK_SPI_XPT2046_SPEED   SPI_BaudRatePrescaler_128
#define LTK_SPI_MAX_SPEED       SPI_BaudRatePrescaler_2
#define LTK_SPI_MIN_SPEED       SPI_BaudRatePrescaler_256
#define LTK_SPI_DEFAULT_SPEED   SPI_BaudRatePrescaler_4

/**
  * @}
  */

/** @defgroup LTK_SPI_Exported_Functions
  * @{
  */
  
uint8_t LTK_SPI_SendByte(SPI_TypeDef *SPIx, uint8_t byte);
void LTK_SPI_Init(void);

/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __LTK_SPI_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 

/****************************** leitek.taobao.com *****************************/
