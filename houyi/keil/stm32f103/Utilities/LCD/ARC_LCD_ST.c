/**
  ******************************************************************************
  * @file    LTK_LCD_ST.c
  * @author  leitek (leitek.taobao.com)
  * @version V1.0.0
  * @brief   LTK middleware. 
  *          This file provides LCD middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * COPYRIGHT leitek.taobao.com
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "LTK_LCD_ST.h"
#include "LTK_SysTick.h"
#include "LTK_Retarget.h"
#include "LTK_Font.h"
#include "LTK_GPIO.h"
#include "LTK_RCC.h"
#include <string.h>

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup LTK_LCD_ST
  * @{
  */ 

/** @defgroup LTK_LCD_ST_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_LCD_ST_Private_Defines
  * @{
  */

#define LTK_LCD_CS_SET()  GPIOD->BSRR = GPIO_Pin_2    /* chip select pin */
#define LTK_LCD_RD_SET()  GPIOC->BSRR = GPIO_Pin_10   /* register select pin */
#define LTK_LCD_WR_SET()  GPIOC->BSRR = GPIO_Pin_11   /* read strobe signal, low active */ 
#define LTK_LCD_RS_SET()  GPIOC->BSRR = GPIO_Pin_12   /* write strobe signal, low active */

#define LTK_LCD_CS_RESET()  GPIOD->BRR = GPIO_Pin_2     
#define LTK_LCD_RD_RESET()  GPIOC->BRR = GPIO_Pin_10       
#define LTK_LCD_WR_RESET()  GPIOC->BRR = GPIO_Pin_11   
#define LTK_LCD_RS_RESET()  GPIOC->BRR = GPIO_Pin_12     

#define LTK_LCD_BL_RESET() GPIO_ResetBits(GPIOC, GPIO_Pin_5)
#define LTK_LCD_BL_SET()   GPIO_SetBits(GPIOC, GPIO_Pin_5)


/**
  * @}
  */ 

/** @defgroup LTK_LCD_ST_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup LTK_LCD_ST_Private_Variables
  * @{
  */
static LTK_LCD_Params LTK_LCD_Param;
static LTK_LCD_Struct_Font LTK_LCD_Font;
/* Global variables to handle the right font */

uint16_t LCD_Height = 240;
uint16_t LCD_Width  = 320;
 
/**
  * @}
  */

/** @defgroup LTK_LCD_ST_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup LTK_LCD_ST_Private_Functions
  * @{
  */

/**
  * @brief  get the pointer to the LCD parameters.
  * @param  None
  * @retval the pointer to the LCD parameters
  */
LTK_LCD_Params *LTK_LCD_get_param(void)
{
    return &LTK_LCD_Param;
}

LTK_LCD_Struct_Font *LTK_LCD_get_Font(void)
{
    return &LTK_LCD_Font;
}

/**
  * @brief  initialize the LCD parameters struct.
  * @param  None
  * @retval None
  */
void LTK_LCD_Struct_Init(void)
{
    LTK_LCD_Struct_Font *lcd_font;
    lcd_font = LTK_LCD_get_Font();
        
    LTK_LCD_Param.LCD_Type = LCD_OTHER;
    LTK_LCD_Param.LCD_BusType = LCD_PARELLEL;
    LTK_LCD_Param.LCD_Text = "";

    lcd_font->LCD_Font = LCD_FONT_BIG;
    lcd_font->LCD_Font_Color = LCD_COLOR_WHITE;
}
  
/**
  * @brief  write index register.
  * @param  irData, the index register value to be written.
  * @retval None
  */
void LTK_LCD_WriteRegIndex(uint16_t irData)
{
    LTK_LCD_RS_RESET(); 
    LTK_LCD_CS_RESET(); 
    GPIO_Write(GPIOB, irData); 
    LTK_LCD_WR_RESET(); 
    LTK_LCD_WR_SET(); 
    LTK_LCD_CS_SET();
}

/**
  * @brief  write data.
  * @param  Data, the data to be written.
  * @retval None
  */
void LTK_LCD_WriteRAM(uint16_t Data)
{
    LTK_LCD_RS_SET(); 
    LTK_LCD_CS_RESET(); 
    GPIO_Write(GPIOB, Data); 
    LTK_LCD_WR_RESET();
    LTK_LCD_WR_SET(); 
    LTK_LCD_CS_SET();
}

/**
  * @brief  read data.
  * @param  None.
  * @retval Value read from LCD.
  */
uint16_t LTK_LCD_RD_DATA(void)
{
    uint16_t value;

    LTK_LCD_RS_SET();
    LTK_LCD_CS_RESET();
    LTK_LCD_RD_RESET();
    __NOP();
    __NOP();
    /* LTK_SysTick_Delay(5); */ /* delay 5us */
    LTK_LCD_RD_SET();
    
    value = GPIOB->IDR;
    LTK_LCD_CS_SET();
    return value; 
}

/**
  * @brief  Read LCD register.
  * @param  LCD_Reg, the register index to be read.
  * @retval value read from LCD.
  */
uint16_t LTK_LCD_ReadReg(uint16_t LCD_Reg)
{    
    uint16_t value;    
    GPIO_InitTypeDef GPIO_InitStructure;
    
    LTK_LCD_WriteRegIndex(LCD_Reg);  /* register index to be write */ 

    /* Configure port B as pull-up input */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* no need to read twice since it is not from GRAM */
    value = LTK_LCD_RD_DATA();
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    return value;  
}  

/**
  * @brief  Write LCD register.
  * @param  LCD_Reg, the register index to be written.
  * @param  LCD_RegValue, value to be written.
  * @retval None.
  */
void LTK_LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue)
{
    LTK_LCD_WriteRegIndex(LCD_Reg); 
    LTK_LCD_WriteRAM(LCD_RegValue); 
} 

/**
  * @brief  Prepare to write to the LCD RAM.
  * @param  None
  * @retval None
  */
void LTK_LCD_WriteRAM_Prepare(void)
{
    LTK_LCD_WriteRegIndex(LCD_REG_22H);
}

/**
  * @brief  Writes 1 word to the LCD RAM.
  * @param  RGB_Code: the pixel color in RGB mode (5-6-5).
  * @retval None
  */
void LTK_LCD_WriteRAMWord(uint16_t RGB_Code)
{
    LTK_LCD_WriteRAM_Prepare();
    LTK_LCD_WriteRAM(RGB_Code);
}

/**
  * @brief  Reads the LCD RAM.
  * @param  None
  * @retval uint16_t - LCD RAM Value.
  */
uint16_t LTK_LCD_ReadRAM(void)
{
    return LTK_LCD_ReadReg(LCD_REG_16H);
}

/**
  * @brief  Enables the Display.
  * @param  None
  * @retval None
  */
void LTK_LCD_DisplayOn(void)
{  
}


/**
  * @brief  Disables the Display.
  * @param  None
  * @retval None
  */
void LTK_LCD_DisplayOff(void)
{
}

/**
  * @brief  Sets the background color.
  * @param  Color: specifies the background color code RGB(5-6-5).
  * @retval None
  */
void LTK_LCD_SetBackColor(uint16_t Color)
{
    LTK_LCD_Struct_Font *lcd_font;
    lcd_font = LTK_LCD_get_Font();
    lcd_font->LCD_Background_color = Color;
}

/**
  * @brief  Sets the Text color.
  * @param  Color: specifies the Text color code RGB(5-6-5).
  * @retval None
  */
void LTK_LCD_SetTextColor(uint16_t Color)
{
    LTK_LCD_Struct_Font *lcd_font;
    lcd_font = LTK_LCD_get_Font();
    lcd_font->LCD_Font_Color = Color;
}

/**
  * @brief  get the font color.
  * @param  None
  * @retval the font color
  */
uint16_t LTK_LCD_GetTextColor(void)
{
    return LTK_LCD_Font.LCD_Font_Color;
}

/**
  * @brief  Clear the screen.
  * @param  Color, color to be filled.
  * @retval None
  */
void LTK_LCD_Clear(uint16_t Color)
{
    uint32_t index = 0;      
    LTK_LCD_SetCursor(0x00,0x0000);
    LTK_LCD_WriteRAM_Prepare();
    for(index = 0; index < LCD_Height * LCD_Width; index++)
    {
        LTK_LCD_WriteRAM(Color);    
    }
}

/**
  * @brief  Sets the cursor position.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position. 
  * @retval None
  */
__inline void LTK_LCD_SetCursor(uint16_t x, uint16_t y)
{
    if(LTK_LCD_Param.LCD_Type == LCD_HX8347A)
    {
        LTK_LCD_WriteReg(LCD_REG_03H, x & 0xff);
        LTK_LCD_WriteReg(LCD_REG_02H, (x >> 8) & 0xff);
        LTK_LCD_WriteReg(LCD_REG_07H, y & 0xff);
        LTK_LCD_WriteReg(LCD_REG_06H, (y >> 8) & 0xff);
    }
    else
    {
        LTK_LCD_WriteReg(LCD_REG_20H, x);
        LTK_LCD_WriteReg(LCD_REG_21H, y);
    }
}

