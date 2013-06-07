/**
  ******************************************************************************
  * @file    ADC_main.c 
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
#include "stm32f10x_it.h"
#include "LTK_ADC.h"
#include "LTK_USART.h"
#include "LTK_SysTick.h"
#include "stdio.h"

/** @addtogroup LTK_Examples
  * @{
  */

/** @addtogroup LTK_ADC
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program, ADC sample example
  * @param  None
  * @retval None
  */
int main(void)
{
    LTK_SysTick_Init();
    LTK_ADC_Init();
    /* Enable ADC1 */
    ADC_Cmd(ADC1, ENABLE);

    /* Enable ADC1 reset calibaration register */   
    ADC_ResetCalibration(ADC1);
    /* Check the end of ADC1 reset calibration register */
    while(ADC_GetResetCalibrationStatus(ADC1));

    /* Start ADC1 calibaration */
    ADC_StartCalibration(ADC1);
    /* Check the end of ADC1 calibration */
    while(ADC_GetCalibrationStatus(ADC1));
     
    /* Start ADC1 Software Conversion */ 
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    LTK_COM_Init();
    USART_Cmd(USART1, ENABLE);

    while (1)
    {
        printf("0x%x\n", ADC1ConvertedValue);
        LTK_SysTick_Delay(500);
        
    }  
}

/**
  * @}
  */

/**
  * @}
  */

/****************************** leitek.taobao.com *****************************/
