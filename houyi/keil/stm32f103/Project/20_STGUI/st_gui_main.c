/**
  ******************************************************************************
  * @file    TouchScreen_main.c 
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
#include "LTK_LCD_ST.h"
#include "LTK_USART.h"
#include "LTK_TouchScreen.h"
#include "LTK_SPI_Flash.h"
#include "LTK_Button_EXTI.h"
#include "graphicObject.h"
#include "JoyHal.h"
#include "cursor.h"
#include "uiframework.h"
#include <stdio.h>
#include <stdlib.h>

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
  * @brief  Main program, the touch screen example.
  * @param  None
  * @retval None
  */
int main(void)
{
    LTK_SysTick_Init();
    LTK_COM_Init();
    USART_Cmd(USART1, ENABLE);
    LTK_LCD_Init();
    CursorInit(GL_NULL);
    Show_HomeScreen();
    CursorShow(200, 20);

    while(1) 
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
