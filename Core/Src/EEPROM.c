/*
 * EEPROM.c
 *
 *  Created on: Dec 1, 2024
 *      Author: Vaishnavi Jadhav
 */
#include "EEPROM.h"

// I2C Initialization
/**
  * @brief I2c2 Initialization Function
  * @param None
  * @retval None
  * @Source : for this I2C initialization I had discussed with  Darshan
  */
void I2C2_Init(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; // Enable GPIOB clock
    RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;  // Enable I2C2 clock

    // Configure PB10 (SCL) and PB9 (SDA)
    GPIOB->MODER &= ~((3U << (2 * I2C_SCL_PIN)) | (3U << (2 * I2C_SDA_PIN)));
    GPIOB->MODER |= (2U << (2 * I2C_SCL_PIN)) | (2U << (2 * I2C_SDA_PIN)); // Alternate function
    GPIOB->OTYPER |= (1U << I2C_SCL_PIN) | (1U << I2C_SDA_PIN);            // Open-drain
    GPIOB->OSPEEDR |= (3U << (2 * I2C_SCL_PIN)) | (3U << (2 * I2C_SDA_PIN)); // High speed
    //GPIOB->PUPDR |= (1U << (2 * I2C_SCL_PIN)) | (1U << (2 * I2C_SDA_PIN)); // Pull-up
    GPIOB->AFR[1] |= (4U << (4 * 2)) | (9U << (4 * 1)); // I2C2 AF4

    I2C2->CR1 |= I2C_CR1_SWRST;   //RESET MODE

    I2C2->CR1 &=~I2C_CR1_SWRST;   //COME OUT OF RESET MODE

    // Configure I2C2
    I2C2->CR1 &= ~I2C_CR1_PE;                     // Disable I2C2
    I2C2->CR2 |= I2C_CR2_FREQ_4;             // APB1 clock frequency in MHz
    I2C2->CCR = APB1_CLOCK / (2 * I2C_SPEED);     // Clock control
    I2C2->TRISE = (APB1_CLOCK / 1000000) + 1;     // Maximum rise time
    I2C2->CR1 |= I2C_CR1_PE;                      // Enable I2C2


}

// I2C Start Condition
/**
  * @brief I2c2 Start Function
  * @param None
  * @retval None
  *
  */
void I2C2_Start(void) {
    I2C2->CR1 |= I2C_CR1_START; // Generate START condition
    while (!(I2C2->SR1 & I2C_SR1_SB)); // Wait for START bit
    (void)I2C2->SR1; // Clear the flag
}

// I2C Stop Condition
/**
  * @brief I2c2 Stop Function
  * @param None
  * @retval None
  *
  */
void I2C2_Stop(void) {
    I2C2->CR1 |= I2C_CR1_STOP; // Generate STOP condition
}




/**
  * @brief I2c2 byte read Function
  * @param slave address, memory address ,data
  * @retval None
  *
  */
void I2C2_byteRead(uint8_t saddr, uint8_t maddr, uint8_t *data)
{
	volatile int temp;
	/*wait unitl bus in not busy */
	while(I2C2->SR2 &(I2C_SR2_BUSY)){}
	I2C2_Start();
	I2C2->DR = saddr<<1;

	while (!(I2C2->SR1 & I2C_SR1_ADDR)){};
	temp = I2C2->SR2;

	I2C2->DR = maddr;
	 while (!(I2C2->SR1 & I2C_SR1_TXE)){}; // Wait until TXE is set
	 //GENERATE A START CONDITION
	 I2C2_Start();
	 I2C2->DR = saddr<<1|1;

	 while (!(I2C2->SR1 & I2C_SR1_ADDR)){};
	 I2C2->CR1 &=~I2C_CR1_ACK;
	 	temp = I2C2->SR2;
	 	//GENERATE STOP AFTER DATA IS RECEIVED
	 	I2C2_Stop();
	 	//WAIT UNTIL RXNE FLAG IS SET
	 	while (!(I2C2->SR1 & I2C_SR1_RXNE)){};

	 	/*READ DATA IN DR*/
	 	*data++=I2C2->DR;





}
/**
  * @brief I2c2 BURST READ( TO REAd specified number of bytes)
  * @param SLAVE ADDRESS, DATA POINTER, memory address
  * @retval none
  * @Source :
  */
void I2C2_BurstRead(uint8_t saddr, uint8_t maddr,int n, uint8_t *data)
{
	volatile int temp;
	/*wait unitl bus in not busy */
		while(I2C2->SR2 &(I2C_SR2_BUSY)){}
		I2C2_Start();

		I2C2->DR = saddr<<1;

		while (!(I2C2->SR1 & I2C_SR1_ADDR)){};
		temp = I2C2->SR2;

		 while (!(I2C2->SR1 & I2C_SR1_TXE)){}; // Wait until TXE is set

		I2C2->DR = maddr;
		 while (!(I2C2->SR1 & I2C_SR1_TXE)){}; // Wait until TXE is set
		 //GENERATE A START CONDITION
		 	 I2C2_Start();

		 I2C2->DR = saddr<<1|1;
         while (!(I2C2->SR1 & I2C_SR1_ADDR)){};
         temp = I2C2->SR2;
         I2C2->CR1 |=I2C_CR1_ACK;

         while(n>0U)
         {
        	 if(n==1U)
        	 {
        		 I2C2->CR1 &=~I2C_CR1_ACK;
        		 I2C2_Stop();
				//WAIT UNTIL RXNE FLAG IS SET
				while (!(I2C2->SR1 & I2C_SR1_RXNE)){};
				/*READ DATA IN DR*/
				*data++=I2C2->DR;
				break;

        	 }
        	 else
        	 {
        		 while (!(I2C2->SR1 & I2C_SR1_RXNE)){}; // Wait until TXE is set

        		(*data++) =I2C2->DR;
        		n--;
        	 }
         }



}
/**
  * @brief I2c2 BURST Write( TO write specified number of bytes)
  * @param SLAVE ADDRESS, DATA POINTER, memory address
  * @retval none
  * @Source :
  */
void I2C2_BurstWrite(uint8_t saddr, uint8_t maddr,int n, uint8_t *data)
{
	volatile int temp;
		/*wait unitl bus in not busy */
			while(I2C2->SR2 &(I2C_SR2_BUSY)){}
			I2C2_Start();
			I2C2->DR = saddr<<1;

			while (!(I2C2->SR1 & I2C_SR1_ADDR)){};
			temp = I2C2->SR2;

			 while (!(I2C2->SR1 & I2C_SR1_TXE)){}; // Wait until TXE is set

			I2C2->DR = maddr;
			for( int i=0;i<n;i++)
			{
				 while (!(I2C2->SR1 & I2C_SR1_TXE)){}; // Wait until TXE is set
				 I2C2->DR = *data++;
			}
			while (!(I2C2->SR1 & I2C_SR1_BTF)){}; // Wait until btf is set
			I2C2_Stop();





}

