#include <string>
#include <iostream>
#include <thread>
#include <Game.h>


int MainLoop(Game& game)
{
	
	// Set up Map
  	game.Map.tileSetLocation = "../../test-game/Assets/tiles/test-tileset.tsx";
  	game.Map.tileMapLocation = "../../test-game/Assets/tiles/World Tilemaps/World1.tmx";
  	game.Map.LoadTileMap();


	//Set up Player
	game.Player.SpriteSheet = "../../test-game/Assets/animations/boy-sprite-sheet.png";
	game.Player.spriteSheetRows = 4;
	game.Player.spriteSheetColumns = 3;
	game.Player.size = {32,32};
	game.Player.walkingSpeed = 80;
	game.Player.sprintSpeed = 160;
	game.Player.cameraZoom = 4;
	game.Player.canSprint = true;
	game.Player.cameraRotation = 0.0f;
	game.Player.isAnimatedOnMove = true;
	game.Player.DrawPlayer();

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