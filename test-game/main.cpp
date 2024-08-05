#include <string>
#include <iostream>
#include <thread>
#include <Game.h>

void ObjectInteract(){
	std::cout << "Object interacted with" << std::endl;
}

int MainLoop(Game& Game)
{
	
	// Set up Map
  	Game.Map.TileSetLocation = "../../test-game/Assets/tileset/test-tileset.tsx";
  	Game.Map.TileMapLocation = "../../test-game/Assets/World1.tmx";


	//Set up Player
	Game.Player.SpriteSheet = "../../test-game/Assets/boy-sprite-sheet.png";
	Game.Player.SpriteSheetRows = 4;
	Game.Player.SpriteSheetColumns = 3;
	Game.Player.Size = {32,32};
	Game.Player.WalkingSpeed = 80;
	Game.Player.SprintSpeed = 160;
	Game.Player.CameraZoom = 4;
	Game.Player.CanSprint = true;
	Game.Player.CameraRotation = 0.0f;
	Game.Player.IsAnimatedOnMove = true;

	InteractableObject Object;
	Object.Position = {25,25};
	Object.Size = {128,128};
	Object.TextureLocation = "../../test-game/Assets/houseUnderground.png";
	Object.InteractAction = ObjectInteract;

	Game.AddInteractableObject(Object);

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