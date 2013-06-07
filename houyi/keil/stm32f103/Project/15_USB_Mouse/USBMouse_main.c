/**
  ******************************************************************************
  * @file    USBMouse_main.c 
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
#include "LTK_USBMouse.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"
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
__IO uint8_t PrevXferComplete = 1;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program, usb control mouse example
  * @param  None
  * @retval None
  */
int main(void)
{
    uint8_t Mouse_Buffer[4];
    static uint16_t pre_x, pre_y;
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

    LTK_USBMouse_Init();

    LTK_LCD_Clear(LCD_COLOR_RED);
    LTK_LCD_ShowString(3, 3, "clear");
    
    LTK_Button_Init();

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
            do
            {
                pre_x = pen_st->x_converted;
                pre_y = pen_st->y_converted;
                if(LTK_TouchScreen_Rd_LCD_XY())
                {
                    if((abs(pen_st->x_converted - 20) < 18) && 
                       (abs(pen_st->y_converted - 8) < 6))
                    {
                        LTK_LCD_Clear(LCD_COLOR_RED);
                        LTK_LCD_ShowString(3, 3, "clear");
                    }
                    else
                        LTK_LCD_DrawBigPoint(pen_st->x_converted, pen_st->y_converted, LCD_COLOR_WHITE);

                    if((bDeviceState == CONFIGURED) || PrevXferComplete)
                    {
                        Mouse_Buffer[0] = 0;
                        Mouse_Buffer[1] = (pen_st->x_converted - pre_x) * 30;
                        Mouse_Buffer[2] = (pen_st->y_converted - pre_y) * 30;
                        Mouse_Buffer[3] = 0;
                        Joystick_Send(Mouse_Buffer, 4);
                    }
                }
            }while(!LTK_PEN_STATE());
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
