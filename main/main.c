#include "stdlib.h"

#include "Buttons.h"

/**
* @breif This function sets the location of a character to a designated x and y coordinate
* @params 
*	struct Player *character -> Pointer to character to move
*	uint8_t x -> X coordinate of character on LCD			
* uint8_t y -> Y coordinate of character on LCD
*/
void resetCharacter(struct Player *character,uint8_t x,uint8_t y);

int main(void)
{
	SysTick_Delay_Init();
	LCD_Init();
	Button_init();
	
	//Set default values and initilizes enemies==========================
	struct Player enemy0;
	struct Player enemy1;
	
	struct Player enemy3;
	struct Player enemy4;
	
	int score = 0;

	uint32_t refresh_rate = 500000;
	
	//=====================================================================
	
	
	
	 
	
	//Creates pointers to enemies and sets initial positions of the characters===================================================
	struct Player *enemy_ptr0 = &enemy0;
	struct Player *enemy_ptr1 = &enemy1;
	struct Player *enemy_ptr3 = &enemy3;
	struct Player *enemy_ptr4 = &enemy4;
	
	resetCharacter(player_ptr,7,1);
	resetCharacter(enemy_ptr0,15,1);	
	resetCharacter(enemy_ptr1,0,0);	
	
	resetCharacter(enemy_ptr3,15,0);	
	resetCharacter(enemy_ptr4,0,1);	
	//====================================================================================================

	
	
	struct Player *chars_On_Screen[8];//Array that stores characters on Screen
	
	//Set Characters in array===================
	chars_On_Screen[0] =player_ptr; //POINTER TO PLAYER MUST ALWAYS BE 1ST ELEMENT
	chars_On_Screen[1] =enemy_ptr0;
	chars_On_Screen[2] =enemy_ptr1;
	
	chars_On_Screen[3] =enemy_ptr3;
	chars_On_Screen[4] =enemy_ptr4;
	//=================================
	
	uint8_t status; // Initialization of the button status 
	

		
	while(1)
	{
		
		//Reads status of push buttons to move player or restart game======
		status = Get_Button_Status();
		Button_Controller(status,player_ptr);
		//==================================================================
		
		if(game_state == ACTIVE)
		{
		
		//Updates Enemy Location Randomly 
			for(int i = 1;i < 5;i++)
			{
			Enemy_move(chars_On_Screen[i]);
			}
		//==============================
		
		//Refreshes the LCD ,speeds up game, and updates character locations on Screen=====
		LCD_Refresh(chars_On_Screen,refresh_rate);
		refresh_rate -= 1000;
		score++;
		//=================================================================
		
		
		}
		//Reset all Default Values========================
		else if (game_state == RESTART)
		{
			
			
		resetCharacter(player_ptr,7,1);
		resetCharacter(enemy_ptr0,15,1);	
		resetCharacter(enemy_ptr1,0,0);	
	
		resetCharacter(enemy_ptr3,15,0);	
		resetCharacter(enemy_ptr4,0,1);	
		if(score != 0) //Assures score is only printed once
		{
		LCD_Print_Score(score);
		}
		
		score = 0;
			
		refresh_rate = 500000;
		
			
		}
		//==================================================
		
		
		
		
	
		
		
		
	}
	
	
	return 0;
}


void resetCharacter(struct Player *character,uint8_t x,uint8_t y)
{
	character->x_cord = x;
	character->y_cord = y;
	
}
