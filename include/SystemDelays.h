#include "TM4C123GH6PM.h"



/**
 * @brief Initializes device to cause interrupts to allow blocking functions to work
 * @param None
 * @return None
 */
void SysTick_Delay_Init(void);


/**
 * @brief Provides a blocking delay for the SysTick timer
 * @param uint32_t delay_in_us -> How long the device should wait for
 * @return None
 */
void SysTick_Delay1us(uint32_t delay_in_us);

/**
 * @brief Interrupt service routine for the SysTick inturrupt
 * @param None
 * @return None
 */
void SysTick_Handler(void);
