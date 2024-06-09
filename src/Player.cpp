#include "Player.h"
#include <raylib.h>
#include <iostream>
#include <chrono>
#include <thread>

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
        std::thread t{ &Player::AnimatePlayerWalking, this };
        t.join();
    }

    DrawTexturePro(PlayerTexture, spriteFrameSource, destRect, {0, 0}, 0.0f, WHITE);
}


void Player::AnimatePlayerWalking() {
    

    spriteFrameSource.x = static_cast<float>(CurrentFrame * size.x);
    CurrentFrame++;
    if (CurrentFrame == Player::spriteSheetColumns + 1){
        CurrentFrame = 1;
    }
    
}

void Player::AnimatePlayerWalkingForward() {
    spriteFrameSource.y = size.y * 3; 
}

void Player::AnimatePlayerWalkingBackward() {
    spriteFrameSource.y = 0; 
}

void Player::AnimatePlayerWalkingLeft() {
    spriteFrameSource.y = size.y * 1; 
}

void Player::AnimatePlayerWalkingRight() {
    spriteFrameSource.y = size.y * 2; 
}
