#include "InteractableObject.h"

InteractableObject::InteractableObject(){
    if(!IsTextureLoaded){
        Texture = LoadTexture(TextureLocation.c_str());
        IsTextureLoaded = true;
    }
}

InteractableObject::~InteractableObject(){
    UnloadTexture(Texture);
    IsTextureLoaded = false;
}