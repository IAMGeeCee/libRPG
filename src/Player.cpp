#include "Player.h"
#include <raylib.h>
#include <iostream>;

using namespace std;

void Player::DetectInput()
{
	int currentSpeed = walkingSpeed;
	bool isMoving = false;

	if (IsKeyDown(sprintKey) && canSprint)
	{
		currentSpeed = sprintSpeed;
	}

	if (IsKeyDown(forwardKey))
	{
		position.y -= currentSpeed * GetFrameTime(); // Ensure movement is frame-rate independent
		isMoving = true;
	}
	if (IsKeyDown(leftKey))
	{
		position.x -= currentSpeed * GetFrameTime();
		isMoving = true;
	}
	if (IsKeyDown(backwardKey))
	{
		position.y += currentSpeed * GetFrameTime();
		isMoving = true;
	}
	if (IsKeyDown(rightKey))
	{
		position.x += currentSpeed * GetFrameTime();
		isMoving = true;
	}

	if (isMoving && isAnimatedOnMove)
	{
		AnimatePlayerWalking();
	}
}

void Player::DrawPlayer()
{
	PlayerTexture = LoadTexture(Player::SpriteSheet);
	int spriteSheetWidth = PlayerTexture.width;
	int spriteSheetHeight = PlayerTexture.height;

	int spriteSheetColumnSize = spriteSheetWidth / spriteSheetColumns;
	int spriteSheetRowSize = spriteSheetHeight / spriteSheetRows;

	Rectangle sourceRect = {
		currentFrame * size.x, // x-coordinate based on current frame
		0,
		static_cast<float>(spriteSheetColumnSize),
		static_cast<float>(spriteSheetRowSize)};

	Rectangle destRect = {
		position.x,
		position.y,
		size.x,
		size.y};

	DrawTexturePro(PlayerTexture, sourceRect, destRect, {0, 0}, 0.0f, WHITE);
}

void Player::AnimatePlayerWalking()
{
	// Update elapsed time
	elapsedTime += GetFrameTime();

	// Check if it's time to advance to the next frame
	if (elapsedTime >= frameDuration)
	{
		elapsedTime = 0.0f;
		currentFrame++;

		// Loop the animation
		if (currentFrame >= frameCount)
		{
			currentFrame = 0;
		}
	}
}