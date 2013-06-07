/**
  ******************************************************************************
  * @file    DAM_main.c 
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
#include "LTK_USART.h"
#include "LTK_DMA.h"
#include "LTK_SysTick.h"
#include "stdio.h"

/** @addtogroup LTK_Examples
  * @{
  */

/** @addtogroup LTK_DAM
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program, Memory to USART DMA example.
  * @param  None
  * @retval None
  */
int main(void)
{
    uint8_t CharDMA[] = "Memory to USART DMA example\n";
    uint32_t CharCount = sizeof(CharDMA) - 1;

    LTK_COM_Init();
    USART_Cmd(USART1, ENABLE);
    LTK_DMA1_RCC_Init();
    LTK_DMA1_Ch4_Param_Init(CharDMA, CharCount);

    USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);

    DMA_Cmd(DMA1_Channel4, ENABLE);

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
