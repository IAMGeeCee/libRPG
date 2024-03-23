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

}

void Player::DrawPlayer(Rectangle destRect)
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
	DrawTexturePro(Player::SpriteSheet, sourceRect, destRect, {0, 0}, 0.0f, WHITE);
}
