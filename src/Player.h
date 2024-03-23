#include <raylib.h>
#include <raymath.h>
#include <list>

using namespace std;

class Player {
public:
	void DetectInput();
	void DrawPlayer();
	void ChangeKeybind();
	Vector2 position = {0,0};
	Vector2 size;
	Color color;
	Texture2D SpriteSheet;
	int spriteSheetRows = 1;
	int spriteSheetColoumns = 3;
	int walkingSpeed;
	int sprintSpeed;
	bool canSprint;

	KeyboardKey forwardKey = KEY_W;
	KeyboardKey backwardKey = KEY_S;
	KeyboardKey leftKey = KEY_A;
	KeyboardKey rightKey = KEY_D;
	KeyboardKey sprintKey = KEY_Q;
};
