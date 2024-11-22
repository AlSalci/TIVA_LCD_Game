#include "SystemDelays.h"



static uint32_t us_elapsed = 0;


void SysTick_Delay_Init(void)
{	

	SysTick->LOAD = (4 - 1);
	
	SysTick->CTRL |= 0x03;
}

void SysTick_Delay1us(uint32_t delay_in_us)
{
	

	us_elapsed = 0;
	
	while (delay_in_us > us_elapsed);
	
	
	
}

void SysTick_Handler(void)
{
	
us_elapsed++;
	
	
}
