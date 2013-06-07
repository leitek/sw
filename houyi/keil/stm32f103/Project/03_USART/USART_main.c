/**
  ******************************************************************************
  * @file    USART_main.c 
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
#include "LTK_USART.h"
#include "LTK_SysTick.h"
#include "LTK_Retarget.h"

/** @addtogroup LTK_Examples
  * @{
  */

/** @addtogroup LTK_USART
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program, retargeting the standard C printf and scanf
            to  UART output.
  * @param  None
  * @retval None
  */
int main(void)
{
    char str[80];
    LTK_COM_Init();
    /* Enable USART */
    USART_Cmd(USART1, ENABLE);

    while (1)
    {
        printf("\ninput your string, max: 80\n");
        scanf("%[^\n]",str);
        printf("your input string is\n%s\n", str);
    }  
}

/**
  * @}
  */

/**
  * @}
  */

/****************************** leitek.taobao.com *****************************/
