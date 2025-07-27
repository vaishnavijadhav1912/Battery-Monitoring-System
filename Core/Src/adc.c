/*
 * adc.c
 *
 *  Created on: Dec 4, 2024
 *      Author: Darshan Salian
 */

#include "adc.h"

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  * @Source : Hal_Fuctions are used in this code
  */
void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */



  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)  //Hal_Fuctions is used
  {
    Error_Handler();
  }


  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}
/**
  * @brief ADC1 channel 10  Function
  * @param None
  * @retval None
  * @Source : Hal_Fuctions are used in this code
  */
void ADC_Select_CH10 (void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	  */
	  sConfig.Channel = ADC_CHANNEL_10;
	  sConfig.Rank = 1;
	  sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)//Hal_Fuctions is used
	  {
	    Error_Handler();
	  }
}
/**
  * @brief ADC1 channel 11  Function
  * @param None
  * @retval None
  * @Source : Hal_Fuctions are used in this code
  */
void ADC_Select_CH11 (void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	  */
	  sConfig.Channel = ADC_CHANNEL_11;
	  sConfig.Rank = 1;
	  sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)//Hal_Fuctions is used
	  {
	    Error_Handler();
	  }
}
/**
  * @brief ADC1 channel 12  Function
  * @param None
  * @retval None
  * @Source : Hal_Fuctions are used in this code
  */
void ADC_Select_CH12 (void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	  */
	  sConfig.Channel = ADC_CHANNEL_12;
	  sConfig.Rank = 1;
	  sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)//Hal_Fuctions is used
	  {
	    Error_Handler();
	  }
}

/**
  * @brief ADC1 channel 13  Function
  * @param None
  * @retval None
  * @Source : Hal_Fuctions are used in this code
  */
void ADC_Select_CH13 (void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	  */
	  sConfig.Channel = ADC_CHANNEL_13;
	  sConfig.Rank = 1;
	  sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)//Hal_Fuctions is used
	  {
	    Error_Handler();
	  }
}

/**
  * @brief ADC1 channel 14  Function
  * @param None
  * @retval None
  * @Source : Hal_Fuctions are used in this code
  */
void ADC_Select_CH14 (void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	  */
	  sConfig.Channel = ADC_CHANNEL_14;
	  sConfig.Rank = 1;
	  sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)//Hal_Fuctions is used
	  {
	    Error_Handler();
	  }
}

void GetTempData(void)
{
	  ADC_Select_CH10();
	  HAL_ADC_Start(&hadc1); //Start ADC(Hal Function)
	  HAL_ADC_PollForConversion(&hadc1, 1000);//Start Conversion(HAL Function)
	  ADC_VAL[0] = HAL_ADC_GetValue(&hadc1); //Get value of ADC After End of COnversion(Hal Function)
	  HAL_ADC_Stop(&hadc1);
	  HAL_Delay(10);
	  // Calculate voltage and temperature
	   Voltage_mV[0] = (((ADC_VAL[0] * 3.0) / 4095.0) - 0.5) * 1000;
	   Temperature_C[0] = Voltage_mV[0] / 10;
	   adc_value_channel[4] =  Temperature_C[0] ;


	  ADC_Select_CH11();
	  HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1, 1000);
	  ADC_VAL[1] = HAL_ADC_GetValue(&hadc1);
	  HAL_ADC_Stop(&hadc1);
	  HAL_Delay(10);
	  Voltage_mV[1] = (((ADC_VAL[1] * 3.0) / 4095.0) - 0.5) * 1000;
	  Temperature_C[1] = Voltage_mV[1] / 10;
	  adc_value_channel[5] =  Temperature_C[1] ;



	  ADC_Select_CH12();
	  HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1, 1000);
	  ADC_VAL[2] = HAL_ADC_GetValue(&hadc1);
	  HAL_ADC_Stop(&hadc1);
	  HAL_Delay(10);
	  Voltage_mV[2] = (((ADC_VAL[2] * 3.0) / 4095.0) - 0.5) * 1000;
	  Temperature_C[2] = Voltage_mV[2] / 10;
	  adc_value_channel[6] =  Temperature_C[2] ;


	  ADC_Select_CH13();
	  HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1, 1000);
	  ADC_VAL[3] = HAL_ADC_GetValue(&hadc1);
	  HAL_ADC_Stop(&hadc1);
	  HAL_Delay(10);
	  Voltage_mV[3] = (((ADC_VAL[3] * 3.0) / 4095.0) - 0.5) * 1000;
	  Temperature_C[3] = Voltage_mV[3] / 10;
	  adc_value_channel[7] =  Temperature_C[3] ;
}
void GetCurrentData(void)
{
	  ADC_Select_CH14();
	  HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1, 1000);
	  ADC_VAL[4] = HAL_ADC_GetValue(&hadc1);
	  HAL_ADC_Stop(&hadc1);
	  current_data+=ADC_VAL[4];
	  HAL_Delay(10);
}
