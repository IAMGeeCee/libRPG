#include <string>
#include <iostream>
#include <thread>
#include <Game.h>

Game testgame = Game(); 

void ObjectInteract(){
	testgame.Map.TileMapLocation = "../../test-game/Assets/test-tilemap.tmx";
}

int MainLoop()
{
	
	// Set up Map
  	testgame.Map.TileSetLocation = "../../test-game/Assets/tileset/test-tileset.tsx";


	//Set up Player
	testgame.Player.SpriteSheet = "../../test-game/Assets/boy-sprite-sheet.png";
	testgame.Player.SpriteSheetRows = 4;
	testgame.Player.SpriteSheetColumns = 3;
	testgame.Player.Size = {32,32};
	testgame.Player.WalkingSpeed = 80;
	testgame.Player.SprintSpeed = 160;
	testgame.Player.CameraZoom = 4;
	testgame.Player.CanSprint = true;
	testgame.Player.CameraRotation = 0.0f;
	testgame.Player.IsAnimatedOnMove = true;

	testgame.InteractInputType = MOUSE_BUTTON;

	InteractableObject Object;
	Object.Position = {25,25};
	Object.Size = {128,128};
	Object.TextureLocation = "../../test-game/Assets/houseUnderground.png";
	Object.InteractAction = ObjectInteract;

	testgame.AddInteractableObject(Object);

	return 0;
}

int main()
{
	// Create an instance of the Game class
	// and then start the game with the user defined game logic function (line 6)
		
  	testgame.Map.TileMapLocation = "../../test-game/Assets/World1.tmx";
	testgame.StartGame(MainLoop);
	
	return 0;
}