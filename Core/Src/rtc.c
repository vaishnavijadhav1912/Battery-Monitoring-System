/*
 * rtc.c
 *
 *  Created on: Dec 4, 2024
 *      Author: Vaishnavi Jadhav
 */

#include "rtc.h"

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  * @source : Hal Functions are Used
  */
void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK) //Hal Functions are Used
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}
/**
  * @brief time is set in this Function
  * @param None
  * @retval None
  * @source : Hal Functions are Used
  */
void SetTime(void)
{

	sTime.Hours = 17;
   sTime.Minutes = 14;
   sTime.Seconds = 0;
   if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
   {
	 Error_Handler();
   }
   sDate.WeekDay = RTC_WEEKDAY_MONDAY;
   sDate.Month = RTC_MONTH_DECEMBER;
   sDate.Date = 9;
   sDate.Year = 24;
   if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
   {
	 Error_Handler();
   }
}
/**
  * @brief get time in this Function
  * @param None
  * @retval None
  * @source : Hal Functions are Used
  */
void GetTime(void)
{
	 if (HAL_RTC_GetTime(&hrtc, &getTime, RTC_FORMAT_BIN) != HAL_OK)
	 {
	   Error_Handler();
	 }
	 if (HAL_RTC_GetDate(&hrtc, &getDate, RTC_FORMAT_BIN) != HAL_OK)
	 {
	   Error_Handler();
	 }

}

