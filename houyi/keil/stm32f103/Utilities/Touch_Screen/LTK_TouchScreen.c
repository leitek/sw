/**
  ******************************************************************************
  * @file    LTK_TouchScreen.c
  * @author  leitek (leitek.taobao.com)
  * @version V1.0.0
  * @brief   LTK middleware. 
  *          This file provides Touch screen middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * COPYRIGHT leitek.taobao.com
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "LTK_TouchScreen.h"
#include "LTK_SPI.h"
#include "LTK_SPI_Flash.h"
#include "LTK_GPIO.h"
#include "LTK_RCC.h"
#include "LTK_EXTI.h"
#include "LTK_NVIC_API.h"
#include "LTK_LCD.h"
#include "LTK_SysTick.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#if (defined LTK_UCGUI && defined LTK_FREERTOS)
#include "LCD_Private.h"      /* private modul definitions & config */
#include "GUI_Private.h"
#include "GUIDebug.h"
#endif


/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_TouchScreen
  * @{
  */ 

/** @defgroup LTK_TouchScreen_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_TouchScreen_Private_Defines
  * @{
  */

#define LTK_TS_XPT2046_X        0xD0
#define LTK_TS_XPT2046_Y        0x90
#define LTK_TS_XPT2046_DUMMY    0x0

#define LTK_TS_READ_TIMES       16
#define LTK_TS_IGNORE_TIMES     5 /* ignore twice, up and down each */

#define LTK_DRAW_RANGE          5
#define LTK_MAGIC               0xFEDCBA1
#define LTK_TS_FLASH_ADDR       (256 * 16)

#define LTK_TS_CAL_X_LEFT       20
#define LTK_TS_CAL_X_RIGHT      (LCD_XSIZE - 1 - LTK_TS_CAL_X_LEFT)
#define LTK_TS_CAL_Y_BOTTOM     20
#define LTK_TS_CAL_Y_TOP        (LCD_YSIZE - 1 - LTK_TS_CAL_Y_BOTTOM)

/**
  * @}
  */ 

/** @defgroup LTK_TouchScreen_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup LTK_TouchScreen_Private_Variables
  * @{
  */ 
  
#if (defined LTK_UCGUI && defined LTK_FREERTOS)
xSemaphoreHandle xBinarySemaphore_ts;
#endif

static pen_state_struct pen_state;

/**
  * @}
  */

/** @defgroup LTK_TouchScreen_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_TouchScreen_Private_Functions
  * @{
  */
#if (defined LTK_UCGUI && defined LTK_FREERTOS)

/**
  * @brief  Initialize a binary semaphore for TS.
  * @param  None
  * @retval None
  */
void LTK_TouchScreen_OS_Init(void)
{
    vSemaphoreCreateBinary( xBinarySemaphore_ts );
}

/**
  * @brief  the touch screen task.
  * @param  pvParameters
  * @retval None
  */
void Touchscreen ( void *pvParameters )
{
    while(1)
    {
        StoreUnstable_Invalid();
        xSemaphoreTake(xBinarySemaphore_ts, portMAX_DELAY);
        
        while(!LTK_PEN_STATE())
        {
            GUI_TOUCH_Exec();
            LTK_SysTick_Delay(10); /*recommanded 100 times per second by uCGUI */
        }
    }
}

#endif

/**
  * @brief  initialize the LCD struct.
  * @param  None
  * @retval None
  */
void LTK_TouchScreen_Struct_Init(void)
{
    pen_state_struct *pen_st;
    pen_st = LTK_get_penstate();
    memset((void*) pen_st, 0, sizeof(pen_state_struct));
}
  
/**
  * @brief  Initialize TouchScreen.
  * @param  None
  * @retval None
  */
void LTK_TouchScreen_Init(void)
{
    LTK_SPI_Init();
    LTK_TouchScreen_RCC_Init();
    LTK_TouchScreen_GPIO_Init();
    LTK_TouchScreen_NVIC_Init();
    LTK_TouchScreen_EXTI_Init();
    #if (defined LTK_UCGUI && defined LTK_FREERTOS)
    LTK_TouchScreen_OS_Init();
    #endif
    LTK_TouchScreen_Struct_Init();
}

/**
  * @brief  get pen_state.
  * @param  None
  * @retval the pointer to the pen_state
  */
pen_state_struct *LTK_get_penstate(void)
{
    return &pen_state;
}

/**
  * @brief  start up the TouchScreen, do adjustment here.
  * @param  None
  * @retval None
  */
void LTK_TouchScreen_start(void)
{
    LTK_SPI_FLASH_ID_check();
    LTK_TouchScreen_Adjust();
}

/**
  * @brief  read the original position on the touch screen.
  * @param  None
  * @retval None
  */
void LTK_TouchScreen_Rd_Phisical_XY(void)
{
    uint8_t i, j, xy_index;
    uint16_t value;
    uint16_t buff[2][LTK_TS_READ_TIMES];
    uint16_t sum[2] = {0, 0};
    uint16_t temp;
    pen_state_struct *pen_st;

    EXTI_SetInt(EXTI_Line6, 0);
    LTK_SysTick_Delay(1);

    pen_st = LTK_get_penstate();

    SPI_BaudRateConfig(SPI1, LTK_SPI_XPT2046_SPEED);
    LTK_TS_CS_LOW();
    
    for (i = 0; i < LTK_TS_READ_TIMES; i++)
    {
        LTK_SPI_SendByte(SPI1, LTK_TS_XPT2046_X);

        value = LTK_SPI_SendByte(SPI1, LTK_TS_XPT2046_DUMMY);

        buff[0][i] = value << 8;
        value = LTK_SPI_SendByte(SPI1, LTK_TS_XPT2046_DUMMY);
        buff[0][i] |= value;
        buff[0][i] >>= 3;
        buff[0][i] &= 0XFFF;
        
        LTK_SPI_SendByte(SPI1, LTK_TS_XPT2046_Y);
        value = LTK_SPI_SendByte(SPI1, LTK_TS_XPT2046_DUMMY);
        buff[1][i] = value << 8;
        value = LTK_SPI_SendByte(SPI1, LTK_TS_XPT2046_DUMMY);
        buff[1][i] |= value;
        buff[1][i] >>= 3;
        buff[1][i] &= 0XFFF;
    }
    LTK_TS_CS_HIGH();
    SPI_BaudRateConfig(SPI1, LTK_SPI_DEFAULT_SPEED);
    
    EXTI_SetInt(EXTI_Line6, 1);

    for(xy_index = 0; xy_index < 2; xy_index++)
    {
        for(i = 0;i < LTK_TS_READ_TIMES - 1; i++)
        {
            for(j = i + 1; j < LTK_TS_READ_TIMES; j++)
            {
                if(buff[xy_index][i] > buff[xy_index][j])
                {
                    temp =buff[xy_index][i];
                    buff[xy_index][i] = buff[xy_index][j];
                    buff[xy_index][j] = temp;
                }
            }
        }
        for(i = LTK_TS_IGNORE_TIMES; i < LTK_TS_READ_TIMES - LTK_TS_IGNORE_TIMES; i++)
            sum[xy_index] += buff[xy_index][i];
        sum[xy_index] = sum[xy_index] / (LTK_TS_IGNORE_TIMES - 2 * LTK_TS_IGNORE_TIMES);
    }
    pen_st->x = sum[0];
    pen_st->y = sum[1];
}

/**
  * @brief  read the converted position on the touch screen.
  * @param  None
  * @retval 1 if the converted point is valid, otherwise return 0.
  */
uint8_t LTK_TouchScreen_Rd_LCD_XY(void)
{
    uint8_t ret_value = 1;
    static uint16_t pre_x, pre_y;
    pen_state_struct *pen_st;
    pen_st = LTK_get_penstate();

    LTK_TouchScreen_Rd_Phisical_XY();
    if (pen_st->xy_reversed)
    {
        pen_st->x_converted = pen_st->xfac * pen_st->y + pen_st->xoff;
        pen_st->y_converted = pen_st->yfac * pen_st->x + pen_st->yoff;
    }
    else
    {
        pen_st->x_converted = pen_st->xfac * pen_st->x + pen_st->xoff;
        pen_st->y_converted = pen_st->yfac * pen_st->y + pen_st->yoff;
    }
    
    if((abs(pre_x - pen_st->x_converted) > LTK_DRAW_RANGE) || 
       (abs(pre_y - pen_st->y_converted) > LTK_DRAW_RANGE))
       ret_value = 0;
       
    pre_x = pen_st->x_converted;
    pre_y = pen_st->y_converted;
    
    return ret_value;
}

/**
  * @brief  calculate the distance of the two points.
  * @param  *point1: the first point.
  * @param  *point2: the second point.
  * @retval the distance of the two points..
  */
int32_t LTK_Calc_distance(int32_t *point1, int32_t *point2)
{
    return sqrt((point1[0] - point2[0]) * (point1[0] - point2[0]) + 
                (point1[1] - point2[1]) * (point1[1] - point2[1]));
}

/**
  * @brief  verify if the touch screen is a valid one.
  * @param  pos_temp[][2]: the four points on the touch screen corners.
  * @retval 1 if the touch screen is valid, otherwise return 0.
  */
uint8_t LTK_Verify_TouchScreen(int32_t pos_temp[][2])
{
    int32_t d1, d2;
    int32_t fac_x100;

    d1 = LTK_Calc_distance(pos_temp[0], pos_temp[1]);
    d2 = LTK_Calc_distance(pos_temp[2], pos_temp[3]);
    fac_x100 = d1 * 100 / d2;
    if(abs(fac_x100 - 100) > 5 || d1 == 0 || d2 == 0)
    {
        return 0;
    }
    
    d1 = LTK_Calc_distance(pos_temp[0], pos_temp[2]);
    d2 = LTK_Calc_distance(pos_temp[1], pos_temp[3]);
    fac_x100 = d1 * 100 / d2;
    if(abs(fac_x100 - 100) > 5 || d1 == 0 || d2 == 0)
    {
        return 0;
    }
    
    d1 = LTK_Calc_distance(pos_temp[0], pos_temp[3]);
    d2 = LTK_Calc_distance(pos_temp[1], pos_temp[2]);
    fac_x100 = d1 * 100 / d2;
    if(abs(fac_x100 - 100) > 5 || d1 == 0 || d2 == 0)
    {
        return 0;
    }
    
    return 1;
}

/**
  * @brief  Do touch screen adjustment.
  * @param  None
  * @retval None
  */
void LTK_TouchScreen_Adjust(void)
{
    uint8_t lcd_drawed = 0;
    int32_t pos_temp[4][2];
    uint8_t  cnt = 0;
    pen_state_struct *pen_st;
    uint32_t FlashAddr;
    uint8_t Rx_Buffer[8];
    uint8_t *Tx_Buffer;
    uint16_t BufferSize;
    uint32_t magic_num = LTK_MAGIC;
    const int32_t LCD_pos[4][2] = { {LTK_TS_CAL_X_LEFT,  LTK_TS_CAL_Y_BOTTOM},
                                    {LTK_TS_CAL_X_RIGHT, LTK_TS_CAL_Y_BOTTOM},
                                    {LTK_TS_CAL_X_RIGHT, LTK_TS_CAL_Y_TOP},
                                    {LTK_TS_CAL_X_LEFT, LTK_TS_CAL_Y_TOP}};

    pen_st = LTK_get_penstate();
    
    if(!(pen_st->force_adjust))
    {
        if(spi_flash_found)
        {
            FlashAddr = LTK_TS_FLASH_ADDR;
            BufferSize = sizeof(uint32_t);
            /* Read data from SPI FLASH memory */
            LTK_FLASH_ReadBuffer(Rx_Buffer, FlashAddr, BufferSize);
            if((*(uint32_t *)Rx_Buffer) == magic_num)
            {
                FlashAddr += BufferSize;
                BufferSize = sizeof(float);
                /* Read data from SPI FLASH memory */
                LTK_FLASH_ReadBuffer(Rx_Buffer, FlashAddr, BufferSize);
                pen_st->xfac = *(float *)Rx_Buffer;

                FlashAddr += BufferSize;
                BufferSize = sizeof(float);
                /* Read data from SPI FLASH memory */
                LTK_FLASH_ReadBuffer(Rx_Buffer, FlashAddr, BufferSize);
                pen_st->xoff = *(float *)Rx_Buffer;

                FlashAddr += BufferSize;
                BufferSize = sizeof(float);
                /* Read data from SPI FLASH memory */
                LTK_FLASH_ReadBuffer(Rx_Buffer, FlashAddr, BufferSize);
                pen_st->yfac = *(float *)Rx_Buffer;

                FlashAddr += BufferSize;
                BufferSize = sizeof(float);
                /* Read data from SPI FLASH memory */
                LTK_FLASH_ReadBuffer(Rx_Buffer, FlashAddr, BufferSize);
                pen_st->yoff = *(float *)Rx_Buffer;

                FlashAddr += BufferSize;
                BufferSize = sizeof(uint8_t);
                /* Read data from SPI FLASH memory */
                LTK_FLASH_ReadBuffer(Rx_Buffer, FlashAddr, BufferSize);
                pen_st->xy_reversed= *(uint8_t *)Rx_Buffer;

                return;
            }
        }
    }
    
    pen_st->pen_pressed = KEY_UP;
    
    while(1)
    {
        if(!lcd_drawed)
        {
            lcd_drawed = 1;
            #if (defined LTK_UCGUI && defined LTK_FREERTOS)
            GUI_SetBkColor(GUI_RED);  
            GUI_Clear();
            GUI_SetColor(GUI_WHITE);  
            GUI_DrawCircle(LCD_pos[cnt][0], LCD_pos[cnt][1], 5);
            GUI_SetColor(GUI_WHITE);
            GUI_DrawHLine(LCD_pos[cnt][1], LCD_pos[cnt][0] - 10, LCD_pos[cnt][0] + 10);
            GUI_DrawVLine(LCD_pos[cnt][0], LCD_pos[cnt][1] - 10, LCD_pos[cnt][1] + 10);
            GUI_SetColor(GUI_WHITE);
            GUI_SetTextAlign(GUI_TA_CENTER);
            GUI_DispStringAt("touchscreen calculation", LCD_XSIZE / 2, LCD_YSIZE / 2 - 20);
            GUI_SetTextAlign(GUI_TA_CENTER);
            GUI_DispStringAt("press the middle of the cross", LCD_XSIZE / 2, LCD_YSIZE / 2 + 20);
            #else
            LTK_LCD_Clear(LCD_COLOR_RED);
            LTK_LCD_DrawCross(LCD_pos[cnt][0], LCD_pos[cnt][1], LCD_COLOR_WHITE);
            #endif
        }
        if(pen_st->pen_pressed == KEY_DOWN)
        {
            lcd_drawed = 0;
            pen_st->pen_pressed = KEY_UP;
            LTK_TouchScreen_Rd_Phisical_XY();
            pos_temp[cnt][0] = pen_st->x;
            pos_temp[cnt][1] = pen_st->y;

            cnt++;
            
            if(cnt == 4)
            {
                if(LTK_Verify_TouchScreen(pos_temp) == 0)
                {
                    cnt = 0;
                }
                else
                {
                    if((pen_st->ts_direction == force_reverse) ||
                       (pen_st->ts_direction == auto_detect && 
                        abs(pos_temp[1][0] - pos_temp[0][0]) < abs(pos_temp[1][1] - pos_temp[0][1])))
                    {
                        uint8_t i;
                        int32_t temp;
                        for(i = 0; i < 4; i++)
                        {
                            temp = pos_temp[i][0];
                            pos_temp[i][0] = pos_temp[i][1];
                            pos_temp[i][1] = temp;
                        }
                        pen_st->xy_reversed = 1;
                    }
                    else
                    {
                        pen_st->xy_reversed = 0;
                    }
                    
                    pen_st->xfac = (float)(LCD_pos[1][0] - LCD_pos[0][0]) / (pos_temp[1][0] - pos_temp[0][0]);
                    pen_st->xoff = ((LCD_pos[1][0] + LCD_pos[0][0]) - pen_st->xfac * (pos_temp[1][0] + pos_temp[0][0])) / 2;
                      
                    pen_st->yfac = (float)(LCD_pos[2][1] - LCD_pos[0][1]) / (pos_temp[2][1] - pos_temp[0][1]);
                    pen_st->yoff = ((LCD_pos[2][1] + LCD_pos[0][1]) - pen_st->yfac * (pos_temp[2][1] + pos_temp[0][1])) / 2;
                    if (spi_flash_found)
                    {
                        FlashAddr = LTK_TS_FLASH_ADDR;
                        /* Erase SPI FLASH Sector to write on */
                        LTK_FLASH_EraseSector(FlashAddr);

                        BufferSize = sizeof(uint32_t);
                        Tx_Buffer = (uint8_t *)(&magic_num);
                        /* Write Tx_Buffer data to SPI FLASH memory */
                        LTK_FLASH_WriteBuffer(Tx_Buffer, FlashAddr, BufferSize);

                        FlashAddr += BufferSize;
                        BufferSize = sizeof(float);
                        Tx_Buffer = (uint8_t *)(&(pen_st->xfac));
                        /* Write Tx_Buffer data to SPI FLASH memory */
                        LTK_FLASH_WriteBuffer(Tx_Buffer, FlashAddr, BufferSize);

                        FlashAddr += BufferSize;
                        BufferSize = sizeof(float);
                        Tx_Buffer = (uint8_t *)(&(pen_st->xoff));
                        /* Write Tx_Buffer data to SPI FLASH memory */
                        LTK_FLASH_WriteBuffer(Tx_Buffer, FlashAddr, BufferSize);

                        FlashAddr += BufferSize;
                        BufferSize = sizeof(float);
                        Tx_Buffer = (uint8_t *)(&(pen_st->yfac));
                        /* Write Tx_Buffer data to SPI FLASH memory */
                        LTK_FLASH_WriteBuffer(Tx_Buffer, FlashAddr, BufferSize);

                        FlashAddr += BufferSize;
                        BufferSize = sizeof(float);
                        Tx_Buffer = (uint8_t *)(&(pen_st->yoff));
                        /* Write Tx_Buffer data to SPI FLASH memory */
                        LTK_FLASH_WriteBuffer(Tx_Buffer, FlashAddr, BufferSize);

                        FlashAddr += BufferSize;
                        BufferSize = sizeof(uint8_t);
                        Tx_Buffer = (uint8_t *)(&(pen_st->xy_reversed));
                        /* Write Tx_Buffer data to SPI FLASH memory */
                        LTK_FLASH_WriteBuffer(Tx_Buffer, FlashAddr, BufferSize);
                    }
                    return;
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
  
/**
  * @}
  */  
    
/****************************** leitek.taobao.com *****************************/
