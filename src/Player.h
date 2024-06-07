#include <raylib.h>
#include <raymath.h>
#include <list>
#include <string>

using namespace std;

class Player
{
public:
	void DetectInput();
	void DrawPlayer();
	Vector2 position = {0, 0};
	Vector2 size = {64, 64};
	Color color = WHITE;
	char *SpriteSheet; // TODO: Make some sort of fallback
	int spriteSheetRows = 1;
	int spriteSheetColoumns = 3;
	int walkingSpeed = 4;
	int sprintSpeed = 8;
	bool canSprint = true;
	bool isAnimatedOnMove = true;
	float cameraZoom = 2.0f;
	float cameraRotation = 0.0f;

	KeyboardKey forwardKey = KEY_W;
	KeyboardKey backwardKey = KEY_S;
	KeyboardKey leftKey = KEY_A;
	KeyboardKey rightKey = KEY_D;
	KeyboardKey sprintKey = KEY_LEFT_CONTROL;
};
