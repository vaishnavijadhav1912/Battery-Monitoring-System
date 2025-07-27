/*
 * adc.h
 *
 *  Created on: Dec 4, 2024
 *      Author: Darshan Salian
 */
#include "main.h"
#ifndef INC_ADC_H_
#define INC_ADC_H_

extern ADC_HandleTypeDef hadc1;  //Hal Type
extern uint16_t  ADC_VAL[5] ;
extern float Voltage_mV[4];
extern float Temperature_C[4];
extern float Temperature_F[4];
extern uint16_t adc_value_channel[16];
extern uint8_t  adc_value_channel_EEPROM[16];
extern float raw_voltage;
extern float output_current;
extern uint16_t current_data;

void MX_ADC1_Init(void);
/*************ADC Channel****************/
void ADC_Select_CH10 (void);
void ADC_Select_CH11 (void);
void ADC_Select_CH12 (void);
void ADC_Select_CH13 (void);
void ADC_Select_CH14 (void);

/************Data*********************/
void GetTempData(void);
void GetCurrentData(void);


#endif /* INC_ADC_H_ */
