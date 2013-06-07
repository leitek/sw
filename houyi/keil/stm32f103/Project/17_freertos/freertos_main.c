/**
  ******************************************************************************
  * @file    freertos_main.c 
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
#include "FreeRTOS.h"
#include "task.h"
#include "stm32f10x.h"
#include "LTK_FreeRTOS.h"
#include "LTK_LED.h"

/** @addtogroup LTK_Examples
  * @{
  */

/** @addtogroup LTK_FREERTOS
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program, freeRTOS immigration to LTK board example.
  * @param  None
  * @retval None
  */
int main(void)
{
    LTK_LED_Init();
    
    /* Create one task. */
    xTaskCreate(    vTask,     /* Pointer to the function that implements the task. */
                    "Task 1",   /* Text name for the task.  This is to facilitate debugging only. */
                    200,        /* Stack depth in words. */
                    NULL,       /* We are not using the task parameter. */
                    1,          /* This task will run at priority 1. */
                    NULL );     /* We are not using the task handle. */

    /* Start the scheduler so our tasks start executing. */
    vTaskStartScheduler();

    /* If all is well we will never reach here as the scheduler will now be
       running.  If we do reach here then it is likely that there was insufficient
       heap available for the idle task to be created. */
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
