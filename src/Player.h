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
 	int CurrentFrame = 1;
    Rectangle spriteFrameSource; // Source rectangle for sprite frame
	bool isMoving = false;

};

#endif // PLAYER_H
