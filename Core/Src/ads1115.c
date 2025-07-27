/*
 * ads1115.c
 *
 *  Created on: Dec 2, 2024
 *      Author: Vaishnavi jadhav
 */


#include "ads1115.h"

// I2C Initialization
/**
  * @brief I2c Initialization Function
  * @param None
  * @retval None
  * @Source :
  */
void I2C_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    //PB6(SCL) AND PB7(SDA)
    GPIOB->MODER &= ~((3UL << 2 * 6) | (3UL << 2 * 7));
    GPIOB->MODER |= (2UL << 2 * 6) | (2UL << 2 * 7);
    GPIOB->OTYPER |= (1UL << 6) | (1UL << 7);
    GPIOB->OSPEEDR |= (3UL << 2 * 6) | (3UL << 2 * 7);
    GPIOB->AFR[0] |= (4UL << (4 * 6)) | (4UL << (4 * 7));

    I2C1->CR1 &= ~I2C_CR1_PE;
    I2C1->CR2 = 42; // 42 MHz APB1 clock
    I2C1->CCR = 210; // 100kHz I2C speed
    I2C1->TRISE = 43; // Max rise time
    I2C1->CR1 |= I2C_CR1_PE;
}

// I2C Start Condition
/**
  * @brief I2c start Function
  * @param None
  * @retval None
  * @Source :
  */
void I2C_Start(void) {
    I2C1->CR1 |= I2C_CR1_START;
    while (!(I2C1->SR1 & I2C_SR1_SB));
    (void)I2C1->SR1;
}

// I2C Stop Condition
/**
  * @brief I2c2 STOP Function
  * @param None
  * @retval None
  * @Source :
  */
void I2C_Stop(void) {
    I2C1->CR1 |= I2C_CR1_STOP;
}


/**
  * @brief I2c2 WRITE byTES
  * @param SLAVE ADDRESS, DATA POINTER, LENGTH
  * @retval INTEGER
  * @Source :
  */
int I2C1_WriteBytes(uint8_t slave_addr, uint8_t *data, uint8_t length) {
    I2C_Start();
    I2C1->DR = (slave_addr << 1);
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    (void)I2C1->SR1;
    (void)I2C1->SR2;

    for (uint8_t i = 0; i < length; i++) {
        while (!(I2C1->SR1 & I2C_SR1_TXE));
        I2C1->DR = data[i];
    }

    while (!(I2C1->SR1 & I2C_SR1_BTF));
    I2C_Stop();

    return 0;
}

/**
  * @brief I2c BURST READ( TO REAd specified number of bytes)
  * @param SLAVE ADDRESS, DATA POINTER, memory address
  * @retval none
  * @Source :
  */
void I2C1_BurstRead(uint8_t saddr, uint8_t maddr,int n, uint8_t *data)
{
	volatile int temp;
	/*wait unitl bus in not busy */
		while(I2C1->SR2 &(I2C_SR2_BUSY)){}
		I2C_Start();

		I2C1->DR = saddr<<1;

		while (!(I2C1->SR1 & I2C_SR1_ADDR)){};
		temp = I2C1->SR2;

		 while (!(I2C1->SR1 & I2C_SR1_TXE)){}; // Wait until TXE is set

		I2C1->DR = maddr;
		 while (!(I2C1->SR1 & I2C_SR1_TXE)){}; // Wait until TXE is set
		 //GENERATE A START CONDITION
		 	 I2C_Start();

		 I2C1->DR = saddr<<1|1;
         while (!(I2C1->SR1 & I2C_SR1_ADDR)){};
         temp = I2C1->SR2;
         I2C1->CR1 |=I2C_CR1_ACK;

         while(n>0U)
         {
        	 if(n==1U)
        	 {
        		 I2C1->CR1 &=~I2C_CR1_ACK;
        		 I2C_Stop();
				//WAIT UNTIL RXNE FLAG IS SET
				while (!(I2C1->SR1 & I2C_SR1_RXNE)){};

				*data++=I2C1->DR;
				break;

        	 }
        	 else
        	 {
        		 while (!(I2C1->SR1 & I2C_SR1_RXNE)){}; // Wait until TXE is set

        		(*data++) =I2C1->DR;
        		n--;
        	 }
         }



}
/**
  * @brief This Function is used to select the channel of the ads1115 module for ADC conversion
  * @param channel Number
  * @retval none
  * @Source :
  */
void Set_Channel_Config(uint8_t channel) {
    uint8_t mux_bits;

    // Set MUX bits based on the channel
    switch (channel) {
        case 0: mux_bits = 0x40; break; // AIN0
        case 1: mux_bits = 0x50; break; // AIN1
        case 2: mux_bits = 0x60; break; // AIN2
        case 3: mux_bits = 0x70; break; // AIN3
        default: return; // Invalid channel
    }

    // Configure ADS1115 for the selected channel
    uint8_t config_data[] = {0x01, (mux_bits| 0x00), 0x83}; // Config for single-shot mode
    I2C1_WriteBytes(ADS1115_ADDRESS, config_data, 3);
}

/**
  * @brief This Function generates delay in ms
  * @param ms
  * @retval none
  * @Source :
  */
void delay_ms(uint32_t ms) {
    volatile uint32_t count = ms * 16000; // Adjust for clock speed (16 MHz assumed)
    while (count--) {
        __asm__ volatile ("nop");
    }
}



