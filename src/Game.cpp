#include "Game.h"
#include <raylib.h>
#include <functional>
#include <raymath.h>


using namespace std;

Game::Game()
{
	// Constructer
	deltaTime = GetFrameTime();

	// Set up game
	Game::player = Player();
}

Game::~Game() {}

void Game::StartGame(std::function<int()> mainLoop)
{
	// Main game starting point
	deltaTime = GetFrameTime();

	// Set up window
	InitWindow(1000, 1000, "LibRPG (dev) Game");

	SetTraceLogLevel(LOG_WARNING);	 // Print less to console

	// Camera
	Camera2D camera = { 0 };
	camera.target = player.position;
	camera.offset = { static_cast<float>(GetScreenWidth()) / 2,
					 static_cast<float>(GetScreenHeight() / 2) };
	camera.rotation = 0.0f;
	camera.zoom = Game::player.cameraZoom;

	while (!WindowShouldClose())
	{
		float deltaTime = GetFrameTime();
		DetectKeys();

		// Begin drawing
		BeginDrawing();
		ClearBackground(RAYWHITE); // Clear the screen to stop overlap

		// Camera
		camera.target = player.position;
		camera.offset = { static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2 };
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

	CloseGame();

	// Deconstructer happens at this point
}

void Game::DetectKeys() {
	if (IsKeyPressed(KEY_F11)) {
		ToggleBorderlessWindowed();
	}

	if (IsKeyPressed(KEY_ESCAPE)) {
		CloseGame();
	}
}

void Game::CloseGame() {
	map.UnloadTileTextures();
	player.UnloadTexture();
	// Game ended
	CloseWindow();
}