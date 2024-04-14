#include "Game.h"
#include <raylib.h>
#include <functional>
#include <raymath.h>

using namespace std;

Game::Game(){
	//Constructer


	//Set up game
	Game::player = Player();
}

Game::~Game(){}

void Game::StartGame(std::function<int()> mainLoop)
{
	//Main game starting point

	//Set up window
	InitWindow(GetScreenHeight(), GetScreenWidth(), "test game");
	SetConfigFlags(FLAG_VSYNC_HINT); //Set FPS to vsync
	ToggleFullscreen();
	SetTraceLogLevel(LOG_WARNING); //Less rubbish in console
  
  //Games camera
  //TODO:Make this customisable
  Camera2D camera = {0};
  camera.target = player.position;
  camera.offset = {static_cast<float>(GetScreenWidth()) / 2,
                   static_cast<float>(GetScreenHeight() / 2)};
  camera.rotation = 0.0f;
  camera.zoom = Game::player.cameraZoom;

	while(!WindowShouldClose())//Main loop (repeats 1 time each frame i think)
	{	
    BeginDrawing();
		ClearBackground(RAYWHITE);//Reload window so content is not drawn on top of existing content
	  camera.target = player.position;  
  
    BeginMode2D(camera);
		//End user defined logic runs
		int mainLoopReturn = mainLoop();
    EndMode2D();
    
    //Any gui must not be drawn in a Mode2D otherwise it will move with the camera
    DrawFPS(50,50);

    EndDrawing();
	}
	
	//Game ended
	CloseWindow();

	//Deconstructer happens at this point
}
