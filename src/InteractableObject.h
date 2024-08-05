#ifndef INTERACTABLEOBJECT_H
#define INTERACTABLEOBJECT_H

#include <raylib.h>
#include <string>
#include <functional>

class InteractableObject
{
public:
    ~InteractableObject();
    void UnloadTexture(); // Unloads the texture
    void DrawInteractableObject();

    Vector2 Position;                     // Position of InteractableObject
    Vector2 Size;                         // Size of fInteractableObject
    std::string TextureLocation;          // Location of texture
    std::function<void()> InteractAction; // Function to run when interacted with
private:
    void LoadTexture(); // Loads the texture
    bool IsTextureLoaded = false;
    Texture2D Texture;
};

#endif