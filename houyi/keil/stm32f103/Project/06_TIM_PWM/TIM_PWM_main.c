/**
  ******************************************************************************
  * @file    TIM_PWM_main.c 
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
#include "LTK_TIM_PWM.h"

/** @addtogroup LTK_Examples
  * @{
  */

/** @addtogroup LTK_TIM_PWM
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program, configure TIM2 as PWM output, to drive LED0.
  * @param  None
  * @retval None
  */
int main(void)
{
    LTK_TIM_PWM_Init();
    /* TIM2 enable counter */
    TIM_Cmd(TIM2, ENABLE);
    
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
