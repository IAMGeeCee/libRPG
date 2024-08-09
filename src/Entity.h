#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>
#include "Map.h"
#include "InteractableObject.h"

class Entity{
public:
	Vector2 Position = {20 * 32, 20 * 32}; // The entitie's current position
	Vector2 Size = {32, 32};			   // How big the entity should be in pixels
	const char *SpriteSheet;			   // Sprite sheet file path
	int SpriteSheetRows = 1;			   // How many rows are on the sprite sheet for animation, each row will represent a different animation such as the firt row for walking down and the seconf for left
	int SpriteSheetColumns = 3;			   // How many coloums are on the sprite sheet for animation, each couloumn represents one frame in an animation
	int WalkingSpeed = 4;				   // Speed the enitity walks at (Defaults to 4)
    bool IsAnimatedOnMove = true;		   // Whether movement animation should be enabled for the entity (Defaults to true)

	void DrawEntity();			 // Draws entity to the screen
	void UnloadEntityTexture();	 // Unloads the entitie's texture at the end of the game

	Map *MapPointer; // Pointer to the games map so that we can do IsTileWalkable()

	std::vector<InteractableObject> *InteractableObjectListPointer;
private:
	Color EntityColour = WHITE;						  // Entitie's colour
	int CurrentFrame = 1;							  // Current frame of animation (out of the value of spriteSheetColumns)
	Rectangle SpriteFrameSource;					  // Source rectangle for sprite frame
	bool IsMoving = false;							  // Whether the entity is currently moving
	Rectangle HitBox;								  // The entitie's hitbox
	bool IsTextureLoaded = false;					  // Whether the texture is loaded
	Texture2D EntityTexture;						  // Entity texture
};

#endif