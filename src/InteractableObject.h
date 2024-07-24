#ifdef INTERACTABLEOBJECT_H
#define INTERACTABLEOBJECT_H

#include <raylib.h>
#include <string>

class InteractableObject
{
public:
    Vector2 Position;            // Position of InteractableObject
    Vector2 Size;                // Size of fInteractableObject
    std::string TextureLocation; // Location of texture
private:
};

#endif