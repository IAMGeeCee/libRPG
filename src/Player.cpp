#include "Player.h"
#include <raylib.h>
#include <iostream>

using namespace std;

void Player::LoadPlayerTexture() {
    PlayerTexture = LoadTexture(SpriteSheet);
    spriteFrameSource = {0.0f, 0.0f, static_cast<float>(PlayerTexture.width / spriteSheetColumns), static_cast<float>(PlayerTexture.height / spriteSheetRows)};
}

void Player::UnloadPlayerTexture() {
    UnloadTexture(PlayerTexture);
}

void Player::DrawPlayer() {
    int currentSpeed = walkingSpeed;
    isMoving = false;

    if (IsKeyDown(sprintKey) && canSprint) {
        currentSpeed = sprintSpeed;
    }

    if (IsKeyDown(forwardKey)) {
        position.y -= currentSpeed * GetFrameTime();
        isMoving = true;
        if (isAnimatedOnMove) {
            AnimatePlayerWalkingForward();
			
        }
    }
    if (IsKeyDown(leftKey)) {
        position.x -= currentSpeed * GetFrameTime();
        isMoving = true;
        if (isAnimatedOnMove) {
            AnimatePlayerWalkingLeft();
        }
    }
    if (IsKeyDown(backwardKey)) {
        position.y += currentSpeed * GetFrameTime();
        isMoving = true;
        if (isAnimatedOnMove) {
            AnimatePlayerWalkingBackward();
        }
    }
    if (IsKeyDown(rightKey)) {
        position.x += currentSpeed * GetFrameTime();
        isMoving = true;
        if (isAnimatedOnMove) {
            AnimatePlayerWalkingRight();
        }
    }

	  Rectangle destRect = {
        position.x,
        position.y,
        size.x,
        size.y
    };

	if (isMoving) {
        AnimatePlayerWalking();
    }

    DrawTexturePro(PlayerTexture, spriteFrameSource, destRect, {0, 0}, 0.0f, WHITE);
}

void Player::AnimatePlayerWalking() {
    // Update elapsed time
    framesCounter++;
    if (framesCounter >= framesSpeed) {
        framesCounter = 0;
        currentFrame++;

        if (currentFrame >= spriteSheetColumns) {
            currentFrame = 0;
        }

        spriteFrameSource.x = static_cast<float>(currentFrame * size.x);
    }
}

void Player::AnimatePlayerWalkingForward() {
    spriteFrameSource.y = 0; // Row 0 for forward animation
}

void Player::AnimatePlayerWalkingBackward() {
    spriteFrameSource.y = size.y * 1; // Row 1 for backward animation
}

void Player::AnimatePlayerWalkingLeft() {
    spriteFrameSource.y = size.y * 2; // Row 2 for left animation
}

void Player::AnimatePlayerWalkingRight() {
    spriteFrameSource.y = size.y * 3; // Row 3 for right animation
}
