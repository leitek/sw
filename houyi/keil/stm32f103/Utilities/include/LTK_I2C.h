/**
  ******************************************************************************
  * @file    LTK_I2C.h
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
#ifndef __LTK_I2C_H
#define __LTK_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_I2C
  * @{
  */

/** @defgroup LTK_I2C_Exported_Types
  * @{
  */

typedef enum
{
    TX_STATUS_START,
    TX_STATUS_PROGRESS,
    TX_STATUS_COMPLETED
}I2C_TX_Struct;

typedef enum
{
    RX_STATUS_START,
    RX_STATUS_PROGRESS,
    RX_STATUS_COMPLETED
}I2C_RX_Struct;

typedef struct 
{
    uint8_t  I2C_DIRECTION;
    uint8_t  DeviceAddr;
    
    uint8_t  SubAddr;
    uint8_t  *TxData;
    /* for write, excluding the device addr and subaddr, for read, exclude device addr */
    uint32_t TxNumOfBytes;
    uint32_t TX_I2C_Index;
    uint8_t TX_Generate_stop;

    uint8_t  *RxData;
    uint32_t RxNumOfBytes;
    uint32_t RX_I2C_Index;
}I2C_param_struct;

/**
  * @}
  */

/** @defgroup LTK_I2C_Exported_Constants
  * @{
  */
  
#define LTK_I2C_DIRECTION_TX                 0
#define LTK_I2C_DIRECTION_RX                 1
#define LTK_EEPROM_ADDR                      0xA0
#define LTK_I2C_FLAG_MASK                    0xFFFFFF
#define LTK_I2C_SR2_SHIFT                    16


/**
  * @}
  */

/** @defgroup LTK_I2C_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_I2C_Exported_Functions
  * @{
  */
void LTK_I2C_Init(void);
void LTK_I2C_DeInit(void);
void LTK_I2C_Write(I2C_TypeDef *I2Cx, I2C_param_struct __IO *I2C_param);
void LTK_I2C_Read(I2C_TypeDef* I2Cx, I2C_param_struct __IO *I2C_param);
void LTK_set_I2C_param(I2C_param_struct *I2C_param);
I2C_param_struct __IO *LTK_get_I2C_param(void);

/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __LTK_I2C_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 

/****************************** leitek.taobao.com *****************************/
