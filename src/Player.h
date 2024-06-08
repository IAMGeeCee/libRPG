#include <raylib.h>
#include <raymath.h>
#include <list>
#include <string>
class Player {
public:
    Vector2 position = {0, 0};
    Vector2 size = {64, 64};
    Color color = WHITE;
    const char *SpriteSheet; // Sprite sheet file path
    int spriteSheetRows = 1;
    int spriteSheetColumns = 3;
    int walkingSpeed = 80;
    int sprintSpeed = 160;
    bool canSprint = true;
    bool isAnimatedOnMove = true;
    float cameraZoom = 2.0f;
    float cameraRotation = 0.0f;

    KeyboardKey forwardKey = KEY_W;
    KeyboardKey backwardKey = KEY_S;
    KeyboardKey leftKey = KEY_A;
    KeyboardKey rightKey = KEY_D;
    KeyboardKey sprintKey = KEY_LEFT_CONTROL;

    void DetectInput();
    void DrawPlayer();

private:
    int currentFrame = 0;
    int frameCount = 3; // Number of frames in one row
    float frameDuration = 0.1f; // Time per frame
    float elapsedTime = 0.0f; // Time since last frame change
	Texture2D PlayerTexture;
    void AnimatePlayerWalking(); // Player texture
};
