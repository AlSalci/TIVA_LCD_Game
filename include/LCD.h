
#include "TM4C123GH6PM.h"
#include "SystemDelays.h"
#include "Player.h"
#include <string.h>
#include <stdio.h>
//Flags==========================================
#define CHARACTER 1
#define COMMAND 0

//==============================================
//LCD Commands===================================
#define CLEAR 0x01
#define RETURN 0x02
#define ENTRY 0x04
#define DISPLAY 0x08
#define CURSOR 0x10
#define FUNSET 0x20
#define SET_CGRAM 0x40
#define SET_DDRAM 0x80
//===============================================

//Controls===============================

	//Function Settings-------------------
	#define BIT_4_MODE 0x00
	#define BIT_8_MODE 0x10
	#define CONFIG_5X8 0x00
	#define CONFIG_5x10 0x04
	#define ONE_LINE 0x00
	#define TWO_LINES 0x08
	//------------------------
	
	//Display Controls------------------
		#define DISPLAY_ON 0x04
		#define DISPLAY_OFF 0x00
	
	//----------------------------------
	
	//Character Memory Addresses----------------
	#define PLAYER_ADDR 0x00
	#define ENEMY_ADDR 0x01
	//------------------------------------------
	

//===============================================
enum GAME_STATE
{
	ACTIVE,
	RESTART
	
};

extern enum GAME_STATE game_state;


static uint8_t Custom_Player_Char[8] =
{
	 0x00, 
  0x0E,  
  0x0E,
  0x0E,
  0x04,
  0x1F,
  0x04,
  0x0A
	
		
};

static uint8_t Custom_Enemy_Char[8] =
{
	 0x00,
  0x00,
  0x00,
  0x06,
  0x0F,
  0x1F,
  0x09,
  0x00
	
		
};

/**
 * @brief Initilizes the GPIO pins to Interface with the LCD
 * @param None
 * @return None
 */
void LCD_Port_Init(void);

/**
*@brief Sends 8 bit data to LCD by splitting it into 2 4-bit nibbles  
* @param 
* uint8_t data -> Data to send to the LCD
* uint 8_t control_flag -> Flag to determine if operation is data write or command write 
* @return None
*/
void LCD_Write_Data_4_Bit(uint8_t data, uint8_t control_flag);

/**
*@brief Sends a pulse to the Enable pin in order to allow for serial data transfer  
* @param None
* @return None
*/
void LCD_Enabled(void);

/**
*@brief Sends Commands to the LCD  
* @param 
* uint8_t command -> Command to send to LCD
* @return None
*/
void LCD_Send_Commands(uint8_t command);

/**
*@brief Sends characters to the LCD to be printed on the Screen 
* @param 
* uint8_t data -> Character or memory address to send to the LCD
* @return None
*/
void LCD_Send_Full_Data(uint8_t data);

/**
*@brief Initializes the LCD to begin communicating with microcontroller 
* @param None
* @return None
*/
void LCD_Init(void);

/**
*@brief Enables the LCD Display 
* @param None
* @return None
*/
void LCD_Enable_Display(void);

/**
*@brief Clears the LCD
* @param None 
* @return None
*/
void LCD_Clear(void);

/**
*@brief Sets the cursor location on the LCD 
* @param 
* uint8_t col -> Sets the cursor point on the LCD on the X axis
* uint8_t row -> Sets the cursor point on the LCD on the Y axis 
* @return None
*/

void LCD_Cursor(uint8_t col,uint8_t row);


/**
*@brief Returns LCD to home position 
* @param None
* @return None
*/
void LCD_Home(void);

/**
*@brief Stores a custom character into the CGRAM of the LCD  
* @param 
* uint8_t loc -> Memory location of custom character
* uint8_t char_buffer -> Array that stores the custom character
* @return None
*/

void LCD_Create_Custom_Char(uint8_t loc, uint8_t char_buffer[]);


/**
*@brief Prints the Player character on LCD by accessing the custom character stored in the CGRAM
* @param 
* struct Player *player- pointer to player in order to obtain location on LCD
* @return None
*/
void LCD_Print_Player(struct Player *player,int isPlayer);


/**
*@brief Refreshes the LCD screen and reprints characters at their new locations
* @param 
* struct Player *(char_array[8]) -> Array that stores pointers to the current objects to be displayed on the LCD
* uint32_t rate -> Sets the how long the LCD should wait before refreshing
* @return None
*/
void LCD_Refresh(struct Player *(char_array[8]),uint32_t rate);

/**
*@brief Prints a string onto the LCD 
* @param 
* char *string -> Array of characters to be printed onto the screen
* uint8_t col -> Sets the cursor point on the LCD on the X axis
* uint8_t line -> Sets the cursor point on the LCD on the Y axis 
* @return None
*/
void LCD_Print_Stirng(char *string,uint8_t col,uint8_t line);

/**
*@brief Prints a string onto the LCD 
* @param 
* char *string -> Array of characters to be printed onto the screen
* uint8_t col -> Sets the cursor point on the LCD on the X axis
* uint8_t line -> Sets the cursor point on the LCD on the Y axis 
* @return None
*/
void LCD_Print_Score(int score);
