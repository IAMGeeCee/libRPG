#include <iostream>
#include "Game.h"
#include <raylib.h>
#include <functional>

int MainLoop(Game& game)
{
	//Set up player
	Texture2D boySpriteSheet = LoadTexture("../../test-game/Assets/animations/boy-sprite-sheet.png");
	game.player.SpriteSheet = boySpriteSheet;
	game.player.spriteSheetRows = 4;
	game.player.spriteSheetColoumns = 3;
	game.player.size = {128,128};
	game.player.walkingSpeed = 2;
	game.player.sprintSpeed = 4;
	game.player.canSprint = true;

	BeginDrawing();
	ClearBackground(RAYWHITE); // Clear the background
	game.player.DrawPlayer();
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