/**
  * @brief  Draws a character on LCD without background.
  * @param  Xpos: the Line where to display the character shape.
  *         This parameter can be one of the following values:
  * @param  Ypos: start column address.
  * @param  c: pointer to the character data.
  * @retval None
  */
void LTK_LCD_DrawCharTransparent(uint16_t Xpos, uint16_t Ypos, const uint16_t *c) /* 16bit char */
{
    LTK_LCD_Struct_Font *lcd_font;
    uint32_t line_index = 0, pixel_index = 0;
    uint8_t Xaddress = 0;
    uint16_t Yaddress = 0;

    lcd_font = LTK_LCD_get_Font();
    Xaddress = Xpos;
    Yaddress = Ypos;

    for (line_index = 0; line_index < lcd_font->LCD_FontHeight; line_index++)
    {
        for (pixel_index = 0; pixel_index < lcd_font->LCD_FontWidth; pixel_index++)
        {
            /* SmallFonts have bytes in reverse order */
            if (( lcd_font->LCD_Font == LCD_FONT_BIG   && (((const uint16_t*)c)[line_index] & (1 << pixel_index)) == 0x00) ||
                ( lcd_font->LCD_Font == LCD_FONT_SMALL && (((const uint16_t*)c)[line_index] & (0x80 >> pixel_index)) == 0x00))
            {
                Yaddress--;
            }
            else
            {
                LTK_LCD_PutPixel(Xaddress, Yaddress--, lcd_font->LCD_Font_Color, SinglePixel);
            }
        }
        Xaddress++;
        Yaddress = Ypos;
    }
}

/**
  * @brief  Displays a maximum of 20 char on the LCD.
  * @param  Line: the Line where to display the character shape.
  * @param  *ptr: pointer to the string to display on LCD.
  * @retval None
  */
void LTK_LCD_DisplayAdjStringLine(uint16_t Line, uint16_t Column, uint8_t *ptr, GL_bool Transparent_Flag)
{
    LTK_LCD_Struct_Font *lcd_font;
    uint32_t index = 0;
    uint32_t iMaxChar;
    lcd_font = LTK_LCD_get_Font();
    iMaxChar = (Column / (lcd_font->LCD_FontWidth - 1));

    /* Send the string character by character on lCD */
    while ((*ptr != 0) & (index < iMaxChar))
    { /* Display one character on LCD */
        LTK_LCD_DisplayChar(Line, Column, *ptr, Transparent_Flag);
        /* Decrement the column position by GL_FontWidth */
        if ( *ptr == 'A' || *ptr == 'G' || *ptr == 'M' || *ptr == 'O' || *ptr == 'Q' || *ptr == 'X' || *ptr == 'm')
            Column -= (lcd_font->LCD_FontWidth);
        else
            Column -= (lcd_font->LCD_FontWidth - 1);
        /* Point on the next character */
        ptr++;
        /* Increment the character counter */
        index++;
    }
}

/**
  * @brief  Displays one character (16dots width, 24dots height).
  * @param  Line: the Line where to display the character shape.
  *         This parameter can be one of the following values:
  *     @arg  - Linex: where x can be 0..9
  * @param  Column: start column address.
  * @param  Ascii: character ascii code, must be between 0x20 and 0x7E.
  * @param  GL_bool Trasparent_Flag, if TRUE it does not print the GL_BackColor
  * @retval None
  */
void LTK_LCD_DisplayChar(uint16_t Line, uint16_t Column, uint8_t Ascii, GL_bool Transparent_Flag)
{
    
    LTK_LCD_Struct_Font *lcd_font;
    lcd_font = LTK_LCD_get_Font();
    Ascii -= 32;
    switch (lcd_font->LCD_Font)
    {
        case LCD_FONT_BIG:
            if (Transparent_Flag)
                LTK_LCD_DrawCharTransparent(Line, Column, &GL_Font16x24.table[Ascii * lcd_font->LCD_FontHeight] );
            else
                LTK_LCD_DrawChar(Line, Column, (&GL_Font16x24.table[Ascii * lcd_font->LCD_FontHeight]));
            break;

        case LCD_FONT_SMALL:
            if (Transparent_Flag)
                LTK_LCD_DrawCharTransparent(Line, Column, &GL_Font8x12_bold.table[Ascii * lcd_font->LCD_FontHeight] );
            else
                LTK_LCD_DrawChar(Line, Column, &GL_Font8x12_bold.table[Ascii * lcd_font->LCD_FontHeight]);
            break;

        default:
            break;
    }
}

/**
  * @brief  Sets a display window
  * @param  Xpos: specifies the X buttom left position.
  * @param  Ypos: specifies the Y buttom left position.
  * @param  Height: display window height.
  * @param  Width: display window width.
  * @retval None
  */
__inline void LTK_LCD_SetDisplayWindow(uint8_t Xpos,uint16_t Ypos,uint8_t Height,uint16_t Width)
{
    
    if(LTK_LCD_Param.LCD_Type == LCD_HX8347A)
    {
        /* Horizontal GRAM Start Address */
        LTK_LCD_WriteReg(LCD_REG_03H, (Xpos - Height + 1) & 0xff);
        LTK_LCD_WriteReg(LCD_REG_02H, ((Xpos - Height + 1) >> 8) & 0xff);
        /* Horizontal GRAM End Address */
        LTK_LCD_WriteReg(LCD_REG_05H, Xpos & 0xff);
        LTK_LCD_WriteReg(LCD_REG_04H, (Xpos >> 8) & 0xff);
        /* Vertical GRAM Start Address */
        LTK_LCD_WriteReg(LCD_REG_07H, (Ypos - Width + 1) & 0xff);\
        LTK_LCD_WriteReg(LCD_REG_06H, ((Ypos - Width + 1) >> 8) & 0xff);
        /* Vertical GRAM End Address */
        LTK_LCD_WriteReg(LCD_REG_09H, Ypos & 0xff);
        LTK_LCD_WriteReg(LCD_REG_08H, (Ypos >> 8) & 0xff);
    }
    else
    {
        /* Horizontal GRAM Start Address */
        LTK_LCD_WriteReg(LCD_REG_50H, (Xpos - Height + 1));
        /* Horizontal GRAM End Address */
        LTK_LCD_WriteReg(LCD_REG_51H, Xpos);
        /* Vertical GRAM Start Address */
        LTK_LCD_WriteReg(LCD_REG_52H, (Ypos - Width + 1));
        /* Vertical GRAM End Address */
        LTK_LCD_WriteReg(LCD_REG_53H, Ypos);
        LTK_LCD_SetCursor(Xpos, Ypos);
    }
}


/**
  * @brief  Displays a line.
  * @param Xpos: specifies the X position.
  * @param Ypos: specifies the Y position.
  * @param Length: line length.
  * @param Direction: line direction.
  *   This parameter can be one of the following values: Vertical or Horizontal.
  * @retval None
  */
void LTK_LCD_DrawLine(uint8_t Xpos, uint16_t Ypos, uint16_t Length, uint8_t Direction)
{
    uint32_t i = 0;
    LTK_LCD_Struct_Font *lcd_font;
    lcd_font = LTK_LCD_get_Font();
    LTK_LCD_SetCursor(Xpos, Ypos);
    if(Direction == LCD_DIR_HORIZONTAL)
    {
        LTK_LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
        for(i = 0; i < Length; i++)
        {
            LCD_WriteRAM(lcd_font->LCD_Font_Color);
        }
    }
    else
    {
        for(i = 0; i < Length; i++)
        {
            LTK_LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
            LTK_LCD_WriteRAM(lcd_font->LCD_Font_Color);
            Xpos++;
            LTK_LCD_SetCursor(Xpos, Ypos);
        }
    }
}

/**
  * @brief  Displays a rectangle.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  Height: display rectangle height.
  * @param  Width: display rectangle width.
  * @retval None
  */
void LTK_LCD_DrawRect(uint8_t Xpos, uint16_t Ypos, uint8_t Height, uint16_t Width)
{
    LTK_LCD_DrawLine(Xpos, Ypos, Width, LCD_DIR_HORIZONTAL);
    LTK_LCD_DrawLine((Xpos + Height), Ypos, Width, LCD_DIR_HORIZONTAL);

    LTK_LCD_DrawLine(Xpos, Ypos, Height, LCD_DIR_VERTICAL);
    LTK_LCD_DrawLine(Xpos, (Ypos - Width + 1), Height, LCD_DIR_VERTICAL);
}

/**
  * @brief  Displays a circle.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  Radius: the radius size of the circle
  * @retval None
  */
