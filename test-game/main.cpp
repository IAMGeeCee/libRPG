#include <iostream>
#include "Game.h"
#include <raylib.h>
#include <functional>

int MainLoop(Game& game)
{
	// Load the sprite sheet
	Texture2D boySpriteSheet = LoadTexture("../../test-game/Assets/animations/boy-sprite-sheet.png");
	game.player.SpriteSheet = boySpriteSheet;
	game.player.spriteSheetRows = 4;
	game.player.spriteSheetColoumns = 3;
	game.player.size = {128,128};
	game.player.walkingSpeed = 4;
	game.player.sprintSpeed = 8;
	game.player.canSprint = true;

	BeginDrawing();
	ClearBackground(RAYWHITE); // Clear the background
	game.player.DrawPlayer();
	game.player.DetectInput();


	EndDrawing();
	return 0;
}

int main()
{
	// Create an instance of the Game class
	// and then start the game with the user defined game logic function (line 6)
	Game testgame = Game();  
	testgame.StartGame([&]() { return MainLoop(testgame); });

	return 0;
}
