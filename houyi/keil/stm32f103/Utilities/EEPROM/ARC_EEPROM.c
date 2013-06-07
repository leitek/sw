/**
  ******************************************************************************
  * @file    LTK_EEPROM.c
  * @author  leitek (leitek.taobao.com)
  * @version V1.0.0
  * @brief   LTK middleware. 
  *          This file provides EEPROM middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * COPYRIGHT leitek.taobao.com
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "LTK_EEPROM.h"
#include "LTK_SysTick.h"
#include "LTK_I2C.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_EEPROM
  * @{
  */ 

/** @defgroup LTK_EEPROM_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_EEPROM_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup LTK_EEPROM_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup LTK_EEPROM_Private_Variables
  * @{
  */ 

/**
  * @}
  */

/** @defgroup LTK_EEPROM_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_EEPROM_Private_Functions
  * @{
  */

/**
  * @brief  EEPROM write api.
  * @param  *EEPBuff: the address of the buffer which will be written to EEPROM
  * @param  SubAdd: the address of the EEPROM which stores the content of the buffer
  * @param  EEPSize: the buffer size
  * @retval None
  */ 
void LTK_EEPROM_Write(uint8_t *EEPBuff, uint32_t SubAdd, uint32_t EEPSize)
{
    uint8_t i = 0;
    LTK_I2C_Init();
    for ( i = 0; i < EEPSize; i++)
    {
        I2C_param_struct __IO *pI2C_param;

        pI2C_param = LTK_get_I2C_param();

        pI2C_param->I2C_DIRECTION = LTK_I2C_DIRECTION_TX;
        pI2C_param->DeviceAddr = LTK_EEPROM_ADDR;
        
        pI2C_param->SubAddr = SubAdd + i;
        pI2C_param->TxData = EEPBuff + i;
        pI2C_param->TxNumOfBytes = 1;
        pI2C_param->TX_I2C_Index = 0;
        pI2C_param->TX_Generate_stop = 1;
        
        LTK_I2C_Write(I2C1, pI2C_param);
        LTK_SysTick_Delay(20);
    }
    LTK_I2C_DeInit();
}

/**
  * @brief  EEPROM read api.
  * @param  *RXEEPBuff: the address of the buffer which stores EEPROM read content.
  * @param  SubAdd: the address of the EEPROM read from
  * @param  EEPSize: the buffer size
  * @retval None
  */ 
void LTK_EEPROM_Read(uint8_t *RXEEPBuff, uint32_t SubAdd, uint32_t EEPSize)
{
    I2C_param_struct __IO *pI2C_param;
    LTK_I2C_Init();
    pI2C_param = LTK_get_I2C_param();

    pI2C_param->I2C_DIRECTION = LTK_I2C_DIRECTION_TX;
    pI2C_param->DeviceAddr = LTK_EEPROM_ADDR;
    
    pI2C_param->SubAddr = SubAdd;
    pI2C_param->TxNumOfBytes = 0;
    pI2C_param->TX_I2C_Index = 0;
    pI2C_param->TX_Generate_stop = 0;

    pI2C_param->RxData = RXEEPBuff;
    pI2C_param->RxNumOfBytes = EEPSize;
    pI2C_param->RX_I2C_Index = 0;
    
    LTK_I2C_Write(I2C1, pI2C_param);
    
    LTK_SysTick_Delay(100);
    LTK_I2C_DeInit();
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
