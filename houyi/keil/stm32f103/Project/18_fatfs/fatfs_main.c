/**
  ******************************************************************************
  * @file    Fatfs_main.c 
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
#include "LTK_Fatfs.h"
#include "LTK_SD.h"
#include "LTK_USART.h"
#include "LTK_SysTick.h"
#include "LTK_SPI_Flash.h"
#include "LTK_TouchScreen.h"
#include "LTK_RCC.h"
#include "diskio.h"
#include <stdio.h>

/** @addtogroup LTK_Examples
  * @{
  */

/** @addtogroup LTK_SD
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program, SD card SPI interface read example.
  * @param  None
  * @retval None
  */
int main(void)
{
    LTK_SysTick_Init();
    LTK_COM_Init();
    USART_Cmd(USART1, ENABLE);
    
    LTK_SD_SPI_Init();
    
    SPI_Cmd(SPI1, ENABLE); /*!< SD_SPI enable */
    
    LTK_DMA1_RCC_Init();
    
    while (1)
    {
        LTK_fat_menu_init();
        LTK_SysTick_Delay(1000);
    }  
}

/**
  * @}
  */

/**
  * @}
  */

/****************************** leitek.taobao.com *****************************/
