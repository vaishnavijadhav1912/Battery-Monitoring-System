/*
 * ads1115.h
 *
 *  Created on: Dec 2, 2024
 *      Author: Vaishnavi jadhav
 */

#include "main.h"
#ifndef INC_ADS1115_H_
#define INC_ADS1115_H_

#define ADS1115_ADDRESS 0x48 // I2C Address of ADS1115
void I2C_Init(void); //I2c Initialization
void I2C_Start(void); //I2c Start Condition
void I2C_Stop(void); //I2c Stop Condition
int I2C1_WriteBytes(uint8_t slave_addr, uint8_t *data, uint8_t length);
void I2C1_BurstRead(uint8_t saddr, uint8_t maddr,int n, uint8_t *data);
void Set_Channel_Config(uint8_t channel);
void delay_ms(uint32_t ms);


#endif /* INC_ADS1115_H_ */
