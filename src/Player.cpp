#include "Player.h"
#include <raylib.h>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int currentFrameNumber = 1;

void Player::DrawPlayer()
{
    Player::SetUpHitbox();
    if (!isTextureLoaded)
    {
        PlayerTexture = LoadTexture(Player::SpriteSheet);
        spriteFrameSource = {size.y * currentFrameNumber, 0.0f, static_cast<float>(PlayerTexture.width / spriteSheetColumns), static_cast<float>(PlayerTexture.height / spriteSheetRows)};
        isTextureLoaded = true;
        cout << "Loaded player texture" << endl;
    }

    int currentSpeed = walkingSpeed;
    isMoving = false;

    if (IsKeyDown(sprintKey) && canSprint)
    {
        currentSpeed = sprintSpeed;
    }

    if (IsKeyDown(forwardKey))
    {
        position.y -= currentSpeed * GetFrameTime();
        isMoving = true;
        if (isAnimatedOnMove)
        {
            AnimatePlayerWalkingForward();
        }
    }
    if (IsKeyDown(leftKey))
    {
        position.x -= currentSpeed * GetFrameTime();
        isMoving = true;
        if (isAnimatedOnMove)
        {
            AnimatePlayerWalkingLeft();
        }
    }
    if (IsKeyDown(backwardKey))
    {
        position.y += currentSpeed * GetFrameTime();
        isMoving = true;
        if (isAnimatedOnMove)
        {
            AnimatePlayerWalkingBackward();
        }
    }
    if (IsKeyDown(rightKey))
    {
        position.x += currentSpeed * GetFrameTime();
        isMoving = true;
        if (isAnimatedOnMove)
        {
            AnimatePlayerWalkingRight();
        }
    }

    Rectangle destRect = {
        position.x,
        position.y,
        size.x,
        size.y};

    if (isMoving)
    {
        AnimatePlayerWalking();
    }

    DrawTexturePro(PlayerTexture, spriteFrameSource, destRect, {0, 0}, 0.0f, WHITE);
}

void Player::AnimatePlayerWalking()
{
    static float frameDelay = 0.07f; // Adjust this value to control the speed
    static float timeSinceLastFrame = 0.0f;

    timeSinceLastFrame += GetFrameTime(); // deltaTime is the time elapsed since the last frame

    if (timeSinceLastFrame >= frameDelay)
    {
        timeSinceLastFrame = 0.0f;

        spriteFrameSource.x = static_cast<float>(CurrentFrame * size.x);
        CurrentFrame++;
        if (CurrentFrame == spriteSheetColumns + 1)
        {
            CurrentFrame = 1;
        }
        currentFrameNumber = CurrentFrame;
    }
}

void Player::AnimatePlayerWalkingForward()
{
    spriteFrameSource.y = size.y * 3;
}

void Player::AnimatePlayerWalkingBackward()
{
    spriteFrameSource.y = 0;
}

void Player::AnimatePlayerWalkingLeft()
{
    spriteFrameSource.y = size.y * 1;
}

void Player::AnimatePlayerWalkingRight()
{
    spriteFrameSource.y = size.y * 2;
}

void Player::SetUpHitbox()
{
    Player::hitBox = {
        Player::position.x,
        Player::position.y + (Player::size.y - 2),
        Player::size.x,
        2};
    DrawRectangle(Player::position.x,
                  Player::position.y + (Player::size.y - 2),
                  Player::size.x,
                  2, RED);
}

void Player::UnloadTexture()
{
    RAYLIB_H::UnloadTexture(PlayerTexture);
    isTextureLoaded = false;
    cout << "Unloaded player texture" << endl;
}
