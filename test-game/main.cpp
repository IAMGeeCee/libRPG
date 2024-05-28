//#include "Game.h"
#include "../src/Game.h"

int MainLoop(Game& game)
{
	// Load the player
  	game.map.tileSetLocation = "../../test-game/Assets/tiles/test-tileset.tsx";
  	game.map.tileMapLocation = "../../test-game/Assets/tiles/World Tilemaps/test-tilemap.tmx";
  	game.map.LoadTileMap();
	game.player.SpriteSheet = "../../test-game/Assets/animations/boy-sprite-sheet.png";
	game.player.spriteSheetRows = 4;
	game.player.spriteSheetColoumns = 3;
	game.player.size = {32,32};
	game.player.walkingSpeed = 8;
	game.player.sprintSpeed = 12;
	game.player.canSprint = true;
	game.player.DrawPlayer();
	game.player.DetectInput();
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