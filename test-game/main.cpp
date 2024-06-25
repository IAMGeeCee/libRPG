#include <string>
#include <iostream>
#include <thread>
#include <Game.h>


int MainLoop(Game& game)
{
	
	// Set up Map
  	game.map.tileSetLocation = "../../test-game/Assets/tiles/test-tileset.tsx";
  	game.map.tileMapLocation = "../../test-game/Assets/tiles/World Tilemaps/World1.tmx";
  	game.map.LoadTileMap();

	//Set up Player
	game.player.SpriteSheet = "../../test-game/Assets/animations/boy-sprite-sheet.png";
	game.player.spriteSheetRows = 4;
	game.player.spriteSheetColumns = 3;
	game.player.size = {32,32};
	game.player.walkingSpeed = 80;
	game.player.sprintSpeed = 160;
	game.player.cameraZoom = 4;
	game.player.canSprint = true;
	game.player.cameraRotation = 0.0f;
	game.player.isAnimatedOnMove = true;
	game.player.DrawPlayer();
	std::cout << "About to unload textures /n";
	game.map.UnloadTileTextures();
	std::cout << "Did it /n";

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