void LTK_LCD_DrawCircle(uint8_t Xpos, uint16_t Ypos, uint16_t Radius)
{
    int32_t  D;/* Decision Variable */
    uint32_t  CurX;/* Current X Value */
    uint32_t  CurY;/* Current Y Value */
    LTK_LCD_Struct_Font *lcd_font;
    lcd_font = LTK_LCD_get_Font();
    D = 3 - (Radius << 1);
    CurX = 0;
    CurY = Radius;

    while (CurX <= CurY)
    {
        LTK_LCD_SetCursor(Xpos + CurX, Ypos + CurY);
        LTK_LCD_WriteRAMWord(lcd_font->LCD_Font_Color);

        LTK_LCD_SetCursor(Xpos + CurX, Ypos - CurY);
        LTK_LCD_WriteRAMWord(lcd_font->LCD_Font_Color);

        LTK_LCD_SetCursor(Xpos - CurX, Ypos + CurY);
        LTK_LCD_WriteRAMWord(lcd_font->LCD_Font_Color);

        LTK_LCD_SetCursor(Xpos - CurX, Ypos - CurY);
        LTK_LCD_WriteRAMWord(lcd_font->LCD_Font_Color);

        LTK_LCD_SetCursor(Xpos + CurY, Ypos + CurX);
        LTK_LCD_WriteRAMWord(lcd_font->LCD_Font_Color);

        LTK_LCD_SetCursor(Xpos + CurY, Ypos - CurX);
        LTK_LCD_WriteRAMWord(lcd_font->LCD_Font_Color);

        LTK_LCD_SetCursor(Xpos - CurY, Ypos + CurX);
        LTK_LCD_WriteRAMWord(lcd_font->LCD_Font_Color);

        LTK_LCD_SetCursor(Xpos - CurY, Ypos - CurX);
        LTK_LCD_WriteRAMWord(lcd_font->LCD_Font_Color);

        if (D < 0)
        {
            D += (CurX << 2) + 6;
        }
        else
        {
            D += ((CurX - CurY) << 2) + 10;
            CurY--;
        }
        CurX++;
    }
}

/**
  * @brief  Copy 4 bytes from bitmap array to 32Bit buffer
  * @param  ptrBitmap - Bitmap pointer
  * @param  ptr32BitBuffer - 32Bit buffer to fill
  * @retval None
  */
void BmpBuffer32BitRead(uint32_t* ptr32BitBuffer, uint8_t* ptrBitmap)
{
    *ptr32BitBuffer = 0;
    *ptr32BitBuffer = (*ptrBitmap);
    *ptr32BitBuffer += (*(ptrBitmap + 1)) << 8;
    *ptr32BitBuffer += (*(ptrBitmap + 2)) << 16;
    *ptr32BitBuffer += (*(ptrBitmap + 3)) << 24;
}

/**
  * @brief  Displays a bitmap picture
  * @param  BmpAddress: Bmp picture address
  * @retval None
  */
void LTK_LCD_DrawBMP(uint8_t* ptrBitmap)
{
    uint32_t uDataAddr = 0, uBmpSize = 0;
    uint16_t uBmpData;

    BmpBuffer32BitRead(&uBmpSize, ptrBitmap + 2);
    BmpBuffer32BitRead(&uDataAddr, ptrBitmap + 10);

    if(LTK_LCD_Param.LCD_Type == LCD_HX8347A)
    {
        LTK_LCD_WriteReg(LCD_REG_16H, 0x0048);
    }
    else
    {
        LTK_LCD_WriteReg(LCD_REG_03H, 0x1008);
    }
    LTK_LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */

    /* Read bitmap data and write them to LCD */
    for (; uDataAddr < uBmpSize; uDataAddr += 2)
    {
        uBmpData = (uint16_t)(*(ptrBitmap + uDataAddr)) + (uint16_t)((*(ptrBitmap + uDataAddr + 1)) << 8);
        LTK_LCD_WriteRAM( uBmpData );
    }

    
    if(LTK_LCD_Param.LCD_Type == LCD_HX8347A)
    {
        LTK_LCD_WriteReg(LCD_REG_16H, 0x00C8);
    }
    else
    {
        LTK_LCD_WriteReg(LCD_REG_03H, 0x1018);
    }
}

/**
  * @brief  Sets the Font (Big or Small).
  * @param  uFont: specifies the Font (GL_FONT_BIG or GL_FONT_SMALL).
  * @retval None
  */
void LTK_LCD_SetFont(uint8_t uFont)
{
    LTK_LCD_Struct_Font *lcd_font;
    lcd_font = LTK_LCD_get_Font();
    
    lcd_font->LCD_Font = (LTK_LCD_FONT_SIZE_TYPE) uFont;
    switch (lcd_font->LCD_Font)
    {
        case LCD_FONT_BIG:
            lcd_font->LCD_FontWidth = GL_FONT_BIG_WIDTH;
            lcd_font->LCD_FontHeight = GL_FONT_BIG_HEIGHT;
            break;

        case LCD_FONT_SMALL:
            lcd_font->LCD_FontWidth  = GL_FONT_SMALL_WIDTH;
            lcd_font->LCD_FontHeight = GL_FONT_SMALL_HEIGHT;
            break;

        default:
            break;
    } /* End switch */
}

/**
  * @brief  Switches the backlight either ON or OFF
  * @param  state. This parameter can be one of the following values:
  *     @arg   LCD_BACKLIGHT_ON
  *     @arg   LCD_BACKLIGHT_OFF
  * @retval None
  */
void LTK_LCD_BackLightSwitch(uint8_t Backlight_State)
{
    if (Backlight_State == LCD_BACKLIGHT_OFF)
    { /* Turning OFF the LCD Backlight */
        LTK_LCD_BL_SET();
        LTK_LCD_DisplayOff();
    }
    else if (Backlight_State == LCD_BACKLIGHT_ON)
    { /* Turning ON the LCD Backlight */
        LTK_LCD_BL_RESET();
        LTK_LCD_DisplayOn();
    }
}

/**
  * @brief  Disables LCD Window mode.
  * @param  None
  * @retval None
  */
void LTK_LCD_WindowModeDisable(void)
{
      LTK_LCD_SetDisplayWindow(239, 0x13F, 240, 320);
}

/**
  * @brief  Draw one pixel at position given by Xpos, Ypos of color Color.
  *     Three different modes are specified by PixelSpec in order to save time:
  *     1.FirstPixel, MiddlePixel and LasPixel are used for fastened block-writing
  *       to GRAM (for instance: drawing rectangle, horizontal line etc.)
  *     2.SinglePixel is used for drawing stand-alone pixel. (for instance:
  *       drawing circle, character etc.).
  * @param  Xpos: specifies X position
  * @param  Ypos: specifies Y position
  * @param  Color: RGB color of point
  * @param  PixelSpec: specifies Mode of putting pixel.
  *         This parameter can be one of the following values:
  *     @arg  - FirstPixel:  Starting pixel of block-writing sequence.
  *     @arg  - MiddlePixel: Middle-located pixel of block-writing sequence.
  *     @arg  - LasPixel:    Ending pixel of block-writing sequence
  *     @arg  - SinglePixel: Separated pixel.
  * @retval None
  */
void LTK_LCD_PutPixel(uint16_t Xpos, uint16_t Ypos, uint16_t Color, uint8_t PixelSpec)
{
    /*Start part of put pixel for first pixel of block and for single one.
    It consists of set the cursor's position and GRAM prepare sequence.*/
    if (PixelSpec & (LCD_FirstPixel | LCD_SinglePixel))
    {
        LTK_LCD_SetCursor(Xpos, Ypos);
        LTK_LCD_WriteRAM_Prepare();
    }

    /*Write pixel's color to GRAM. Obligatory for all modes of PutPixel call.*/
    LTK_LCD_WriteRAM(Color);
}

/**
  * @brief  Get color of pixel located at appropriate position
  * @param  Xpos: specifies X position
  * @param  Ypos: specifies Y position
  * @retval uint16_t - RGB color of required pixel.
  */
uint16_t LTK_LCD_GetPixel(uint16_t Xpos, uint16_t Ypos)
{
    uint16_t tmpColor = 0, tmpRed = 0, tmpBlue = 0;

    /*Read the color of given pixel*/
    LTK_LCD_SetCursor(Xpos, Ypos);

    tmpColor = LTK_LCD_ReadRAM();

    /*Swap the R and B color channels*/
    tmpRed = (tmpColor & LCD_COLOR_BLUE) << 11;
    tmpBlue = (tmpColor & LCD_COLOR_RED) >> 11;
    tmpColor &= ~(LCD_COLOR_RED | LCD_COLOR_BLUE);
    tmpColor |= (tmpRed | tmpBlue);

    return tmpColor;
}

/**
  * @brief  Draws a character on LCD.
  * @param  Xpos: the Line where to display the character shape.
  *         This parameter can be one of the following values:
  *     @arg  - Linex: where x can be 0..9
  * @param  Ypos: start column address.
  * @param  c: pointer to the character data.
  * @retval None
  */
