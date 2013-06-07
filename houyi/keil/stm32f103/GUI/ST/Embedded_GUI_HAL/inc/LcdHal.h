/**
  ******************************************************************************
  * @file    LcdHal.h
  * @author  MCD Application Team
  * @version V2.0.0
  * @date    11-July-2011
  * @brief   This file contains all the LCD functions whose
  *          implementation depends on the LCD Type used in your Application.
  *          You only need to change these functions implementations
  *          in order to reuse this code with other LCD
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * COPYRIGHT 2011 STMicroelectronicsCOPYRIGHT
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion ---------------------------------------*/
#ifndef __LCD_HAL_H
#define __LCD_HAL_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32HAL.h"
#include "LTK_LCD_ST.h"
#include "LTK_SysTick.h"
#include "graphicObjectTypes.h"

/** @addtogroup Embedded_GUI_Library
  * @{
  */

/** @addtogroup LcdHal 
  * @{
  */ 

/** @defgroup LcdHal_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup LcdHal_Imported_Variables
  * @{
  */
/**
  * @}
  */

/** @defgroup LcdHal_Exported_Constants
  * @{
  */

#define GL_Clear                        LTK_LCD_Clear
#define GL_LCD_DrawCharTransparent      LTK_LCD_DrawCharTransparent
#define GL_DisplayAdjStringLine         LTK_LCD_DisplayAdjStringLine
#define GL_LCD_DisplayChar              LTK_LCD_DisplayChar
#define GL_SetDisplayWindow             LTK_LCD_SetDisplayWindow
#define GL_DrawLine                     LTK_LCD_DrawLine
#define GL_LCD_DrawRect                 LTK_LCD_DrawRect
#define GL_LCD_DrawCircle               LTK_LCD_DrawCircle
#define GL_DrawBMP                      LTK_LCD_DrawBMP
#define GL_SetFont                      LTK_LCD_SetFont
#define GL_BackLightSwitch              LTK_LCD_BackLightSwitch
#define GL_LCD_Init                     LTK_LCD_Init
#define GL_LCD_WindowModeDisable        LTK_LCD_WindowModeDisable
#define LCD_PutPixel                    LTK_LCD_PutPixel
#define LCD_GetPixel                    LTK_LCD_GetPixel
#define GL_LCD_DrawChar                 LTK_LCD_DrawChar
#define GL_LCD_ReadRAM                  LTK_LCD_ReadRAM
#define LCD_Change_Direction            LTK_LCD_Change_Direction
#define LCD_WriteChar                   LTK_LCD_WriteChar
#define LCD_PrintChar                   LTK_LCD_PrintChar
#define LCD_PrintStringLine             LTK_LCD_PrintStringLine
#define LCD_DrawMonoBMP                 LTK_LCD_DrawMonoBMP
#define LCD_FillArea                    LTK_LCD_FillArea
#define LCD_DrawColorBMP                LTK_LCD_DrawColorBMP
#define GL_SetBackColor                 LTK_LCD_SetBackColor
#define GL_LCD_GetTextColor             LTK_LCD_GetTextColor
#define GL_SetTextColor                 LTK_LCD_SetTextColor

#define GL_OFF                          LCD_BACKLIGHT_OFF
#define GL_ON                           LCD_BACKLIGHT_ON

/* LCD color */
#define GL_White                        LCD_COLOR_WHITE
#define GL_Black                        LCD_COLOR_BLACK
#define GL_Grey                         LCD_COLOR_GREY
#define GL_Blue                         LCD_COLOR_BLUE
#define GL_Blue2                        LCD_COLOR_BLUE2
#define GL_Red                          LCD_COLOR_RED
#define GL_Magenta                      LCD_COLOR_MAGENTA
#define GL_Green                        LCD_COLOR_GREEN
#define GL_Cyan                         LCD_COLOR_CYAN
#define GL_Yellow                       LCD_COLOR_YELLOW

#define GL_Horizontal                   LCD_DIR_HORIZONTAL
#define GL_Vertical                     LCD_DIR_VERTICAL

#define GL_FONT_BIG                     LCD_FONT_BIG
#define GL_FONT_SMALL                   LCD_FONT_SMALL
#define GL_FONT_BIG_WIDTH               LCD_FONT_BIG_WIDTH
#define GL_FONT_BIG_HEIGHT              LCD_FONT_BIG_HEIGHT
#define GL_FONT_SMALL_WIDTH             LCD_FONT_SMALL_WIDTH
#define GL_FONT_SMALL_HEIGHT            LCD_FONT_SMALL_HEIGHT

#define FirstPixel                      LCD_FirstPixel
#define MiddlePixel                     LCD_MiddlePixel
#define LastPixel                       LCD_LastPixel
#define SinglePixel                     LCD_SinglePixel

/**
  * @}
  */

/** @defgroup LcdHal_Exported_Variables
  * @{
  */
/**
  * @}
  */

/** @defgroup LcdHal_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup LcdHal_Exported_Functions
  * @{
  */

#ifdef __cplusplus
}
#endif

#endif /*__LCD_HAL_H */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics ***************************/
