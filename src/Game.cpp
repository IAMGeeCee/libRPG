#include "Game.h"
#include <raylib.h>
#include <functional>
#include <raymath.h>


using namespace std;

Game::Game()
{
  // Constructer

  // Set up game
  Game::player = Player();
}

Game::~Game() {}

void Game::StartGame(std::function<int()> mainLoop)
{
	// Main game starting point

	// Set up window
	InitWindow(GetScreenHeight(), GetScreenWidth(), "LibRPG (dev) Game");
	ToggleFullscreen();
	SetConfigFlags(FLAG_VSYNC_HINT); // Enable VSYNC
	SetTraceLogLevel(LOG_WARNING);	 // Print less to console
	//SetTargetFPS(60);

	// Camera
	Camera2D camera = {0};
	camera.target = player.position;
	camera.offset = {static_cast<float>(GetScreenWidth()) / 2,
					 static_cast<float>(GetScreenHeight() / 2)};
	camera.rotation = 0.0f;
	camera.zoom = Game::player.cameraZoom;

	while (!WindowShouldClose())
	{
		float deltaTime = GetFrameTime();

		// Begin drawing
		BeginDrawing();
		ClearBackground(RAYWHITE); // Clear the screen to stop overlap

		// Camera
		camera.target = player.position;
		camera.offset = {static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2};
		camera.rotation = Game::player.cameraRotation;
		camera.zoom = Game::player.cameraZoom;
		BeginMode2D(camera);

		// Do the users logic
		int mainLoopReturn = mainLoop();
		//map.UnloadTextures();

		EndMode2D();

		// Any gui must not be drawn in a Mode2D otherwise it will move with the camera
		DrawFPS(50, 50);
		// DrawText((std::to_string(static_cast<int>(player.position.x) / map.tileWidth) + ',' + std::to_string(static_cast<int>(player.position.y) / map.tileHeight)).c_str(), 50, 100, 25, GREEN);

		EndDrawing();
	}

	cout << map.IsTileWalkable(20,20) << endl;

	map.UnloadTileTextures();
	player.UnloadTexture();
	// Game ended
	CloseWindow();

	// Deconstructer happens at this point
}
