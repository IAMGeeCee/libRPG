#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include <Map.h>
#include <vector>
#include <InteractableObject.h>

class Player
{
public:
	Vector2 Position = {20 * 32, 20 * 32}; // The players current position
	Vector2 Size = {32, 32};			   // How big the player should be in pixels
	const char *SpriteSheet;			   // Sprite sheet file path
	int SpriteSheetRows = 1;			   // How many rows are on the sprite sheet for animation, each row will represent a different animation such as the firt row for walking down and the seconf for left
	int SpriteSheetColumns = 3;			   // How many coloums are on the sprite sheet for animation, each couloumn represents one frame in an animation
	int WalkingSpeed = 4;				   // Speed the player walks at (Defaults to 4)
	int SprintSpeed = 8;				   // Speed the player should move at when sprintign (Defaults to 8)
	bool CanSprint = true;				   // Whether sprinting is enabled (Defaults to true)
	bool IsAnimatedOnMove = true;		   // Whether movement animation should be enabled for the player (Defaults to true)
	float CameraZoom = 2.0f;			   // How zoomed the camera should be as a float, (Defaults to 2.0f)
	float CameraRotation = 0.0f;		   // How rotated the camera should be as a float (Defaults to 0f)

	KeyboardKey ForwardKey = KEY_W;			  // Key binding for forward key (Defaults to W)
	KeyboardKey BackwardKey = KEY_S;		  // Key binding for backward key (Defaults to S)
	KeyboardKey LeftKey = KEY_A;			  // Key binding for left key (Defaults to a)
	KeyboardKey RightKey = KEY_D;			  // Key binding for right key (Defaults to d)
	KeyboardKey SprintKey = KEY_LEFT_CONTROL; // Key binding for sprint key, sprinting can be dissabled by setting canSprint to false (Defaults to Left Control)

	void DrawPlayer();			 // Draws player to the screen
	void AnimatePlayerWalking(); // Animates the player as it walks
	void UnloadPlayerTexture();	 // Unloads the player's texture at the end of the game

	Map *MapPointer; // Pointer to the games map so that we can do IsTileWalkable()

	std::vector<InteractableObject> *InteractableObjectListPointer;
	InteractableObject *ClosestInteractableObject;	  // The last interactableObject that the player got near
	bool GetCanInteract();

private:
	Color PlayerColour = WHITE;						  // Player colour
	int CurrentFrame = 1;							  // Current frame of animation (out of the value of spriteSheetColumns)
	Rectangle SpriteFrameSource;					  // Source rectangle for sprite frame
	bool IsMoving = false;							  // Whether the player is currently moving
	Rectangle HitBox;								  // The player's hitbox
	bool IsTextureLoaded = false;					  // Whether the texture is loaded
	Texture2D PlayerTexture;						  // Player texture
	bool MoveHitbox(int Direction, int currentSpeed); // Moves the hitbox before moving the playerprotected:
	bool CanInteractWithInteractable = false;		  // Wether or not the player can interact with an interactableobject
};

#endif // PLAYER_H