void LTK_LCD_DrawChar(uint8_t Xpos, uint16_t Ypos, const uint16_t *c) /* 16bit char */
{
    uint32_t line_index = 0, pixel_index = 0;
    uint8_t Xaddress = 0;
    uint16_t Yaddress = 0;
    __IO uint16_t tmp_color = 0;
    LTK_LCD_Struct_Font *lcd_font;

    lcd_font = LTK_LCD_get_Font();

    Xaddress = Xpos;
    Yaddress = Ypos;

    for (line_index = 0; line_index < lcd_font->LCD_FontHeight; line_index++)
    {
        /* SmallFonts have bytes in reverse order */
        if (( lcd_font->LCD_Font == LCD_FONT_BIG   && (((const uint16_t*)c)[line_index] & (1 << 0)) == 0x00) ||
        ( lcd_font->LCD_Font == LCD_FONT_SMALL && (((const uint16_t*)c)[line_index] & (0x80 >> 0)) == 0x00))
        {
            tmp_color = lcd_font->LCD_Background_color;
        }
        else
        {
            tmp_color = lcd_font->LCD_Font_Color;
        }

        LTK_LCD_PutPixel(Xaddress, Yaddress--, tmp_color, LCD_FirstPixel);

        for (pixel_index = 1; pixel_index < lcd_font->LCD_FontWidth - 1; pixel_index++)
        {
            /* SmallFonts have bytes in reverse order */
            if (( lcd_font->LCD_Font == LCD_FONT_BIG   && (((const uint16_t*)c)[line_index] & (1 << pixel_index)) == 0x00) ||
            ( lcd_font->LCD_Font == LCD_FONT_SMALL && (((const uint16_t*)c)[line_index] & (0x80 >> pixel_index)) == 0x00))
            {
                tmp_color = lcd_font->LCD_Background_color;
            }
            else
            {
                tmp_color = lcd_font->LCD_Font_Color;
            }

            LTK_LCD_PutPixel(Xaddress, Yaddress--, tmp_color, LCD_MiddlePixel);
        }
        pixel_index++;
        /* SmallFonts have bytes in reverse order */
        if (( lcd_font->LCD_Font == LCD_FONT_BIG   && (((const uint16_t*)c)[line_index] & (1 << pixel_index)) == 0x00) ||
        ( lcd_font->LCD_Font == LCD_FONT_SMALL && (((const uint16_t*)c)[line_index] & (0x80 >> pixel_index)) == 0x00))
        {
            tmp_color = lcd_font->LCD_Background_color;
        }
        else
        {
            tmp_color = lcd_font->LCD_Font_Color;
        }

        LTK_LCD_PutPixel(Xaddress, Yaddress--, tmp_color, LCD_LastPixel);

        Xaddress++;
        Yaddress = Ypos;
    }
}

/**
  * @brief  LCD_Change_Direction
  * @param  RCC_APBPeriph: specifies the APB peripheral to gates its clock.
  * @param  Direction: The Drawing Direction
  *         This parameter can be one of the following values:
  *     @arg  _0_degree
  *     @arg  _90_degree
  *     @arg  _180_degree
  *     @arg  _270_degree
  * @retval None
  */
void LTK_LCD_Change_Direction(LCD_Direction_TypeDef Direction)
{
    LTK_LCD_Struct_Font *lcd_font;
    lcd_font = LTK_LCD_get_Font();

    lcd_font->LCD_Direction = Direction;
    if(LTK_LCD_Param.LCD_Type == LCD_HX8347A)
    {
        if (lcd_font->LCD_Direction == _0_degree)
        {
            LTK_LCD_WriteReg(LCD_REG_16H, 0X00C8);
        }
        else if (lcd_font->LCD_Direction == _90_degree)
        {
            LTK_LCD_WriteReg(LCD_REG_16H, 0x00A8);
        }
        else if (lcd_font->LCD_Direction == _180_degree)
        {
            LTK_LCD_WriteReg(LCD_REG_16H, 0X0008);
        }
        else if (lcd_font->LCD_Direction == _270_degree)
        {
            LTK_LCD_WriteReg(LCD_REG_16H, 0x0068);
        }
    }
    else
    {
        if (lcd_font->LCD_Direction == _0_degree)
        {
            LTK_LCD_WriteReg(LCD_REG_03H, 0x1018);
        }
        else if (lcd_font->LCD_Direction == _90_degree)
        {
            LTK_LCD_WriteReg(LCD_REG_03H, 0x1030);
        }
        else if (lcd_font->LCD_Direction == _180_degree)
        {
            LTK_LCD_WriteReg(LCD_REG_03H, 0x1028);
        }
        else if (lcd_font->LCD_Direction == _270_degree)
        {
            LTK_LCD_WriteReg(LCD_REG_03H, 0x1000);
        }
    }
}

/**
  * @brief  LCD_WriteChar
  * @param  Xpos: The X axis position
  * @param  Ypos: The Y axis position
  * @param  *c:   The Character pointer
  * @retval None
  */
void LTK_LCD_WriteChar(uint16_t Xpos, uint16_t Ypos, const uint16_t *c)
{
    uint32_t index = 0, counter = 0;
    uint16_t Xaddress = 0;
    uint16_t Yaddress = 0;
    LTK_LCD_Struct_Font *lcd_font;
    lcd_font = LTK_LCD_get_Font();
    if ((lcd_font->LCD_Direction == _0_degree) || (lcd_font->LCD_Direction == _180_degree))
    {
        Xaddress = Xpos;
        LTK_LCD_SetCursor(Xaddress, Ypos);
    }
    else if ((lcd_font->LCD_Direction == _90_degree) || (lcd_font->LCD_Direction == _270_degree))
    {
        Yaddress = Ypos;
        LTK_LCD_SetCursor(Xpos, Yaddress);
    }

    for (index = 0; index < lcd_font->LCD_FontHeight; index++)
    {
        if ((LTK_LCD_Param.LCD_Type == LCD_ILI9320) ||
            (LTK_LCD_Param.LCD_Type == LCD_HX8347A))
        {
            LTK_LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
        }
        for (counter = 0; counter < lcd_font->LCD_FontWidth; counter++)
        {
            /* SmallFonts have bytes in reverse order */
            if (( lcd_font->LCD_Font == LCD_FONT_BIG   && (((const uint16_t*)c)[index] & (1 << counter)) == 0x00) ||
                ( lcd_font->LCD_Font == LCD_FONT_BIG && (c[index] & (0x80 >> counter)) == 0x00))
            {
                LTK_LCD_WriteRAM(lcd_font->LCD_Background_color);
            }
            else
            {
                LTK_LCD_WriteRAM(lcd_font->LCD_Font_Color);
            }
        }

        if (lcd_font->LCD_Direction == _0_degree)
        {
            Xaddress++;
            LTK_LCD_SetCursor(Xaddress, Ypos);
        }
        else if (lcd_font->LCD_Direction == _90_degree)
        {
            Yaddress++;
            LTK_LCD_SetCursor(Xpos, Yaddress);
        }
        else if (lcd_font->LCD_Direction == _180_degree)
        {
            Xaddress--;
            LTK_LCD_SetCursor(Xaddress, Ypos);
        }
        else if (lcd_font->LCD_Direction == _270_degree)
        {
            Yaddress--;
            LTK_LCD_SetCursor(Xpos, Yaddress);
        }
    }
}

/**
  * @brief  LCD_PrintChar
  * @param  Line:   The X axis position
  * @param  Column: The Y axis position
  * @param  Ascii:  The Character pointer
  * @retval None
  */
void LTK_LCD_PrintChar(uint16_t Line, uint16_t Column, uint8_t Ascii)
{
    LTK_LCD_Struct_Font *lcd_font;
    lcd_font = LTK_LCD_get_Font();
    Ascii -= 32;
    switch (lcd_font->LCD_Font)
    {
        case LCD_FONT_BIG:
            LTK_LCD_WriteChar( Line, Column, &GL_Font16x24.table[Ascii * lcd_font->LCD_FontHeight] );
            break;

        case LCD_FONT_SMALL:
            LTK_LCD_WriteChar( Line, Column, &GL_Font8x12_bold.table[Ascii * lcd_font->LCD_FontHeight] );
            break;

        default:
            break;
    }
}

/**
  * @brief  LCD_PrintStringLine
  * @param  Line:   The X axis position
  * @param  Column: The Y axis position
  * @param  *ptr:  The String of characters to be printed
  * @retval None
  */
void LTK_LCD_PrintStringLine(uint16_t Line, uint16_t Column, uint8_t *ptr)
{
    uint32_t counter = 0;
    uint16_t refcolumn = 0;
    uint8_t max_char_line = 0;
    static uint16_t line;
    LTK_LCD_Struct_Font *lcd_font;

    lcd_font = LTK_LCD_get_Font();

    line = Line;

    if (lcd_font->LCD_Direction == _0_degree)
    {
        max_char_line = (LCD_Width / lcd_font->LCD_FontWidth);
        refcolumn = Column;
    }
    else if (lcd_font->LCD_Direction == _90_degree)
    {
        max_char_line = (LCD_Height / lcd_font->LCD_FontWidth);
        refcolumn = Column;
    }
    else if (lcd_font->LCD_Direction == _180_degree)
    {
        max_char_line = (LCD_Width / lcd_font->LCD_FontWidth);
        refcolumn = Column;
        line = LCD_Height - Line;
    }
    else if (lcd_font->LCD_Direction == _270_degree)
    {
        max_char_line = (LCD_Height / lcd_font->LCD_FontWidth);
        refcolumn = Column;
        line = LCD_Width - Line;
    }

    /* Send the string character by character on LCD */
    while ((*ptr != 0) & (counter < max_char_line))
    {
        if (lcd_font->LCD_Direction == _0_degree)
        {
            /* Display one character on LCD */
            LTK_LCD_PrintChar(line, refcolumn, *ptr);
            /* Decrement the column position by 16 */
            refcolumn -= lcd_font->LCD_FontWidth;
        }
        else if (lcd_font->LCD_Direction == _90_degree)
        {
            /* Display one character on LCD */
            LTK_LCD_PrintChar(refcolumn, line, *ptr);
            /* Increment the column position by 16 */
            refcolumn += lcd_font->LCD_FontWidth;
        }
        else if (lcd_font->LCD_Direction == _180_degree)
        {
            /* Display one character on LCD */
            LTK_LCD_PrintChar(line, refcolumn, *ptr);
            /* Decrement the column position by 16 */
            refcolumn += lcd_font->LCD_FontWidth;
        }
        else if (lcd_font->LCD_Direction == _270_degree)
        {
            /* Display one character on LCD */
            LTK_LCD_PrintChar(refcolumn, line, *ptr);
            /* Increment the column position by 16 */
            refcolumn -= lcd_font->LCD_FontWidth;
        }

        /* Point on the next character */
        ptr++;
        /* Increment the character counter */
        counter++;
    }
}

