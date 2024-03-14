#include "Game.h"
#include <raylib.h>
#include <iostream>
#include <functional>

using namespace std;

Game::Game(std::function<int()> mainLoop){
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

Game::~Game(){}
