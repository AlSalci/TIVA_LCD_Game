#include "Buttons.h"


void Button_init(void)
{
	// Enable Clock to Port D
	SYSCTL->RCGCGPIO |= 0x08;
	
	// Set PD0, PD1, PD2, and PD3 as input GPIO pins
	GPIOD->DIR &= ~0x0F;
	
	// Configure PD0, PD1, PD2, and PD3 to function as GPIO pins
	GPIOD->AFSEL &= ~0x0F;
	
	// Enable Digital Functionality for PD0, PD1, PD2, and PD3
	GPIOD->DEN |= 0x0F;
	
}

uint8_t Get_Button_Status(void)
{
	uint8_t button_status = GPIOD->DATA & 0xF;
	return button_status;
	
}



void Button_Controller(uint8_t button_status,struct Player *ptr)
{
	
	switch(button_status)	
	{
		// No buttons are pressed
		case 0x00:
		{
			
		}
		break;
		
		//SW3 Pressed
		case 0x04:
		{
			
			Player_Move_Line(ptr);
			
				
			
		}
		
		
		break;
		
		// SW5 is pressed
		case 0x01:
		{
			
		
			Player_Move_Forward(ptr);
			
		}
		break;
		//SW2 is pressed 
		case 0x08:
		{
			
		
			Player_Move_Back(ptr);
			
		}
		break;
		//SW4 Pressed 
		case 0x02:
			game_state = ACTIVE;
		
		break;
		
		default:
		{
		
		}
	
	
  }
}

