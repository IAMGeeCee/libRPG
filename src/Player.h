#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include <Map.h>

class Player
{
public:
	Vector2 position = {20 * 32, 20 * 32}; // The players current position
	Vector2 size = {32, 32};			   // How big the player should be in pixels
	const char *SpriteSheet;			   // Sprite sheet file path
	int spriteSheetRows = 1;			   // How many rows are on the sprite sheet for animation, each row will represent a different animation such as the firt row for walking down and the seconf for left
	int spriteSheetColumns = 3;			   // How many coloums are on the sprite sheet for animation, each couloumn represents one frame in an animation
	int walkingSpeed = 4;				   // Speed the player walks at (Defaults to 4)
	int sprintSpeed = 8;				   // Speed the player should move at when sprintign (Defaults to 8)
	bool canSprint = true;				   // Whether sprinting is enabled (Defaults to true)
	bool isAnimatedOnMove = true;		   // Whether movement animation should be enabled for the player (Defaults to true)
	float cameraZoom = 2.0f;			   // How zoomed the camera should be as a float, (Defaults to 2.0f)
	float cameraRotation = 0.0f;		   // How rotated the camera should be as a float (Defaults to 0f)

	KeyboardKey forwardKey = KEY_W;			  // Key binding for forward key (Defaults to W)
	KeyboardKey backwardKey = KEY_S;		  // Key binding for backward key (Defaults to S)
	KeyboardKey leftKey = KEY_A;			  // Key binding for left key (Defaults to a)
	KeyboardKey rightKey = KEY_D;			  // Key binding for right key (Defaults to d)
	KeyboardKey sprintKey = KEY_LEFT_CONTROL; // Key binding for sprint key, sprinting can be dissabled by setting canSprint to false (Defaults to Left Control)

	void DrawPlayer();			 // Draws player to the screen
	void AnimatePlayerWalking(); // Animates the player as it walks
	void UnloadTexture();		 // Unloads the player's texture at the end of the game

	Map * map; // Pointer to the gamees map so that we can do IsTileWalkable()

private:
	Color color = WHITE;							  // Player colour
	int CurrentFrame = 1;							  // Current frame of animation (out of the value of spriteSheetColumns)
	Rectangle spriteFrameSource;					  // Source rectangle for sprite frame
	bool isMoving = false;							  // Whether the player is currently moving
	Rectangle hitBox;								  // The player's hitbox
	bool isTextureLoaded = false;					  // Whether the texture is loaded
	Texture2D PlayerTexture;						  // Player texture
	void MoveHitbox(int Direction, int currentSpeed); // Moves the hitbox before moving the playerprotected:
};

#endif // PLAYER_H
