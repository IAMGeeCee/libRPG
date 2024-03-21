#include "Game.h"
#include <raylib.h>
#include <iostream>
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
		
	
	while(!WindowShouldClose())//Main loop (repeats 1 time each frame i think)
	{	
		ClearBackground(BLACK);//Reload window so content is not drawn on top of existing content
		
		//End user defined logic runs
		int mainLoopReturn = mainLoop();
	}
	
	//Game ended
	CloseWindow();

	//Deconstructer happens at this point
}
