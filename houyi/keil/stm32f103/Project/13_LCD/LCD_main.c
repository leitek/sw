/**
  ******************************************************************************
  * @file    LCD_main.c 
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

/** @addtogroup LTK_Examples
  * @{
  */

/** @addtogroup LTK_LCD
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program, show strings on LCD screen.
  * @param  None
  * @retval None
  */
int main(void)
{
    uint16_t x = 0;
    LTK_SysTick_Init();
    
    LTK_COM_Init();
    USART_Cmd(USART1, ENABLE);
    
    LTK_LCD_Init();
    LTK_LCD_On();
    while(1) 
    {
        switch(x)
        {
            case 0:
                LTK_LCD_Clear(LCD_COLOR_BLACK);
                break;
            case 1:
                LTK_LCD_Clear(LCD_COLOR_MAGENTA);
                break;
            case 2:
                LTK_LCD_Clear(LCD_COLOR_GREEN);
                break;
            case 3:
                LTK_LCD_Clear(LCD_COLOR_RED);
                break;
            case 4:
                LTK_LCD_Clear(LCD_COLOR_BLUE);
                break;
        }
        
        x++;
        x = (x > 4) ? 0 : x;

        LTK_LCD_ShowString(30, 50, "LTK STM32");

        LTK_LCD_ShowString(30, 70, "TFT LCD Example");
        
        LTK_LCD_ShowString(30, 90, "leitek.taobao.com");
        
        LTK_LCD_ShowString(30, 110, "http://leitek.taobao.com");
        LTK_SysTick_Delay(2000);
    }                                               
}

/**
  * @}
  */

/**
  * @}
  */

/****************************** leitek.taobao.com *****************************/