/**
  * @brief  LCD_DrawMonoBMP
  * @param  *Pict:   The pointer to the image
  * @param  Xpos_Init: The X axis position
  * @param  Ypos_Init: The Y axis position
  * @param  Height:    The Height of the image
  * @param  Width:     The Width of the image
  * @retval None
  */
void LTK_LCD_DrawMonoBMP(const uint8_t *Pict, uint16_t Xpos_Init, uint16_t Ypos_Init, uint16_t Height, uint16_t Width)
{
    int32_t index = 0, counter = 0;
    LTK_LCD_Struct_Font *lcd_font;
    lcd_font = LTK_LCD_get_Font();
    
    LTK_LCD_SetDisplayWindow(Xpos_Init + Height - 1, Ypos_Init + Width - 1, Height, Width);

    LTK_LCD_SetCursor(Xpos_Init, Ypos_Init);

    if ((LTK_LCD_Param.LCD_Type == LCD_ILI9320) ||
        (LTK_LCD_Param.LCD_Type == LCD_HX8347A))
    {
        /* Prepare to write GRAM */
        LTK_LCD_WriteRAM_Prepare(); 
    }

    for (index = 0; index < (Height*Width) / 8; index++)
    {
        for (counter = 7; counter >= 0; counter--)
        {
            if ((Pict[index] & (1 << counter)) == 0x00)
            {
                LTK_LCD_WriteRAM(lcd_font->LCD_Background_color);
            }
            else
            {
                LTK_LCD_WriteRAM(lcd_font->LCD_Font_Color);
            }
        }
    }

    LTK_LCD_Change_Direction(lcd_font->LCD_Direction);
    LTK_LCD_SetDisplayWindow(LCD_Height - 1, LCD_Width - 1, LCD_Height, LCD_Width);
}

/**
  * @brief  Fill area with color.
  * @param  maxX: Maximum X coordinate
  * @param  minX: Minimum X coordinate
  * @param  maxY: Maximum Y coordinate
  * @param  minY: Minimum Y coordinate
  * @param  ptrBitmap: pointer to the image
  * @retval None
  */
void LTK_LCD_FillArea(uint16_t Xpos_Init, uint16_t Ypos_Init, uint16_t Height, uint16_t Width, uint16_t color)
{
    uint32_t area = 0;
    uint32_t index = 0;
    LTK_LCD_Struct_Font *lcd_font;
    lcd_font = LTK_LCD_get_Font();
    area =  Width *  Height;

    LTK_LCD_SetCursor(Xpos_Init, Ypos_Init);

    if ((LTK_LCD_Param.LCD_Type == LCD_ILI9320) ||
        (LTK_LCD_Param.LCD_Type == LCD_HX8347A))
    {
        LTK_LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    }

    for (index = 0;index < area; index++)
    {
        LTK_LCD_WriteRAM(color);
    }

    LTK_LCD_Change_Direction(lcd_font->LCD_Direction);
    LTK_LCD_SetDisplayWindow(LCD_Height - 1, LCD_Width - 1, LCD_Height, LCD_Width);
}

/**
  * @brief  LCD_DrawColorBMP
  * @param  *ptrBitmap:   The pointer to the image
  * @param  Xpos_Init: The X axis position
  * @param  Ypos_Init: The Y axis position
  * @param  Height:    The Height of the image
  * @param  Width:     The Width of the image
  * @retval None
  */
void LTK_LCD_DrawColorBMP(uint8_t* ptrBitmap, uint16_t Xpos_Init, uint16_t Ypos_Init, uint16_t Height, uint16_t Width)
{
    uint32_t uDataAddr = 0, uBmpSize = 0;
    uint16_t uBmpData = 0;
    LTK_LCD_Struct_Font *lcd_font;
    lcd_font = LTK_LCD_get_Font();
    BmpBuffer32BitRead(&uBmpSize, ptrBitmap + 2);  
    BmpBuffer32BitRead(&uDataAddr, ptrBitmap + 10);  

    LTK_LCD_SetCursor(Xpos_Init, Ypos_Init);

    if ((LTK_LCD_Param.LCD_Type == LCD_ILI9320) ||
        (LTK_LCD_Param.LCD_Type == LCD_HX8347A))
    {
        /* Prepare to write GRAM */
        LTK_LCD_WriteRAM_Prepare(); 
    }

    /* Read bitmap data and write them to LCD */
    for (; uDataAddr < uBmpSize; uDataAddr += 2)
    {
        uBmpData = (uint16_t)(*(ptrBitmap + uDataAddr)) + (uint16_t)((*(ptrBitmap + uDataAddr + 1)) << 8);
        LTK_LCD_WriteRAM( uBmpData );
    }

    LTK_LCD_Change_Direction(lcd_font->LCD_Direction);
    LTK_LCD_SetDisplayWindow(LCD_Height - 1, LCD_Width - 1, LCD_Height, LCD_Width);
}

/**
  * @brief  initialize panel.
  * @param  None.
  * @retval None
  */
void LTK_LGDP4531_Init(void)
{
    LTK_LCD_WriteReg(0X00,0X0001);
    LTK_SysTick_Delay(50);
    LTK_LCD_WriteReg(0X10,0X1628);   
    LTK_LCD_WriteReg(0X12,0X000e);  
    LTK_LCD_WriteReg(0X13,0X0A39);   
    LTK_SysTick_Delay(50);
    LTK_LCD_WriteReg(0X11,0X0040);   
    LTK_LCD_WriteReg(0X15,0X0050);   
    LTK_SysTick_Delay(50);
    LTK_LCD_WriteReg(0X12,0X001e);  
    LTK_SysTick_Delay(50);
    LTK_LCD_WriteReg(0X10,0X1620);   
    LTK_LCD_WriteReg(0X13,0X2A39);   
    LTK_SysTick_Delay(50);
    LTK_LCD_WriteReg(0X01,0X0100);   
    LTK_LCD_WriteReg(0X02,0X0300);   
    LTK_LCD_WriteReg(0X03,0X1030); 
    LTK_LCD_WriteReg(0X08,0X0202);   
    LTK_LCD_WriteReg(0X0A,0X0008);   
    LTK_LCD_WriteReg(0X30,0X0000);   
    LTK_LCD_WriteReg(0X31,0X0402);   
    LTK_LCD_WriteReg(0X32,0X0106);   
    LTK_LCD_WriteReg(0X33,0X0503);   
    LTK_LCD_WriteReg(0X34,0X0104);   
    LTK_LCD_WriteReg(0X35,0X0301);   
    LTK_LCD_WriteReg(0X36,0X0707);   
    LTK_LCD_WriteReg(0X37,0X0305);   
    LTK_LCD_WriteReg(0X38,0X0208);   
    LTK_LCD_WriteReg(0X39,0X0F0B);   
    LTK_LCD_WriteReg(0X41,0X0002);   
    LTK_LCD_WriteReg(0X60,0X2700);   
    LTK_LCD_WriteReg(0X61,0X0001);   
    LTK_LCD_WriteReg(0X90,0X0210);   
    LTK_LCD_WriteReg(0X92,0X010A);   
    LTK_LCD_WriteReg(0X93,0X0004);   
    LTK_LCD_WriteReg(0XA0,0X0100);   
    LTK_LCD_WriteReg(0X07,0X0001);   
    LTK_LCD_WriteReg(0X07,0X0021);   
    LTK_LCD_WriteReg(0X07,0X0023);   
    LTK_LCD_WriteReg(0X07,0X0033);   
    LTK_LCD_WriteReg(0X07,0X0133);   
    LTK_LCD_WriteReg(0XA0,0X0000); 
}

/**
  * @brief  initialize panel.
  * @param  None.
  * @retval None
  */
