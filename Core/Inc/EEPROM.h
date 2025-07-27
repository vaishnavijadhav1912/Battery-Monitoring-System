/*
 * EEPROM.h
 *
 *  Created on: Dec 1, 2024
 *      Author: Vaishnavi Jadhav
 */

#include "main.h"
#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_

// I2C Pin Definitions
#define I2C_SCL_PIN 10  // PB10
#define I2C_SDA_PIN 9  // PB9

#define EEPROM_I2C_ADDRESS 0x50 // 7-bit address
#define I2C_SPEED 100000        // 100 kHz
#define APB1_CLOCK 16000000     // 42 MHz

/************EEPROM****************/
#define EEPROM_I2C_ADDRESS 0x50 // 7-bit address
void I2C2_Init(void);
void I2C2_Start(void);
void I2C2_Stop(void);
void I2C2_byteRead(uint8_t saddr, uint8_t maddr, uint8_t *data);
void I2C2_BurstRead(uint8_t saddr, uint8_t maddr,int n, uint8_t *data);
void I2C2_BurstWrite(uint8_t saddr, uint8_t maddr,int n, uint8_t *data);


#endif /* INC_EEPROM_H_ */
