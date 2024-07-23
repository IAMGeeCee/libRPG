#include "Player.h"
#include <raylib.h>
#include <iostream>
#include <chrono>
#include <thread>

void Player::DrawPlayer()
{
    if (!IsTextureLoaded) // Load the texture if it isn't already loaded
    {
        PlayerTexture = LoadTexture(Player::SpriteSheet);
        SpriteFrameSource = {Size.y * Player::CurrentFrame, 0.0f, static_cast<float>(PlayerTexture.width / SpriteSheetColumns), static_cast<float>(PlayerTexture.height / SpriteSheetRows)};
        IsTextureLoaded = true;
        std::cout << "Loaded player texture" << std::endl;
    }

    IsMoving = false;

    int CurrentSpeed = WalkingSpeed;
    if (IsKeyDown(SprintKey) && CanSprint) // Set player's speed
    {
        CurrentSpeed = SprintSpeed;
    }

    if (IsKeyDown(ForwardKey))
    {
        Position.y -= CurrentSpeed * GetFrameTime();
        IsMoving = true;
        if (IsAnimatedOnMove)
        {
            SpriteFrameSource.y = Size.y * 3;
        }
        Player::MoveHitbox(ForwardKey, CurrentSpeed);
    }
    if (IsKeyDown(LeftKey))
    {
        Position.x -= CurrentSpeed * GetFrameTime();
        IsMoving = true;
        if (IsAnimatedOnMove)
        {
            SpriteFrameSource.y = Size.y * 1;
        }
        Player::MoveHitbox(LeftKey, CurrentSpeed);
    }
    if (IsKeyDown(BackwardKey))
    {
        Position.y += CurrentSpeed * GetFrameTime();
        IsMoving = true;
        if (IsAnimatedOnMove)
        {
            SpriteFrameSource.y = 0;
        }
        Player::MoveHitbox(BackwardKey, CurrentSpeed);
    }
    if (IsKeyDown(RightKey))
    {
        Position.x += CurrentSpeed * GetFrameTime();
        IsMoving = true;
        if (IsAnimatedOnMove)
        {
            SpriteFrameSource.y = Size.y * 2;
        }
        Player::MoveHitbox(RightKey, CurrentSpeed);
    }

    Rectangle DestRect = {Position.x, Position.y, Size.x, Size.y};

    if (IsMoving)
    {
        AnimatePlayerWalking();
    }

    DrawTexturePro(PlayerTexture, SpriteFrameSource, DestRect, {0, 0}, 0.0f, WHITE);
}

void Player::AnimatePlayerWalking()
{
    static float FrameDelay = 0.1f; // Animation speed
    static float TimeSinceLastFrame = 0.0f;

    TimeSinceLastFrame += GetFrameTime(); // Get deltaTime which is the time elapsed since the last frame

    if (TimeSinceLastFrame >= FrameDelay)
    {
        TimeSinceLastFrame = 0.0f;

        SpriteFrameSource.x = static_cast<float>(CurrentFrame * Size.x);
        CurrentFrame++;
        if (CurrentFrame == SpriteSheetColumns + 1)
        {
            CurrentFrame = 1;
        }
    }
}

void Player::MoveHitbox(int Direction, int CurrentSpeed)
{
    int OffsetX = 0, OffsetY = 0; // This is so the hitbox moves in a different direction based on the keypress

    if (Direction == Player::ForwardKey)
    {
        OffsetY = -1;
    }
    else if (Direction == Player::LeftKey)
    {
        OffsetX = -1;
    }
    else if (Direction == Player::RightKey)
    {
        OffsetX = 1;
    }
    else if (Direction == Player::BackwardKey)
    {
        OffsetY = 1;
    }

    Player::HitBox = {
        Player::Position.x + OffsetX,
        Player::Position.y + (Player::Size.y - 2) + OffsetY,
        Player::Size.x,
        2};

    DrawRectangle(Player::HitBox.x, Player::HitBox.y, Player::HitBox.width, Player::HitBox.height, RED);



    if (IsKeyDown(KEY_C))
    {
        std::cout << "X: " << static_cast<int>(HitBox.x / MapPointer->TileWidth) << ",Y: " << static_cast<int>(HitBox.y / MapPointer->TileHeight) << std::endl;
    }

    if (!(MapPointer->IsTileWalkable(static_cast<int>(HitBox.x / MapPointer->TileWidth), static_cast<int>(HitBox.y / MapPointer->TileHeight)))){
        std::cout << "Not walkable tile" << std::endl;
    }
}

void Player::UnloadPlayerTexture()
{
    UnloadTexture(PlayerTexture);
    IsTextureLoaded = false;
    std::cout << "Unloaded player texture" << std::endl;
}