void LTK_ILI9325_Init(void)
{
    /* Start Initial Sequence ------------------------------------------------*/
    LTK_LCD_WriteReg(LCD_REG_00H, 0x0001); /* Start internal OSC. */
    LTK_LCD_WriteReg(LCD_REG_01H, 0x0100); /* Set SS and SM bit */
    LTK_LCD_WriteReg(LCD_REG_02H, 0x0700); /* Set 1 line inversion */
    LTK_LCD_WriteReg(LCD_REG_03H, 0x1018); /* Set GRAM write direction and BGR=1. */
    LTK_LCD_WriteReg(LCD_REG_04H, 0x0000); /* Resize register */
    LTK_LCD_WriteReg(LCD_REG_08H, 0x0202); /* Set the back porch and front porch */
    LTK_LCD_WriteReg(LCD_REG_09H, 0x0000); /* Set non-display area refresh cycle ISC[3:0] */
    LTK_LCD_WriteReg(LCD_REG_0AH, 0x0000); /* FMARK function */
    LTK_LCD_WriteReg(LCD_REG_0CH, 0x0000); /* RGB interface setting */
    LTK_LCD_WriteReg(LCD_REG_0DH, 0x0000); /* Frame marker Position */
    LTK_LCD_WriteReg(LCD_REG_0FH, 0x0000); /* RGB interface polarity */

    /* Power On sequence -----------------------------------------------------*/
    LTK_LCD_WriteReg(LCD_REG_10H, 0x0000); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
    LTK_LCD_WriteReg(LCD_REG_11H, 0x0000); /* DC1[2:0], DC0[2:0], VC[2:0] */
    LTK_LCD_WriteReg(LCD_REG_12H, 0x0000); /* VREG1OUT voltage */
    LTK_LCD_WriteReg(LCD_REG_13H, 0x0000); /* VDV[4:0] for VCOM amplitude */
    LTK_SysTick_Delay(200);                      /* Dis-charge capacitor power voltage (200ms) */
    LTK_LCD_WriteReg(LCD_REG_10H, 0x17B0); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
    LTK_LCD_WriteReg(LCD_REG_11H, 0x0137); /* DC1[2:0], DC0[2:0], VC[2:0] */
    LTK_SysTick_Delay(50);                       /* Delay 50 ms */
    LTK_LCD_WriteReg(LCD_REG_12H, 0x0139); /* VREG1OUT voltage */
    LTK_SysTick_Delay(50);                       /* Delay 50 ms */
    LTK_LCD_WriteReg(LCD_REG_13H, 0x1d00); /* VDV[4:0] for VCOM amplitude */
    LTK_LCD_WriteReg(LCD_REG_29H, 0x0013); /* VCM[4:0] for VCOMH */
    LTK_SysTick_Delay(50);                       /* Delay 50 ms */
    LTK_LCD_WriteReg(LCD_REG_20H, 0x0000); /* GRAM horizontal Address */
    LTK_LCD_WriteReg(LCD_REG_21H, 0x0000); /* GRAM Vertical Address */

    /* Adjust the Gamma Curve (ILI9325)---------------------------------------*/
    LTK_LCD_WriteReg(LCD_REG_30H, 0x0007);
    LTK_LCD_WriteReg(LCD_REG_31H, 0x0302);
    LTK_LCD_WriteReg(LCD_REG_32H, 0x0105);
    LTK_LCD_WriteReg(LCD_REG_35H, 0x0206);
    LTK_LCD_WriteReg(LCD_REG_36H, 0x0808);
    LTK_LCD_WriteReg(LCD_REG_37H, 0x0206);
    LTK_LCD_WriteReg(LCD_REG_38H, 0x0504);
    LTK_LCD_WriteReg(LCD_REG_39H, 0x0007);
    LTK_LCD_WriteReg(LCD_REG_3CH, 0x0105);
    LTK_LCD_WriteReg(LCD_REG_3DH, 0x0808);

    /* Set GRAM area ---------------------------------------------------------*/
    LTK_LCD_WriteReg(LCD_REG_50H, 0x0000); /* Horizontal GRAM Start Address */
    LTK_LCD_WriteReg(LCD_REG_51H, 0x00EF); /* Horizontal GRAM End Address */
    LTK_LCD_WriteReg(LCD_REG_52H, 0x0000); /* Vertical GRAM Start Address */
    LTK_LCD_WriteReg(LCD_REG_53H, 0x013F); /* Vertical GRAM End Address */

    LTK_LCD_WriteReg(LCD_REG_60H,  0xA700); /* Gate Scan Line(GS=1, scan direction is G320~G1) */
    LTK_LCD_WriteReg(LCD_REG_61H,  0x0001); /* NDL,VLE, REV */
    LTK_LCD_WriteReg(LCD_REG_6AH, 0x0000); /* set scrolling line */

    /* Partial Display Control -----------------------------------------------*/
    LTK_LCD_WriteReg(LCD_REG_80H, 0x0000);
    LTK_LCD_WriteReg(LCD_REG_81H, 0x0000);
    LTK_LCD_WriteReg(LCD_REG_82H, 0x0000);
    LTK_LCD_WriteReg(LCD_REG_83H, 0x0000);
    LTK_LCD_WriteReg(LCD_REG_84H, 0x0000);
    LTK_LCD_WriteReg(LCD_REG_85H, 0x0000);

    /* Panel Control ---------------------------------------------------------*/
    LTK_LCD_WriteReg(LCD_REG_90H, 0x0010);
    LTK_LCD_WriteReg(LCD_REG_92H, 0x0000);
    LTK_LCD_WriteReg(LCD_REG_93H, 0x0003);
    LTK_LCD_WriteReg(LCD_REG_95H, 0x0110);
    LTK_LCD_WriteReg(LCD_REG_97H, 0x0000);
    LTK_LCD_WriteReg(LCD_REG_98H, 0x0000);

    /* set GRAM write direction and BGR = 1 */
    /* I/D=00 (Horizontal : increment, Vertical : decrement) */
    /* AM=1 (address is updated in vertical writing direction) */
    LTK_LCD_WriteReg(LCD_REG_03H, (1<<12)|(3<<4)|(0<<3));

    LTK_LCD_WriteReg(LCD_REG_07H, 0x0133); /* 262K color and display ON */
}

/**
  * @brief  initialize panel.
  * @param  None.
  * @retval None
  */
