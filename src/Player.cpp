#include "Player.h"
#include <raylib.h>
#include <iostream>
#include <list>

using namespace std;

void Player::DetectInput()
{

}

void Player::DrawPlayer(Rectangle sourceRect, Rectangle destRect)
{
	DrawTexturePro(Player::SpriteSheet, sourceRect, destRect, {0, 0}, 0.0f, WHITE);
}
