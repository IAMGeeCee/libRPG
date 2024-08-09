#include "Entity.h"
#include <iostream>

void Entity::DrawEntity()
{
    if (!IsTextureLoaded) // Load the texture if it isn't already loaded
    {
        EntityTexture = LoadTexture(Entity::SpriteSheet);
        SpriteFrameSource = {Size.y * Entity::CurrentFrame, 0.0f, static_cast<float>(EntityTexture.width / SpriteSheetColumns), static_cast<float>(EntityTexture.height / SpriteSheetRows)};
        IsTextureLoaded = true;
        std::cout << "Loaded player texture" << std::endl;
    }

    IsMoving = false;

    Rectangle DestRect = {Position.x, Position.y, Size.x, Size.y};
    DrawTexturePro(EntityTexture, SpriteFrameSource, DestRect, {0, 0}, 0.0f, WHITE);
}

void Entity::UnloadEntityTexture(){
    UnloadTexture(EntityTexture);
}