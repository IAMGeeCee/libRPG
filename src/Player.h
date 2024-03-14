#include <raylib.h>
#include <list>

using namespace std;

class Player {
public:
	void DetectInput();
	void DrawPlayer(Texture2D SpriteSheet, Rectangle sourceRect, Rectangle destRect);
	Vector2 position;
	Vector2 size;
	Color color;
};
