#include "Game.h"
#include <raylib.h>

Game::Game(){
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
	}

	CloseWindow();
}

Game::~Game(){}
