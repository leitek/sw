/**
  ******************************************************************************
  * @file    SD_main.c 
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
#include "LTK_SD.h"
#include "LTK_USART.h"
#include "LTK_SysTick.h"
#include "LTK_SPI_Flash.h"
#include "LTK_TouchScreen.h"
#include "LTK_RCC.h"
#include <stdio.h>

/** @addtogroup LTK_Examples
  * @{
  */

/** @addtogroup LTK_SD
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program, SD card SPI interface read example.
  * @param  None
  * @retval None
  */
int main(void)
{
    uint16_t i;
    uint8_t resp;
    uint8_t sd_response[5];
    uint8_t RxData[512];
    SD_Card_Type SD_CT = SD_Unknown;
    LTK_SysTick_Init();
    LTK_COM_Init();
    USART_Cmd(USART1, ENABLE);
    
    LTK_SD_SPI_Init();
    
    SPI_Cmd(SPI1, ENABLE); /*!< SD_SPI enable */
    
    LTK_DMA1_RCC_Init();
    
    for (i = 0; i < 3; i++)
    {
        SD_CT = LTK_SD_SPI_Start();
        if (SD_CT != SD_Unknown)
            break;
    }
    
    if(SD_CT == SD_Unknown)
    {
        printf("Unknown SD card or SD card not present\n");
    }
    else
    {
        printf("SD card type: 0x%X\n", (int)SD_CT);
    }
    
    while (1)
    {
        resp = LTK_sd_send_command(SD_CMD_READ_SINGLE_BLOCK, 0, R1, sd_response);
        if (resp == 0) /* READ_SINGLE_BLOCK */
        {
            resp = LTK_SD_SPI_ReadBlock(RxData, 512);
            if (resp) 
            {
                for(i = 0; i < 512; i++)
                    printf("0x%02X ", RxData[i]);
                printf("\n\n\n");
            }
            else
            {
                printf("Failed to read block\n"); 
            }
        }
        else
        {
                printf("Failed to send command\n"); 
        }
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
