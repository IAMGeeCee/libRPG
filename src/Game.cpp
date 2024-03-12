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
		//Main loop
		BeginDrawing();
		ClearBackground(BLACK);

		DrawFPS(50,50);

		EndDrawing();



		//TODO: Engine users game logic here
		//Maybe somehow pass it in the Game class as a function that i can run here.

		int mainLoopReturn = mainLoop();
	}

	CloseWindow();
}

Game::~Game(){}
