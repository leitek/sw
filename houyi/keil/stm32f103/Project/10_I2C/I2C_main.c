/**
  ******************************************************************************
  * @file    I2C_main.c 
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
#include "LTK_I2C.h"
#include "LTK_EEPROM.h"
#include "LTK_USART.h"
#include "LTK_SysTick.h"
#include <stdio.h>

/** @addtogroup LTK_Examples
  * @{
  */

/** @addtogroup LTK_USART
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program, write, read EEPROM example.
  * @param  None
  * @retval None
  */
int main(void)
{
    uint8_t TxBuffer[] = "LTK STM32, I2C example.";
    uint8_t RxBuffer[100] = "EEPROM not present\n";
    uint16_t Buffer_Size = sizeof(TxBuffer) / sizeof(*(TxBuffer));

    
    LTK_SysTick_Init();
    LTK_COM_Init();
    USART_Cmd(USART1, ENABLE);
    LTK_I2C_Init();
    I2C_Cmd(I2C1, ENABLE);
    
    LTK_EEPROM_Write(TxBuffer, 0, Buffer_Size);
    
    LTK_EEPROM_Read(RxBuffer, 0, Buffer_Size);
      
    while(1)
    {
        printf("TX: %s\n", TxBuffer);
        printf("RX: %s\n", RxBuffer);
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
