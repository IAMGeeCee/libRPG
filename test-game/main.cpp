#include <iostream>
#include "Game.h"
#include <raylib.h>
#include <functional>

int MainLoop(Game& game)
{
	// Load the sprite sheet
	Texture2D boySpriteSheet = LoadTexture("../../test-game/Assets/animations/boy-sprite-sheet.png");
	
	BeginDrawing();

	ClearBackground(RAYWHITE); // Clear the background
	
	DrawFPS(50, 50);

	game.player.position.x;

	EndDrawing();

	return 0;
}

int main()
{
	std::cout << "Hello World!\n";

	// Create an instance of the Game class
	// and then start the game with the user defined game logic function (line 6)
	Game testgame = Game();  
	testgame.StartGame([&]() { return MainLoop(testgame); });

	return 0;
}
