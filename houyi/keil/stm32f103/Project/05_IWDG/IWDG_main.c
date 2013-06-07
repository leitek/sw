/**
  ******************************************************************************
  * @file    IWDG_main.c 
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
#include "LTK_RCC.h"
#include "LTK_EXTI.h"
#include "LTK_GPIO.h"
#include "LTK_NVIC_API.h"
#include "LTK_Button_EXTI.h"
#include "LTK_SysTick.h"
#include "LTK_IWDG.h"
/** @addtogroup LTK_Examples
  * @{
  */

/** @addtogroup LTK_IWDG
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program, IWDG example.
  * @param  None
  * @retval None
  */
int main(void)
{
    LTK_LED_Init();
    LTK_Button_Init();
    LTK_SysTick_Init();  
    LTK_IWDG_Init(IWDG_Prescaler_256, (2 * 40000 / 256));
    LTK_LED_Set(0, 1);
    LTK_LED_Set(1, 1);
    LTK_SysTick_Delay(1000);
    LTK_LED_Set(0, 0);
    LTK_LED_Set(1, 0);
    IWDG_Enable();
    while (1)
    {
    }  
}

/**
  * @}
  */

/**
  * @}
  */

/****************************** leitek.taobao.com *****************************/
