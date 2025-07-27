/*
 * rtc.h
 *
 *  Created on: Dec 4, 2024
 *      Author: Vaishnavi Jadhav
 */
#include "main.h"
#ifndef INC_RTC_H_
#define INC_RTC_H_

extern RTC_HandleTypeDef hrtc;

extern RTC_TimeTypeDef sTime ;
extern RTC_DateTypeDef sDate ;
extern RTC_DateTypeDef getDate;
extern RTC_TimeTypeDef getTime;
 void MX_RTC_Init(void);
 void SetTime(void);
 void GetTime(void);


#endif /* INC_RTC_H_ */
