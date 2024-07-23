#include <string>
#include <iostream>
#include <thread>
#include <Game.h>


int MainLoop(Game& game)
{
	
	// Set up Map
  	game.Map.TileSetLocation = "../../test-game/Assets/tiles/test-tileset.tsx";
  	game.Map.TileMapLocation = "../../test-game/Assets/tiles/World Tilemaps/World1.tmx";
  	game.Map.LoadTileMap();


	//Set up Player
	game.Player.SpriteSheet = "../../test-game/Assets/animations/boy-sprite-sheet.png";
	game.Player.SpriteSheetRows = 4;
	game.Player.SpriteSheetColumns = 3;
	game.Player.Size = {32,32};
	game.Player.WalkingSpeed = 80;
	game.Player.SprintSpeed = 160;
	game.Player.CameraZoom = 4;
	game.Player.CanSprint = true;
	game.Player.CameraRotation = 0.0f;
	game.Player.IsAnimatedOnMove = true;
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