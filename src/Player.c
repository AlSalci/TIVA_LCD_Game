#include "Player.h"




void Player_Move_Forward(struct Player *player)
{
	if(player->x_cord< 15)
	{
	player->x_cord++;
	}
	
}

void Player_Move_Back(struct Player *player)
{
	if(player->x_cord> 0)
	{
	player->x_cord--;
	}
	
}


void Player_Move_Line(struct Player *player)
{
	if(player->y_cord == 1)
	{
	player->y_cord = 0;
		return;
	}
	
	
	if(player->y_cord ==0)
	{
	player->y_cord = 1;
		return;
	}
	
	
}

void Enemy_move(struct Player *Enemy)
{
	int ran = rand()%51;
	if( ran <= 25)
	{
		Player_Move_Forward(Enemy);
	} else
	{
		Player_Move_Back(Enemy);
		
	}
	
	ran = rand()%2;
	
	if( ran == 1)
	{
		Player_Move_Line(Enemy);
	} 
	
	
	
}

