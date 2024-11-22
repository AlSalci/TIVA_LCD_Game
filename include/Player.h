
#include "TM4C123GH6PM.h"
#include <stdlib.h>
static struct Player player;
static struct Player *player_ptr = &player;

struct Player
{
	uint8_t x_cord,y_cord;
	
};


/**
 * @brief Increments the x coordinate of the character that is passed by the pointer paramater
 * @param *player- Pointer to current character to be moved
 * @return None
 */
void Player_Move_Forward(struct Player *player);

/**
 * @brief Decrements the x coordinate of the character that is passed by the pointer paramater
 * @param *player- Pointer to current character to be moved
 * @return None
 */
void Player_Move_Back(struct Player *player);

/**
 * @brief Toggles y coordinate of the character to move between the lines of the LCD
 * @param *player- Pointer to current character to be moved
 * @return None
 */
void Player_Move_Line(struct Player *player);

/**
 * @brief Randomly moves an enemy character around the LCD
 * @param *enemy- Pointer to current character to be moved
 * @return None
 */
void Enemy_move(struct Player *Enemy);