#include "InteractableObject.h"
#include <iostream>

void InteractableObject::LoadTexture(){
    Texture = RAYLIB_H::LoadTexture(InteractableObject::TextureLocation.c_str());
    IsTextureLoaded = true;
}

void InteractableObject::DrawInteractableObject(){
    if(!IsTextureLoaded){
        LoadTexture();
    }

    Rectangle SourceRec = { 0.0f, 0.0f, (float)Texture.width, (float)Texture.height };
    Rectangle DestRec = {Position.x,Position.y,Size.x,Size.y};

    DrawTexturePro(InteractableObject::Texture,SourceRec,DestRec,{0,0},0.0f,WHITE);

    
}

void InteractableObject::UnloadTexture(){
    RAYLIB_H::UnloadTexture(InteractableObject::Texture);
    IsTextureLoaded = false;
}

InteractableObject::~InteractableObject(){
    RAYLIB_H::UnloadTexture(InteractableObject::Texture);
    IsTextureLoaded = false;
}