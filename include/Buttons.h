#include "TM4C123GH6PM.h"
#include "SystemDelays.h"
#include "LCD.h"

/**
 * @brief Initializes the pins that are to be used by the push buttons SW2 to SW5
 * @param None
 * @return None
 */
void Button_init(void);


/**
 * @brief Gets the status of the push buttons on the EduBase board from SW2 to SW5
 * @param None
 * @return None
 */
uint8_t Get_Button_Status(void);


/**
 * @brief Determines the player actions that are performed based on which push button is pressed
 * @param 
 * uint8_t button_status -> Current status of the push buttons SW2-SW5
 * struct Player *ptr -> Pointer to player character
 * @return None
 */
void Button_Controller(uint8_t button_status,struct Player *ptr);

