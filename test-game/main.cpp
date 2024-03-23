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

	BeginDrawing();
	ClearBackground(RAYWHITE); // Clear the background
	DrawFPS(50, 50);



	Rectangle destRect;
		destRect.x = 500;
		destRect.y = 500;
		destRect.width = 128;
		destRect.height = 128;
	game.player.DrawPlayer(destRect);



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