void LTK_ILI9320_Init(void)
{
    LTK_SysTick_Delay(50); /* Delay 50 ms */
    /* Start Initial Sequence ------------------------------------------------*/
    LTK_LCD_WriteReg(LCD_REG_E5H, 0x8000); /* Set the internal vcore voltage */
    LTK_LCD_WriteReg(LCD_REG_00H,  0x0001); /* Start internal OSC. */
    LTK_LCD_WriteReg(LCD_REG_01H,  0x0100); /* set SS and SM bit */
    LTK_LCD_WriteReg(LCD_REG_02H,  0x0700); /* set 1 line inversion */
    LTK_LCD_WriteReg(LCD_REG_03H,  (1<<12)|(3<<4)|(0<<3)); /* set GRAM write direction and BGR=1. */
    LTK_LCD_WriteReg(LCD_REG_04H,  0x0000); /* Resize register */
    LTK_LCD_WriteReg(LCD_REG_08H,  0x0202); /* set the back porch and front porch */
    LTK_LCD_WriteReg(LCD_REG_09H,  0x0000); /* set non-display area refresh cycle ISC[3:0] */
    LTK_LCD_WriteReg(LCD_REG_0AH, 0x0000); /* FMARK function */
    LTK_LCD_WriteReg(LCD_REG_0CH, 0x0000); /* RGB interface setting */
    LTK_LCD_WriteReg(LCD_REG_0DH, 0x0000); /* Frame marker Position */
    LTK_LCD_WriteReg(LCD_REG_0FH, 0x0000); /* RGB interface polarity */
    /* Power On sequence -----------------------------------------------------*/
    LTK_LCD_WriteReg(LCD_REG_10H, 0x0000); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
    LTK_LCD_WriteReg(LCD_REG_11H, 0x0000); /* DC1[2:0], DC0[2:0], VC[2:0] */
    LTK_LCD_WriteReg(LCD_REG_12H, 0x0000); /* VREG1OUT voltage */
    LTK_LCD_WriteReg(LCD_REG_13H, 0x0000); /* VDV[4:0] for VCOM amplitude */
    LTK_SysTick_Delay(200);                      /* Dis-charge capacitor power voltage (200ms) */
    LTK_LCD_WriteReg(LCD_REG_10H, 0x17B0); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
    LTK_LCD_WriteReg(LCD_REG_11H, 0x0137); /* DC1[2:0], DC0[2:0], VC[2:0] */
    LTK_SysTick_Delay(50);                       /* Delay 50 ms */
    LTK_LCD_WriteReg(LCD_REG_12H, 0x0139); /* VREG1OUT voltage */
    LTK_SysTick_Delay(50);                       /* Delay 50 ms */
    LTK_LCD_WriteReg(LCD_REG_13H, 0x1d00); /* VDV[4:0] for VCOM amplitude */
    LTK_LCD_WriteReg(LCD_REG_29H, 0x0013); /* VCM[4:0] for VCOMH */
    LTK_SysTick_Delay(50);                       /* Delay 50 ms */
    LTK_LCD_WriteReg(LCD_REG_20H, 0x0000); /* GRAM horizontal Address */
    LTK_LCD_WriteReg(LCD_REG_21H, 0x0000); /* GRAM Vertical Address */
    /* Adjust the Gamma Curve ------------------------------------------------*/
    LTK_LCD_WriteReg(LCD_REG_30H, 0x0006);
    LTK_LCD_WriteReg(LCD_REG_31H, 0x0101);
    LTK_LCD_WriteReg(LCD_REG_32H, 0x0003);
    LTK_LCD_WriteReg(LCD_REG_35H, 0x0106);
    LTK_LCD_WriteReg(LCD_REG_36H, 0x0b02);
    LTK_LCD_WriteReg(LCD_REG_37H, 0x0302);
    LTK_LCD_WriteReg(LCD_REG_38H, 0x0707);
    LTK_LCD_WriteReg(LCD_REG_39H, 0x0007);
    LTK_LCD_WriteReg(LCD_REG_3CH, 0x0600);
    LTK_LCD_WriteReg(LCD_REG_3DH, 0x020b);
  
    /* Set GRAM area ---------------------------------------------------------*/
    LTK_LCD_WriteReg(LCD_REG_50H, 0x0000); /* Horizontal GRAM Start Address */
    LTK_LCD_WriteReg(LCD_REG_51H, 0x00EF); /* Horizontal GRAM End Address */
    LTK_LCD_WriteReg(LCD_REG_52H, 0x0000); /* Vertical GRAM Start Address */
    LTK_LCD_WriteReg(LCD_REG_53H, 0x013F); /* Vertical GRAM End Address */
    LTK_LCD_WriteReg(LCD_REG_60H,  0x2700); /* Gate Scan Line */
    LTK_LCD_WriteReg(LCD_REG_61H,  0x0001); /* NDL,VLE, REV */
    LTK_LCD_WriteReg(LCD_REG_6AH, 0x0000); /* set scrolling line */
    /* Partial Display Control -----------------------------------------------*/
    LTK_LCD_WriteReg(LCD_REG_80H, 0x0000);
    LTK_LCD_WriteReg(LCD_REG_81H, 0x0000);
    LTK_LCD_WriteReg(LCD_REG_82H, 0x0000);
    LTK_LCD_WriteReg(LCD_REG_83H, 0x0000);
    LTK_LCD_WriteReg(LCD_REG_84H, 0x0000);
    LTK_LCD_WriteReg(LCD_REG_85H, 0x0000);
    /* Panel Control ---------------------------------------------------------*/
    LTK_LCD_WriteReg(LCD_REG_90H, 0x0010);
    LTK_LCD_WriteReg(LCD_REG_92H, 0x0000);
    LTK_LCD_WriteReg(LCD_REG_93H, 0x0003);
    LTK_LCD_WriteReg(LCD_REG_95H, 0x0110);
    LTK_LCD_WriteReg(LCD_REG_97H, 0x0000);
    LTK_LCD_WriteReg(LCD_REG_98H, 0x0000);
    /* Set GRAM write direction and BGR = 1 */
    /* I/D=01 (Horizontal : increment, Vertical : decrement) */
    /* AM=1 (address is updated in vertical writing direction) */
    LTK_LCD_WriteReg(LCD_REG_03H, (1<<12)|(3<<4)|(0<<3));
    LTK_LCD_WriteReg(LCD_REG_07H, 0x0173); /* 262K color and display ON */
}

/**
  * @brief  initialize panel.
  * @param  None.
  * @retval None
  */
void LTK_HX8347A_Init()
{   
    //=========Initial HX8347  for INL2.8"QVGA Panel======// 
    LTK_SysTick_Delay(10); // Delay 1ms 
    LTK_SysTick_Delay(10); // Delay 10ms  
    LTK_SysTick_Delay(150); // Delay 150 ms 

    LTK_LCD_WriteReg(LCD_REG_42H,0x0008);   
    //Gamma setting  
    LTK_LCD_WriteReg(LCD_REG_46H,0x00B4); 
    LTK_LCD_WriteReg(LCD_REG_47H,0x0043); 
    LTK_LCD_WriteReg(LCD_REG_48H,0x0013); 
    LTK_LCD_WriteReg(LCD_REG_49H,0x0047); 
    LTK_LCD_WriteReg(LCD_REG_4AH,0x0014); 
    LTK_LCD_WriteReg(LCD_REG_4BH,0x0036); 
    LTK_LCD_WriteReg(LCD_REG_4CH,0x0003); 
    LTK_LCD_WriteReg(LCD_REG_4DH,0x0046); 
    LTK_LCD_WriteReg(LCD_REG_4EH,0x0005);  
    LTK_LCD_WriteReg(LCD_REG_4FH,0x0010);  
    LTK_LCD_WriteReg(LCD_REG_50H,0x0008);  
    LTK_LCD_WriteReg(LCD_REG_51H,0x000a);  

    //Window Setting 
    LTK_LCD_WriteReg(LCD_REG_02H,0x0000); 
    LTK_LCD_WriteReg(LCD_REG_03H,0x0000); 
    LTK_LCD_WriteReg(LCD_REG_04H,0x0000); 
    LTK_LCD_WriteReg(LCD_REG_05H,0x00EF); 
    LTK_LCD_WriteReg(LCD_REG_06H,0x0000); 
    LTK_LCD_WriteReg(LCD_REG_07H,0x0000); 
    LTK_LCD_WriteReg(LCD_REG_08H,0x0001); 
    LTK_LCD_WriteReg(LCD_REG_09H,0x003F); 

    LTK_SysTick_Delay(10); 

    LTK_LCD_WriteReg(LCD_REG_01H,0x0006); 
    LTK_LCD_WriteReg(LCD_REG_16H,0x00C8);   
    LTK_LCD_WriteReg(LCD_REG_23H,0x0095); 
    LTK_LCD_WriteReg(LCD_REG_24H,0x0095); 
    LTK_LCD_WriteReg(LCD_REG_25H,0x00FF); 
    LTK_LCD_WriteReg(LCD_REG_27H,0x0002); 
    LTK_LCD_WriteReg(LCD_REG_28H,0x0002); 
    LTK_LCD_WriteReg(LCD_REG_29H,0x0002); 
    LTK_LCD_WriteReg(LCD_REG_2AH,0x0002); 
    LTK_LCD_WriteReg(LCD_REG_2CH,0x0002); 
    LTK_LCD_WriteReg(LCD_REG_2DH,0x0002); 

    LTK_LCD_WriteReg(LCD_REG_3AH,0x0001);  
    LTK_LCD_WriteReg(LCD_REG_3BH,0x0001);  
    LTK_LCD_WriteReg(LCD_REG_3CH,0x00F0);    
    LTK_LCD_WriteReg(LCD_REG_3DH,0x0000); 

    LTK_SysTick_Delay(20); 

    LTK_LCD_WriteReg(LCD_REG_35H,0x0038); 
    LTK_LCD_WriteReg(LCD_REG_36H,0x0078); 
    LTK_LCD_WriteReg(LCD_REG_3EH,0x0038); 
    LTK_LCD_WriteReg(LCD_REG_40H,0x000F); 
    LTK_LCD_WriteReg(LCD_REG_41H,0x00F0);  

    LTK_LCD_WriteReg(LCD_REG_38H,0x0000); 

    // Power Setting 
    LTK_LCD_WriteReg(LCD_REG_19H,0x0049);  
    LTK_LCD_WriteReg(LCD_REG_93H,0x000A); 

    LTK_SysTick_Delay(10); 

    LTK_LCD_WriteReg(LCD_REG_20H,0x0020);   
    LTK_LCD_WriteReg(LCD_REG_1DH,0x0003);   
    LTK_LCD_WriteReg(LCD_REG_1EH,0x0000);  

    LTK_LCD_WriteReg(LCD_REG_1FH,0x0009);   

    LTK_LCD_WriteReg(LCD_REG_44H,0x0053);  
    LTK_LCD_WriteReg(LCD_REG_45H,0x0010);   


    LTK_SysTick_Delay(10);  

    LTK_LCD_WriteReg(LCD_REG_1CH,0x0004);  

    LTK_SysTick_Delay(20); 

    LTK_LCD_WriteReg(LCD_REG_43H,0x0080);    

    LTK_SysTick_Delay(5); 

    LTK_LCD_WriteReg(LCD_REG_1BH,0x000a);    

    LTK_SysTick_Delay(40);  

    LTK_LCD_WriteReg(LCD_REG_1BH,0x0012);    

    LTK_SysTick_Delay(40);   
    //Display On Setting 

    LTK_LCD_WriteReg(LCD_REG_90H,0x007F); 
    LTK_LCD_WriteReg(LCD_REG_26H,0x0004); 

    LTK_SysTick_Delay(40);  

    LTK_LCD_WriteReg(LCD_REG_26H,0x0024); 
    LTK_LCD_WriteReg(LCD_REG_26H,0x002C); 

    LTK_SysTick_Delay(40);   
    LTK_LCD_WriteReg(LCD_REG_70H,0x0008); 
    LTK_LCD_WriteReg(LCD_REG_26H,0x003C);  
    LTK_LCD_WriteReg(LCD_REG_57H,0x0002); 
    LTK_LCD_WriteReg(LCD_REG_55H,0x0000); 
    LTK_LCD_WriteReg(LCD_REG_57H,0x0000);
 }


