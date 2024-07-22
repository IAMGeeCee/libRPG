#include "Game.h"
#include <raylib.h>
#include <raymath.h>
#include <functional>

Game::Game() // Constructer
{
	// Set up game
	Game::Player = Player::Player();
	Game::Map = Map::Map();
}

Game::~Game() {} // Deconstructer

void Game::StartGame(std::function<int()> mainLoop) // Main game starting point
{
	InitWindow(1000, 1000, "LibRPG (dev) Game"); // Set up a window
	SetTraceLogLevel(LOG_WARNING);				 // Print less to console

	Camera2D camera = {0}; // Create a Camera

	while (!WindowShouldClose())
	{
		deltaTime = GetFrameTime(); // Get frame time
		DetectKeys();

		BeginDrawing();
		ClearBackground(RAYWHITE); // Clear the screen to stop overlap

		// Camera
		camera.target = Player.position;
		camera.offset = {static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2};
		camera.rotation = Game::Player.cameraRotation;
		camera.zoom = Game::Player.cameraZoom;
		
		Player.map = &Map; // Hand the map to the Player class so it can interact with it

		BeginMode2D(camera);		

		int mainLoopReturn = mainLoop(); // Do any of the users logic and drawing

		EndMode2D();

		// TODO: This is where GUI would be drawn
		// Any gui must not be drawn in a Mode2D otherwise it will move with the camera
		
		DrawFPS(50, 50);
		DrawText((std::to_string(static_cast<int>(Player.position.x) / Map.tileWidth) + ',' + std::to_string(static_cast<int>(Player.position.y) / Map.tileHeight)).c_str(), 50, 100, 25, GREEN);

		EndDrawing();
	}

	CloseGame(); // Game has ended
}

void Game::DetectKeys() // Detect other key presses
{
	if (IsKeyPressed(KEY_F11))
	{
		ToggleBorderlessWindowed();
	}

	if (IsKeyPressed(KEY_ESCAPE))
	{
		CloseGame();
	}
}

void Game::CloseGame() // Game has ended, bye 👋
{
	Map.UnloadTileTextures();
	Player.UnloadTexture();
	CloseWindow();
}