/**
  ******************************************************************************
  * @file    RTC_main.c 
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
#include "LTK_RTC.h"
#include "LTK_Systick.h"
#include "LTK_USART.h"
#include "stdio.h"
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
  * @brief  Main program, RTC example.
  * @param  None
  * @retval None
  */
int main(void)
{
    RTC_t rtc;
    LTK_RTC_Init();
    LTK_SysTick_Init();
    LTK_COM_Init();
    USART_Cmd(USART1, ENABLE);
    while (1)
    {
        LTK_RTC_gettime(&rtc);
        LTK_SysTick_Delay(1000);
        printf("%d-%d-%d %d:%d:%d\n", rtc.year, rtc.month, rtc.mday, rtc.hour, rtc.min, rtc.sec);
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
