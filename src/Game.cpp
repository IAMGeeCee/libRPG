#include "Game.h"
#include <raylib.h>
#include <iostream>
#include <functional>
#include <raymath.h>

using namespace std;

Game::Game(){
	//Set up game
	Game::player = Player();
}

Game::~Game(){}

void Game::StartGame(std::function<int()> mainLoop)
{
	//Set up window
	InitWindow(GetScreenHeight(), GetScreenWidth(), "test game");
	SetConfigFlags(FLAG_VSYNC_HINT);
	ToggleFullscreen();
	SetTraceLogLevel(LOG_WARNING);
		
	
	while(!WindowShouldClose())
	{	
		ClearBackground(BLACK);

		int mainLoopReturn = mainLoop();
	}

	CloseWindow();


}
