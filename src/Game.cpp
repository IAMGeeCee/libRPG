#include "Game.h"
#include <raylib.h>
#include <raymath.h>
#include <functional>

Game::Game() // Constructor
{
	// Set up game
	Game::Player = Player::Player();
	Game::Map = Map::Map();
}

Game::~Game() {} // Destructor

void Game::StartGame(std::function<int()> MainLoop) // Main game starting point
{
	InitWindow(1000, 1000, "libRPG (dev) Game"); // Set up a window
	SetTraceLogLevel(LOG_WARNING);				 // Print less to console

	Camera2D Camera = {0}; // Create a Camera

	while (!WindowShouldClose())
	{
		DeltaTime = GetFrameTime(); // Get frame time
		DetectKeys();

		BeginDrawing();
		ClearBackground(RAYWHITE); // Clear the screen to stop overlap

		InteractableObjects.clear();

		// Camera
		Camera.target = Player.Position;
		Camera.offset = {static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2};
		Camera.rotation = Game::Player.CameraRotation;
		Camera.zoom = Game::Player.CameraZoom;

		Player.MapPointer = &Map; // Hand the map to the Player class so it can interact with it

		BeginMode2D(Camera);

		int MainLoopReturn = MainLoop(); // Do any of the user's logic and drawing

		Map.LoadTileMap(); // Load the tileMap

		//RENDER ANYTHING TO BE DRAWN ON TOP OF MAP HERE:
		for (int i = 0; i < InteractableObjects.size(); i++)
		{
			InteractableObjects[i].DrawInteractableObject();
		}
		

		Player.DrawPlayer(); //Draw the player

		EndMode2D();

		// TODO: This is where GUI would be drawn
		// Any GUI must not be drawn in a Mode2D otherwise it will move with the camera

		DrawFPS(50, 50);
		DrawText((std::to_string(static_cast<int>(Player.Position.x) / Map.TileWidth) + ',' + std::to_string(static_cast<int>(Player.Position.y) / Map.TileHeight)).c_str(), 50, 100, 25, GREEN);

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
	Player.UnloadPlayerTexture();
	CloseWindow();
}
