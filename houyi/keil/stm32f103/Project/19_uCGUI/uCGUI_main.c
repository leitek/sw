/**
  ******************************************************************************
  * @file    uCGUI_main.c 
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
#include "LTK_SysTick.h"
#include "LTK_LCD.h"
#include "LTK_USART.h"
#include "LTK_TouchScreen.h"
#include "LTK_SPI_Flash.h"
#include "LTK_Button_EXTI.h"
#include "FreeRTOS.h"
#include "task.h"
#include "GUIDEMO.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/** @addtogroup LTK_Examples
  * @{
  */

/** @addtogroup LTK_TS
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initialize take.
  */
void InitTask ( void *pvParameters )
{
    portBASE_TYPE task_error;
    LTK_Button_Init();
    LTK_COM_Init();
    USART_Cmd(USART1, ENABLE);
    
    task_error = xTaskCreate(uCGUI, "uCGUI task", (1 * 1024), NULL, 8, NULL );
    assert( task_error == pdPASS);
    
    vTaskDelete(NULL);
}

/**
  * @brief  Main program, the touch screen example.
  * @param  None
  * @retval None
  */
int main(void)
{
    
    portBASE_TYPE task_error;
    task_error = xTaskCreate(InitTask, "Init task", (200), NULL, 0, NULL );
    
    assert( task_error == pdPASS);
    vTaskStartScheduler();
    assert(0);
}

/**
  * @}
  */

/**
  * @}
  */

/****************************** leitek.taobao.com *****************************/
