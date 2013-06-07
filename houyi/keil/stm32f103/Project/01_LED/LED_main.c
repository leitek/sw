/**
  ******************************************************************************
  * @file    LED_main.c 
  * @author  leitek (leitek.taobao.com)
  * @version V1.0.0
  * @brief   main program body.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * COPYRIGHT leitek.taobao.com
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "LTK_LED.h"
/** @addtogroup LTK_Examples
  * @{
  */

/** @addtogroup LTK_GPIO
  * @{
  */

/** @addtogroup LTK_GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program, flash LED0 and LED1.
  * @param  None
  * @retval None
  */
int main(void)
{
    uint32_t i;
    LTK_LED_Init();
    while (1)
    {
        LTK_LED_Set(0, 1);
        LTK_LED_Set(1, 0);
        for( i = 0; i < 5000000; i++);        
        LTK_LED_Set(0, 0);
        LTK_LED_Set(1, 1);
        for( i = 0; i < 5000000; i++);        
    }
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
