#include "Player.h"
#include <raylib.h>
#include <iostream>
#include <list>

using namespace std;

void Player::ChangeKeybind()
{

}

void Player::DetectInput()
{
	if(IsKeyDown(Player::forwardKey))
	{
		Player::position.y = Player::position.y - Player::walkingSpeed;
	}
	if(IsKeyDown(Player::leftKey))
	{
		Player::position.x = Player::position.x - Player::walkingSpeed;
	}
	if(IsKeyDown(Player::backwardKey))
	{
		Player::position.y = Player::position.y + Player::walkingSpeed;
	}
	if(IsKeyDown(Player::rightKey))
	{
		Player::position.x = Player::position.x + Player::walkingSpeed;
	}
}

void Player::DrawPlayer()
{	
	int spriteSheetWidth = Player::SpriteSheet.width;
	int spriteSheetHeight = Player::SpriteSheet.height;

	int spriteSheetColoumnSize = spriteSheetWidth / Player::spriteSheetColoumns;
	int spriteSheetRowSize = spriteSheetHeight / Player::spriteSheetRows;

	Rectangle sourceRect;
		sourceRect.x = 0;
		sourceRect.y = 0;
		sourceRect.width = spriteSheetColoumnSize;
		sourceRect.height = spriteSheetRowSize;
	Rectangle destRect;
		destRect.x = Player::position.x;
		destRect.y = Player::position.y;
		destRect.width = Player::size.x;
		destRect.height = Player::size.y;

	DrawTexturePro(Player::SpriteSheet, sourceRect, destRect, {0, 0}, 0.0f, WHITE);
}
