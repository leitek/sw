/**
  ******************************************************************************
  * @file    SysTick_main.c 
  * @author  leitek (leitek.taobao.com)
  * @version V1.0.0
  * @date    10/21/2011
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
#include "LTK_SysTick.h"
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
  * @brief  Main program, flash LED0 and LED1 every 1 second using
            SysTick to delay.
  * @param  None
  * @retval None
  */
int main(void)
{
    LTK_LED_Init();
    LTK_SysTick_Init();
    while (1)
    {
        LTK_LED_Set(0, 1);
        LTK_LED_Set(1, 0);
        LTK_SysTick_Delay(1000);
        LTK_LED_Set(0, 0);
        LTK_LED_Set(1, 1);
        LTK_SysTick_Delay(1000);
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
