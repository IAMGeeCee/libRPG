#ifndef INTERACTABLEOBJECT_H
#define INTERACTABLEOBJECT_H

#include <raylib.h>
#include <string>

class InteractableObject
{
public:
    InteractableObject();
    ~InteractableObject();

    Vector2 Position;            // Position of InteractableObject
    Vector2 Size;                // Size of fInteractableObject
    std::string TextureLocation; // Location of texture
private:
    bool IsTextureLoaded = false;
    Texture2D Texture;
};

#endif