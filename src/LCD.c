

#include "LCD.h"

static uint8_t display_control = 0x00;
static uint8_t display_mode =0x00;
static char game_over_message[] = {'G','A','M','E',' ','O','V','E','R','\0'};
static char Score_messgae[] = {'S','C','O','R','E',':','\0'};
enum GAME_STATE game_state = ACTIVE;

void LCD_Port_Init(void)
{
	
			SYSCTL->RCGCGPIO |= 0x01;
			GPIOA ->DIR |= 0x3C;	
			GPIOA ->AFSEL &= ~0x3C;
			GPIOA -> DEN |= 0x3C;
			GPIOA ->DATA  &= ~0x3C;
	
			SYSCTL -> RCGCGPIO |= 0x04;
		  GPIOC ->DIR |= 0x40;
			GPIOC -> AFSEL &= ~0x40;
			GPIOC->DEN |= 0x40;
			GPIOC->DATA &= ~0x40;
	  
			SYSCTL->RCGCGPIO |= 0x10;
			GPIOE ->DIR |= 0x01;
			GPIOE->AFSEL &= ~0x01;
			GPIOE->DEN |= 0x01;
			GPIOE->DATA &= ~0x01;
}

void LCD_Write_Data_4_Bit(uint8_t data, uint8_t control_flag)
{
		
	GPIOA->DATA |= (data & 0xF0) >> 0x2;
	if (control_flag & 0x01)
	{
		GPIOE->DATA |= 0x01;
	}	
	else
	{
		GPIOE->DATA &= ~0x01;
	}
	LCD_Enabled();
	GPIOA->DATA &= ~0x3C;
	SysTick_Delay1us(1000);
	
}


void LCD_Enabled(void)
{
	
	GPIOC->DATA &= ~0x40;
	SysTick_Delay1us(1);
	
	
	GPIOC->DATA |= 0x40;
	SysTick_Delay1us(1);
	GPIOC->DATA &= ~0x40;
	
}

void LCD_Send_Commands(uint8_t command)
{
	//Send First Nibble====================
	LCD_Write_Data_4_Bit(command & 0xF0, COMMAND);
	//=====================================
	
	
	//Send Second Nibble======================
	LCD_Write_Data_4_Bit(command << 4, COMMAND);
	//========================================
	
	//Wait time for Commands========================
	if(command < 3)
	{
	SysTick_Delay1us(1520);
	}
	else 
	{
		SysTick_Delay1us(37);
	}
	//==============================================
}

void LCD_Send_Full_Data(uint8_t data)
{
	//Send First Nibble====================
	LCD_Write_Data_4_Bit(data & 0xF0, CHARACTER);
	//=====================================
	
	//Send Second Nibble======================
	LCD_Write_Data_4_Bit(data << 4, CHARACTER);
	//========================================
}


void LCD_Init(void)
{
		//Enable LCD Pins
		LCD_Port_Init();
	
	//Waits for 50ms after LCD is powered On
	SysTick_Delay1us(50000);
	
	//LCD initialization Sequence=======================
	LCD_Write_Data_4_Bit(FUNSET | BIT_8_MODE,COMMAND);
	SysTick_Delay1us(4500);
	
	LCD_Write_Data_4_Bit(FUNSET | BIT_8_MODE,COMMAND);
	SysTick_Delay1us(4500);
	
	LCD_Write_Data_4_Bit(FUNSET | BIT_8_MODE,COMMAND);
	SysTick_Delay1us(150);
	//==================================================
	
	LCD_Write_Data_4_Bit(FUNSET | BIT_4_MODE, COMMAND);
	
	LCD_Send_Commands(FUNSET | CONFIG_5X8 | TWO_LINES);
	
	LCD_Enable_Display();
	
	LCD_Home();
	
	LCD_Clear();
	
	//Creates and stores the Player Character
	LCD_Create_Custom_Char(PLAYER_ADDR,Custom_Player_Char);
	
	//Creates and stores the Enemy Characyer
	LCD_Create_Custom_Char(ENEMY_ADDR,Custom_Enemy_Char);
	LCD_Cursor(0,0);
}

void LCD_Enable_Display(void)
{
	display_control |= DISPLAY_ON;
	LCD_Send_Commands(DISPLAY | display_control);
}

void LCD_Clear(void)
{
	LCD_Send_Commands(CLEAR);
}


void LCD_Cursor(uint8_t col,uint8_t row)
{
		if(row == 0)
		{
			LCD_Send_Commands(SET_DDRAM | col);
			
		} else 
		{
			LCD_Send_Commands(SET_DDRAM | (col+0x40));
			
		}
		
		
}
	

void LCD_Home(void)
{

LCD_Send_Commands(RETURN);	
	
}


void LCD_Create_Custom_Char(uint8_t loc, uint8_t char_buffer[])
{
	loc &= 0x7;
	LCD_Send_Commands(SET_CGRAM | (loc << 3));
	for (int i = 0; i < 8; i++)
	{
		LCD_Send_Full_Data(char_buffer[i]);
	}
	
	
}

void LCD_Print_Player(struct Player *player,int isPlayer)
{
	
	LCD_Cursor(player->x_cord,player->y_cord);
	
	if(isPlayer == 1)
	{
	LCD_Send_Full_Data(PLAYER_ADDR);
	}
	else 
	{
	LCD_Send_Full_Data(ENEMY_ADDR);
	}
	
}

void LCD_Refresh(struct Player *(char_array[8]),uint32_t rate)
{
	LCD_Clear();
	
	LCD_Print_Player(char_array[0],1);
	
	for(int i = 1; i < 5;i++)
	{
	LCD_Print_Player(char_array[i],0);
	
	}
	for(int i = 1; i < 5;i++)
	{
	if(char_array[0]->x_cord == char_array[i]->x_cord && char_array[0]->y_cord == char_array[i]->y_cord)
	{
		
		LCD_Clear();
		LCD_Print_Stirng(game_over_message,0,0);
		game_state = RESTART;
		return;
	}
}
	
	SysTick_Delay1us(rate);
	
}

void LCD_Print_Stirng(char *string,uint8_t col,uint8_t line)
{
	LCD_Cursor(col,line);
	for(unsigned int i = 0; i<strlen(string); i++)
	{
		LCD_Send_Full_Data(string[i]);
		
	}
	
}



void LCD_Print_Score(int score)
{
	char int_buffer[32];
	sprintf(int_buffer, "%d", score);
	LCD_Print_Stirng(Score_messgae,0,1);
	LCD_Print_Stirng(int_buffer,7,1);
	
}
	




