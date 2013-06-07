/**
  ******************************************************************************
  * @file    LTK_TouchScreen.h
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
#ifndef __LTK_TouchScreen_H
#define __LTK_TouchScreen_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#if (defined LTK_UCGUI && defined LTK_FREERTOS)
#include "FreeRTOS.h"
#include "semphr.h"
#endif
/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_TouchScreen
  * @{
  */

/** @defgroup LTK_TouchScreen_Exported_Types
  * @{
  */
typedef enum
{
    KEY_UP = 0,
    KEY_DOWN = 1
}pen_pressed_status;

typedef enum
{
    auto_detect = 0,
    force_reverse
}ts_direction_struct;

typedef struct 
{
    uint16_t x;
    uint16_t y;
    uint16_t x_converted;
    uint16_t y_converted;
    float xfac;
    float yfac;
    float xoff;
    float yoff;
    uint8_t xy_reversed;
    ts_direction_struct ts_direction;
    pen_pressed_status __IO pen_pressed;
    uint8_t  __IO force_adjust;
}pen_state_struct;


/**
  * @}
  */
/** @defgroup LTK_TouchScreen_Exported_Variables
  * @{
  */
#if (defined LTK_UCGUI && defined LTK_FREERTOS)
extern xSemaphoreHandle xBinarySemaphore_ts;
#endif
/**
  * @}
  */

/** @defgroup LTK_TouchScreen_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_TouchScreen_Exported_Macros
  * @{
  */
  
#define LTK_PEN_STATE()  GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6)

/**
  * @}
  */

/** @defgroup LTK_TouchScreen_Exported_Functions
  * @{
  */
  
void LTK_TouchScreen_Init(void);
void LTK_TouchScreen_Rd_Phisical_XY(void);
uint8_t LTK_TouchScreen_Rd_LCD_XY(void);
pen_state_struct *LTK_get_penstate(void);
void LTK_TouchScreen_Adjust(void);
void LTK_TouchScreen_start(void);
#if (defined LTK_UCGUI && defined LTK_FREERTOS)
void Touchscreen ( void *pvParameters );
#endif
 
/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __LTK_TouchScreen_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 
/****************************** leitek.taobao.com *****************************/
