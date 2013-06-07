/**
  ******************************************************************************
  * @file    Button_EXTI_main.c 
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
#include "LTK_Button_EXTI.h"

/** @addtogroup LTK_Examples
  * @{
  */

/** @addtogroup LTK_Button_EXTI
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program, EXTI example.
  * @param  None
  * @retval None
  */
int main(void)
{     
    LTK_LED_Init();
    LTK_Button_Init();  
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
