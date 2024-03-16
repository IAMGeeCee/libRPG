#include <raylib.h>
#include <raymath.h>
#include <list>

using namespace std;

class Player {
public:
	void DetectInput();
	void DrawPlayer(Rectangle sourceRect, Rectangle destRect);
	Vector2 position = {0,0};
	Vector2 size;
	Color color;
	Texture2D SpriteSheet;
};
