/**
  ******************************************************************************
  * @file    SPI_FLASH_main.c 
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
#include "LTK_SPI_Flash.h"
#include "LTK_USART.h"
#include "LTK_LCD.h"
#include "LTK_SysTick.h"
#include "stdio.h"

/** @addtogroup LTK_Examples
  * @{
  */

/** @addtogroup LTK_SPI_FLASH
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program, SPI flash write/read example.
  * @param  None
  * @retval None
  */
int main(void)
{
    uint8_t  Tx_Buffer[] = "LTK SPI FLASH Example";
    uint8_t  Rx_Buffer[512] = "flash not present or not recognized\n";
    uint16_t BufferSize = sizeof(Tx_Buffer) / sizeof(*Tx_Buffer);
    uint32_t FlashAddr = 0x0;

    /* initialize SysTick for exact time delay */
    LTK_SysTick_Init();
    
    /* initialize UART */
    LTK_COM_Init();
    USART_Cmd(USART1, ENABLE);

    /* initialize SPI flash */
    LTK_SPI_Flash_Init();
    SPI_Cmd(SPI1, ENABLE);

    /* check if flash recognized */
    LTK_SPI_FLASH_ID_check();
    
    if (spi_flash_found)
    {
        /* Erase SPI FLASH Sector to be written */
        LTK_FLASH_EraseSector(FlashAddr);
    
        /* Write data in Tx_Buffer to SPI FLASH memory */
        LTK_FLASH_WriteBuffer(Tx_Buffer, FlashAddr, BufferSize);
    
        /* Read data from SPI FLASH memory */
        LTK_FLASH_ReadBuffer(Rx_Buffer, FlashAddr, BufferSize);
    }

    while (1)
    {        
        printf("Tx: %s\n", Tx_Buffer);
        printf("Rx: %s\n", Rx_Buffer);
        
        /* delay one second */
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
