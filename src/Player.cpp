#include "Player.h"
#include <raylib.h>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int currentFrameNumber = 1;

void Player::DrawPlayer()
{

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
            spriteFrameSource.y = size.y * 3;
        }
        Player::MoveHitbox(forwardKey, currentSpeed);
    }
    if (IsKeyDown(leftKey))
    {
        position.x -= currentSpeed * GetFrameTime();
        isMoving = true;
        if (isAnimatedOnMove)
        {
            spriteFrameSource.y = size.y * 1;
        }
        Player::MoveHitbox(leftKey, currentSpeed);
    }
    if (IsKeyDown(backwardKey))
    {
        position.y += currentSpeed * GetFrameTime();
        isMoving = true;
        if (isAnimatedOnMove)
        {
            spriteFrameSource.y = 0;
        }
        Player::MoveHitbox(backwardKey, currentSpeed);
    }
    if (IsKeyDown(rightKey))
    {
        position.x += currentSpeed * GetFrameTime();
        isMoving = true;
        if (isAnimatedOnMove)
        {
            spriteFrameSource.y = size.y * 2;
        }
        Player::MoveHitbox(rightKey, currentSpeed);
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
    static float frameDelay = 0.1f; // Adjust this value to control the speed
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

void Player::MoveHitbox(int Direction, int currentSpeed)
{
    if (Direction == Player::forwardKey)
    {
        Player::hitBox = {
            Player::position.x,
            (Player::position.y + (Player::size.y - 2)) - 1,
            Player::size.x,
            2};

        DrawRectangle(hitBox.x, hitBox.y, hitBox.width, hitBox.height, RED);
    }
    else if (Direction == Player::leftKey)
    {
        Player::hitBox = {
            (Player::position.x) - 1,
            Player::position.y + (Player::size.y - 2),
            Player::size.x,
            2};

        DrawRectangle(hitBox.x, hitBox.y, hitBox.width, hitBox.height, RED);
    }
    else if (Direction == Player::rightKey)
    {
        Player::hitBox = {
            Player::position.x + 1,
            Player::position.y + (Player::size.y - 2),
            Player::size.x,
            2};

        DrawRectangle(hitBox.x, hitBox.y, hitBox.width, hitBox.height, RED);
    }
    else if (Direction == Player::backwardKey)
    {
        Player::hitBox = {
            Player::position.x,
            (Player::position.y + (Player::size.y - 2)) + 1,
            Player::size.x,
            2};

        DrawRectangle(hitBox.x, hitBox.y, hitBox.width, hitBox.height, RED);
    }

    
}

void Player::UnloadTexture()
{
    RAYLIB_H::UnloadTexture(PlayerTexture);
    isTextureLoaded = false;
    cout << "Unloaded player texture" << endl;
}