/**
  * @brief  initialize panel.
  * @param  None.
  * @retval None
  */
void LTK_LGD4535_Init(void)
{                 
    LTK_LCD_WriteReg(0X15,0X0030);   
    LTK_LCD_WriteReg(0X9A,0X0010);   
    LTK_LCD_WriteReg(0X11,0X0020);   
    LTK_LCD_WriteReg(0X10,0X3428);   
    LTK_LCD_WriteReg(0X12,0X0002);   
    LTK_LCD_WriteReg(0X13,0X1038);   
    LTK_SysTick_Delay(40);   
    LTK_LCD_WriteReg(0X12,0X0012);   
    LTK_SysTick_Delay(40);   
    LTK_LCD_WriteReg(0X10,0X3420);   
    LTK_LCD_WriteReg(0X13,0X3038);   
    LTK_SysTick_Delay(70);   
    LTK_LCD_WriteReg(0X30,0X0000);   
    LTK_LCD_WriteReg(0X31,0X0402);   
    LTK_LCD_WriteReg(0X32,0X0307);   
    LTK_LCD_WriteReg(0X33,0X0304);   
    LTK_LCD_WriteReg(0X34,0X0004);   
    LTK_LCD_WriteReg(0X35,0X0401);   
    LTK_LCD_WriteReg(0X36,0X0707);   
    LTK_LCD_WriteReg(0X37,0X0305);   
    LTK_LCD_WriteReg(0X38,0X0610);   
    LTK_LCD_WriteReg(0X39,0X0610); 
      
    LTK_LCD_WriteReg(0X01,0X0100);   
    LTK_LCD_WriteReg(0X02,0X0300);   
    LTK_LCD_WriteReg(0X03,0X1030);  
    LTK_LCD_WriteReg(0X08,0X0808);   
    LTK_LCD_WriteReg(0X0A,0X0008);   
    LTK_LCD_WriteReg(0X60,0X2700);   
    LTK_LCD_WriteReg(0X61,0X0001);   
    LTK_LCD_WriteReg(0X90,0X013E);   
    LTK_LCD_WriteReg(0X92,0X0100);   
    LTK_LCD_WriteReg(0X93,0X0100);   
    LTK_LCD_WriteReg(0XA0,0X3000);   
    LTK_LCD_WriteReg(0XA3,0X0010);   
    LTK_LCD_WriteReg(0X07,0X0001);   
    LTK_LCD_WriteReg(0X07,0X0021);   
    LTK_LCD_WriteReg(0X07,0X0023);   
    LTK_LCD_WriteReg(0X07,0X0033);   
    LTK_LCD_WriteReg(0X07,0X0133);   
}

/**
  * @brief  initialize panel.
  * @param  None.
  * @retval None
  */
void LTK_SPFD5408_Init()
{
    LTK_LCD_WriteReg(LCD_REG_01H,0x0100);                                
    LTK_LCD_WriteReg(LCD_REG_02H,0x0700); //LCD Driving Waveform Contral 
    LTK_LCD_WriteReg(LCD_REG_03H,0x1030); //Entry Mode setting    
    LTK_LCD_WriteReg(LCD_REG_04H,0x0000); //Scalling Control register     
    LTK_LCD_WriteReg(LCD_REG_08H,0x0207); //Display Control 2 
    LTK_LCD_WriteReg(LCD_REG_09H,0x0000); //Display Control 3   
    LTK_LCD_WriteReg(LCD_REG_0AH,0x0000); //Frame Cycle Control     
    LTK_LCD_WriteReg(LCD_REG_0CH,0x0000); //External Display Interface Control 1 
    LTK_LCD_WriteReg(LCD_REG_0DH,0x0000); //Frame Maker Position        
    LTK_LCD_WriteReg(LCD_REG_0FH,0x0000); //External Display Interface Control 2 
    LTK_SysTick_Delay(20);
    LTK_LCD_WriteReg(LCD_REG_10H,0x16B0); //0x14B0 //Power Control 1
    LTK_LCD_WriteReg(LCD_REG_11H,0x0001); //0x0007 //Power Control 2
    LTK_LCD_WriteReg(LCD_REG_17H,0x0001); //0x0000 //Power Control 3
    LTK_LCD_WriteReg(LCD_REG_12H,0x0138); //0x013B //Power Control 4
    LTK_LCD_WriteReg(LCD_REG_13H,0x0800); //0x0800 //Power Control 5
    LTK_LCD_WriteReg(LCD_REG_29H,0x0009); //NVM read data 2
    LTK_LCD_WriteReg(LCD_REG_2AH,0x0009); //NVM read data 3
    LTK_LCD_WriteReg(LCD_REG_A4H,0x0000);   
    LTK_LCD_WriteReg(LCD_REG_50H,0x0000); //Horizontal GRAM Start Address
    LTK_LCD_WriteReg(LCD_REG_51H,0x00EF); //Horizontal GRAM End Address
    LTK_LCD_WriteReg(LCD_REG_52H,0x0000); //Vertical GRAM Start Address
    LTK_LCD_WriteReg(LCD_REG_53H,0x013F); //Vertical GRAM End Address
    LTK_LCD_WriteReg(LCD_REG_60H,0x2700); //Driver Output Control
    LTK_LCD_WriteReg(LCD_REG_61H,0x0001); //Driver Output Control
    LTK_LCD_WriteReg(LCD_REG_6AH,0x0000); //Vertical Scroll Control
    LTK_LCD_WriteReg(LCD_REG_80H,0x0000); //Display Position 每 Partial Display 1
    LTK_LCD_WriteReg(LCD_REG_81H,0x0000); //RAM Address Start 每 Partial Display 1
    LTK_LCD_WriteReg(LCD_REG_82H,0x0000); //RAM address End - Partial Display 1
    LTK_LCD_WriteReg(LCD_REG_83H,0x0000); //Display Position 每 Partial Display 2
    LTK_LCD_WriteReg(LCD_REG_84H,0x0000); //RAM Address Start 每 Partial Display 2
    LTK_LCD_WriteReg(LCD_REG_85H,0x0000); //RAM address End 每 Partail Display2
    LTK_LCD_WriteReg(LCD_REG_90H,0x0013); //Frame Cycle Control
    LTK_LCD_WriteReg(LCD_REG_92H,0x0000); //Panel Interface Control 2
    LTK_LCD_WriteReg(LCD_REG_93H,0x0003); //Panel Interface control 3
    LTK_LCD_WriteReg(LCD_REG_95H,0x0110); //Frame Cycle Control
    LTK_LCD_WriteReg(LCD_REG_07H,0x0173);       
    LTK_SysTick_Delay(50);
}

/**
  * @brief  Get the ID of the LCD controller.
  * @param  None
  * @retval The ID of the LCD controller
  */
uint16_t LTK_LCD_ID_Check()
{
    uint16_t DeviceCode = 0xFFFF;
    LTK_SysTick_Delay(100); /* delay 100 ms */
    DeviceCode = LTK_LCD_ReadReg(LCD_REG_00H); 
    if((DeviceCode != 0x9320) && (DeviceCode != 0x9325) && 
       (DeviceCode != 0x9328) && (DeviceCode != 0x5408))
    {
        LTK_SysTick_Delay(100); /* delay 100 ms */
        DeviceCode = LTK_LCD_ReadReg(LCD_REG_67H); 
    }
    return DeviceCode;
}

/**
  * @brief  Initialize LCD.
  * @param  None
  * @retval None
  */
void LTK_LCD_Init(void)
{
    uint16_t DeviceCode;
    LTK_LCD_Struct_Init();
    LTK_LCD_RCC_Init();
    LTK_LCD_GPIO_Init();
    DeviceCode = LTK_LCD_ID_Check(); 

    printf("LCD Device ID: 0x%X\n", DeviceCode);
    
    if(DeviceCode == 0x4531)
    {
        LTK_LCD_Param.LCD_Type = LCD_LGDP4531;
        LTK_LGDP4531_Init();
    }
    else if(DeviceCode == 0x9325 || DeviceCode == 0x9328)
    {
        LTK_LCD_Param.LCD_Type = LCD_ILI9325;
        LTK_ILI9325_Init();
    }
    else if(DeviceCode == 0x9320)
    {
        LTK_LCD_Param.LCD_Type = LCD_ILI9320;
        LTK_ILI9320_Init();
    }
    else if(DeviceCode == 0x5408)
    {
        LTK_LCD_Param.LCD_Type = LCD_SPFD5408;
        LTK_SPFD5408_Init();
    }
    else if(DeviceCode == 0x4535)
    {
        LTK_LCD_Param.LCD_Type = LCD_LGDP4535;
        LTK_LGD4535_Init();
    }
    else if(DeviceCode == 0x47)
    {
        LTK_LCD_Param.LCD_Type = LCD_HX8347A;
        LTK_HX8347A_Init();
    }
    
    LTK_LCD_BackLightSwitch(LCD_BACKLIGHT_OFF);
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
