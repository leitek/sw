/**
  ******************************************************************************
  * @file    uCGUI_main.c 
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
#include "LTK_LED.h"
#include "LTK_TIM_PWM.h"
#include "LTK_RTC.h"
#include "LTK_EEPROM.h"
#include "LTK_I2C.h"
#include "LTK_SD.h"
#include "LTK_Device.h"
#include "LTK_LCD.h"
#include "LTK_USART.h"
#include "LTK_TouchScreen.h"
#include "LTK_SPI_Flash.h"
#include "LTK_Button_EXTI.h"
#include "FreeRTOS.h"
#include "task.h"
#include "GUIDEMO.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


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
  * @brief  Initialize take.
  */
void InitTask ( void *pvParameters )
{
    uint8_t TxBuffer[] = "LTK STM32, I2C example.";
    uint8_t RxBuffer[100] = "EEPROM not present\n";
    uint16_t Buffer_Size = sizeof(TxBuffer) / sizeof(*(TxBuffer));
    uint32_t cur_time, i;
    portBASE_TYPE task_error;
    SD_Card_Type SD_CT = SD_Unknown;
    
    LTK_Button_Init();
    LTK_LED_Init();

    LTK_COM_Init();
    USART_Cmd(USART1, ENABLE);
    
    LTK_TIM_PWM_Init();
    /* TIM2 enable counter */
    TIM_Cmd(TIM2, ENABLE);
    
    LTK_RTC_Init();

    LTK_I2C_Init();
    I2C_Cmd(I2C1, ENABLE);

    LTK_LED_Set(1, 0);
    printf("UART test OK\n");

    LTK_Get_SerialNum();

    cur_time = RTC_GetCounter();
    printf("time: 0X%X\n", cur_time);

    
    LTK_EEPROM_Write(TxBuffer, 0, Buffer_Size);
    
    LTK_EEPROM_Read(RxBuffer, 0, Buffer_Size);
    
    I2C_Cmd(I2C1, DISABLE);
    if (strcmp((char*)TxBuffer, (char*)RxBuffer) == 0)
        printf("EEPROM tested OK\n");
    else
    {
        printf("EEPROM test failed\n");
        while(1);
    }

    LTK_SD_SPI_Init();
        
    SPI_Cmd(SPI1, ENABLE); /*!< SD_SPI enable */

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
    SPI_Cmd(SPI1, DISABLE); /*!< SD_SPI enable */
    task_error = xTaskCreate(uCGUI, "uCGUI task", (1 * 1024), NULL, 8, NULL );
    assert( task_error == pdPASS);
    
    vTaskDelete(NULL);
}

/**
  * @brief  Main program, the touch screen example.
  * @param  None
  * @retval None
  */
int main(void)
{
    portBASE_TYPE task_error;
    task_error = xTaskCreate(InitTask, "Init task", (200), NULL, 5, NULL );
    
    assert( task_error == pdPASS);
    vTaskStartScheduler();
    assert(0);
}

/**
  * @}
  */

/**
  * @}
  */

/****************************** leitek.taobao.com *****************************/
