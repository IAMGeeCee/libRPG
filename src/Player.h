#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

class Player {
public:
    Vector2 position = {0, 0};
    Vector2 size = {64, 64};
    Color color = WHITE;
    const char *SpriteSheet; // Sprite sheet file path
    int spriteSheetRows = 1;
    int spriteSheetColumns = 3;
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

    Texture2D PlayerTexture; // Player texture
    void LoadPlayerTexture();
    void UnloadPlayerTexture();

    void DrawPlayer();
    void AnimatePlayerWalking();
    void AnimatePlayerWalkingForward();
    void AnimatePlayerWalkingBackward();
    void AnimatePlayerWalkingLeft();
    void AnimatePlayerWalkingRight();

private:
 	int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 10;
    int frameCount = 3; // Number of frames in one row
    float frameDuration = 0.1f; // Time per frame
    float elapsedTime = 0.0f; // Time since last frame change
    Rectangle spriteFrameSource; // Source rectangle for sprite frame
	bool isMoving = false;
};

#endif // PLAYER_H
