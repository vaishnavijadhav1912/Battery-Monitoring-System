/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/*
 * Authors Darshan Salian,Vaishnavi Jadhav
 *
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

RTC_HandleTypeDef hrtc;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}

uint16_t current_data=0;
/*********ADS1115***************/
int millivolts =0;


uint8_t Data_to_write[16]= {0};
uint8_t Data_to_read[16]= {0};


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



 RTC_TimeTypeDef sTime = {0};
 RTC_DateTypeDef sDate = {0};
 RTC_DateTypeDef getDate = {0};
 RTC_TimeTypeDef getTime = {0};
 uint16_t  ADC_VAL[5] = {0};


 float Voltage_mV[4] = {0};
 float Temperature_C[4] = {0};
 float Temperature_F[4] = {0};
 uint16_t adc_value_channel[16]={0};
 uint8_t  adc_value_channel_EEPROM[16] = {0};
 float raw_voltage=0;
 float output_current=0;




/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_RTC_Init();
  MX_ADC1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  I2C_Init();

  I2C2_Init();

  SetTime();  //Set Time For RTC

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  printf("E\r\n");

	  GetTime();
	  for (uint8_t channel = 0; channel < 4; channel++) {
		  // Configure the ADC for the current channel
		  Set_Channel_Config(channel);

		  // Wait for conversion (adjust based on ADS1115's data rate)
		  delay_ms(10);

		  // Read the ADC value from the conversion register
		  uint8_t data[2] = {0};
		  I2C1_BurstRead(ADS1115_ADDRESS, 0x00, 2, data);
		  adc_value_channel[channel] = (data[0] << 8) | data[1];

		  // Convert ADC value to millivolts
		   int millivolts = adc_value_channel[channel] * 6.144 * 1000 / 32768.0;
		   adc_value_channel[channel]=millivolts;

		  // Print channel information and ADC value
//		  printf("Channel %d: ADC Value = %u, Millivolts = %d\r\n", channel, adc_value, millivolts);

		  // Add a delay before the next conversion
		  delay_ms(100);

	  }
	  //printf("%dA%dB%dC%dD",adc_value_channel[0],adc_value_channel[1],adc_value_channel[2],adc_value_channel[3]);

	  GetTempData();


		  current_data=0;
		  for(int p=0;p<10;p++)
		  {
			  GetCurrentData();
		  }
		  current_data=current_data/10;
		  raw_voltage = (float)current_data * 3.0/4096;
		  output_current  = (2.43-raw_voltage)/0.1;
		  if(output_current<0)
		  {
			  output_current=output_current*(-1);
		  }
		  adc_value_channel[8]= (output_current*1000)-50;


		  Data_to_write[0]=adc_value_channel[0]/100;  //voltage of A0
		  Data_to_write[1]=adc_value_channel[1]/100;  //voltage of A1
		  Data_to_write[2]=adc_value_channel[2]/100;  //voltage of A2
		  Data_to_write[3]=adc_value_channel[3]/100;  //voltage of A3
		  Data_to_write[4]=(uint8_t)adc_value_channel[4];  //Temp1
		  Data_to_write[5]=(uint8_t)adc_value_channel[5];  //Temp2
		  Data_to_write[6]=(uint8_t)adc_value_channel[6];  //Temp3
		  Data_to_write[7]=(uint8_t)adc_value_channel[7];  //Temp4
		  Data_to_write[8]=(uint8_t)adc_value_channel[8];  //Load Current
		  Data_to_write[9]=(uint8_t)getTime.Hours;
		  Data_to_write[10]=(uint8_t)getTime.Minutes;
		  Data_to_write[11]=(uint8_t)getTime.Seconds;
		  Data_to_write[12]=(uint8_t)getDate.Date;
		  Data_to_write[13]=(uint8_t)getDate.Month;
		  Data_to_write[14]=(uint8_t)getDate.Year;




		     I2C2_BurstWrite(EEPROM_I2C_ADDRESS, 0x00,16, Data_to_write);
		     HAL_Delay(50);//
		     I2C2_BurstRead(EEPROM_I2C_ADDRESS, 0x00,16, Data_to_read);

		     HAL_Delay(500);


		     printf("%dA%dB%dC%dD%dF%dG%dH%dI%dJ",adc_value_channel[0],adc_value_channel[1],adc_value_channel[2],adc_value_channel[3],adc_value_channel[4],adc_value_channel[5],adc_value_channel[6],adc_value_channel[7],adc_value_channel[8]);







  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}





/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LD4_Pin LD3_Pin LD5_Pin LD6_Pin */
  GPIO_InitStruct.Pin = LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
