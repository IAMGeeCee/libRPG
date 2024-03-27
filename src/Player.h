#include <raylib.h>
#include <raymath.h>
#include <list>
#include <string>

using namespace std;

class Player {
public:
	void DetectInput();
	void DrawPlayer();
	Vector2 position = {0,0};
	Vector2 size;
	Color color;
  char* SpriteSheet;
	int spriteSheetRows = 1;
	int spriteSheetColoumns = 3;
	int walkingSpeed;
	int sprintSpeed;
	bool canSprint;

	KeyboardKey forwardKey = KEY_W;
	KeyboardKey backwardKey = KEY_S;
	KeyboardKey leftKey = KEY_A;
	KeyboardKey rightKey = KEY_D;
	KeyboardKey sprintKey = KEY_LEFT_CONTROL;
};
