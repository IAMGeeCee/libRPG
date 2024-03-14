#include "Player.h"
#include <raylib.h>
#include <iostream>
#include <list>

using namespace std;

void Player::DetectInput()
{
}

void Player::DrawPlayer(Texture2D SpriteSheet, Rectangle sourceRect, Rectangle destRect)
{
	DrawTexturePro(SpriteSheet, sourceRect, destRect, {0, 0}, 0.0f, WHITE);
}
