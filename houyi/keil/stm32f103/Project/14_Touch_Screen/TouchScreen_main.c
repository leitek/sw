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
#include "LTK_LCD.h"
#include "LTK_USART.h"
#include "LTK_TouchScreen.h"
#include "LTK_SPI_Flash.h"
#include "LTK_Button_EXTI.h"
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
    pen_state_struct *pen_st;
    pen_st = LTK_get_penstate();
    LTK_SysTick_Init();
    LTK_COM_Init();
    USART_Cmd(USART1, ENABLE);
    LTK_LCD_Init();
    LTK_LCD_On();
    LTK_TouchScreen_Init();
    SPI_Cmd(SPI1, ENABLE);
    LTK_TouchScreen_start();
    
    LTK_Button_Init();

    LTK_LCD_Clear(LCD_COLOR_RED);
    LTK_LCD_ShowString(3, 3, "clear");
    
    while(1) 
    {
        if (pen_st->force_adjust == 1)
        {
            LTK_TouchScreen_Adjust();
            pen_st->force_adjust = 0;
            LTK_LCD_Clear(LCD_COLOR_RED);
            LTK_LCD_ShowString(3, 3, "clear");
        }
        if (pen_st->pen_pressed == KEY_DOWN)
        {
            pen_st->pen_pressed = KEY_UP;
            while(!LTK_PEN_STATE())
            {
                if(LTK_TouchScreen_Rd_LCD_XY())
                {
                    if((abs(pen_st->x_converted - 20) < 18) && 
                       (abs(pen_st->y_converted - 8) < 6))
                    {
                        LTK_LCD_Clear(LCD_COLOR_RED);
                        LTK_LCD_ShowString(3, 3, "clear");
                    }
                    else if((abs(pen_st->x_converted - LCD_XSIZE / 2) < LCD_XSIZE / 2) && 
                            (abs(pen_st->y_converted - LCD_YSIZE / 2) < LCD_YSIZE / 2))
                    {
                        LTK_LCD_DrawBigPoint(pen_st->x_converted, pen_st->y_converted, LCD_COLOR_WHITE);
                    }
                }
            }
        }
    }                                               
}

/**
  * @}
  */

/**
  * @}
  */

/****************************** leitek.taobao.com *****************************/
