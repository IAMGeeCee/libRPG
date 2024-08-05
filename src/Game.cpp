#include "Game.h"
#include "../external/rapidxml-1.13/rapidxml.hpp"
#include <raylib.h>
#include <raymath.h>
#include <functional>
#include <string>
#include <list>
#include <ostream>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

Game::Game() // Constructor
{
	// Set up game
	Game::Player = Player::Player();
	Game::Map = Map::Map();
}

Game::~Game() {} // Destructor

void Game::StartGame(std::function<int()> MainLoop) // Main game starting point
{
	InitWindow(GetScreenWidth(), GetScreenHeight(), "libRPG (dev) Game"); // Set up a window
	SetTraceLogLevel(LOG_WARNING);										  // Print less to console
	SetConfigFlags(FLAG_VSYNC_HINT);
	ToggleFullscreen();
	Camera2D Camera = {0}; // Create a Camera

	while (!WindowShouldClose())
	{
		// Reset
		DetectInput();
		BeginDrawing();
		ClearBackground(RAYWHITE); // Clear the screen to stop overlap
		InteractableObjects.clear();

		// Camera
		Camera.target = Player.Position;
		Camera.offset = {static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2};
		Camera.rotation = Game::Player.CameraRotation;
		Camera.zoom = Game::Player.CameraZoom;

		Player.MapPointer = &Map; // Hand the map to the Player class so it can interact with it
		Player.InteractableObjectListPointer = &InteractableObjects;

		BeginMode2D(Camera);

		int MainLoopReturn = MainLoop(); // Do any of the user's logic and drawing

		Map.LoadTileMap(); // Load the tileMap

		for (int i = 0; i < InteractableObjects.size(); i++) // Load interactableObjects
		{
			InteractableObjects[i].DrawInteractableObject();
		}

		Player.DrawPlayer(); // Draw the player

		EndMode2D();

		// TODO: This is where GUI would be drawn
		// Any GUI must not be drawn in a Mode2D otherwise it will move with the camera

		DrawFPS(50, 50);
		DrawText((std::to_string(static_cast<int>(Player.Position.x) / Map.TileWidth) + ',' + std::to_string(static_cast<int>(Player.Position.y) / Map.TileHeight)).c_str(), 50, 100, 25, GREEN);

		EndDrawing();
	}

	CloseGame(); // Game has ended
}

void Game::DetectInput() // Detect other key presses
{
	if (IsKeyPressed(KEY_F11))
	{
		ToggleFullscreen();
	}

	if (IsKeyPressed(KEY_ESCAPE))
	{
		CloseGame();
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		if (Player.GetCanInteract())
		{
			if (Player.ClosestInteractableObject->InteractAction)
			{
				Player.ClosestInteractableObject->InteractAction();
			}
		}
	}
}

void Game::AddInteractableObject(InteractableObject Object)
{
	Object.Position.x = Object.Position.x * Map.TileWidth;
	Object.Position.y = Object.Position.y * Map.TileHeight;
	InteractableObjects.push_back(Object);
}

void Game::LoadInteractableObjecsFromXML(std::string Path)
{
	rapidxml::xml_document<> ObjectsXML;
	std::ifstream File(Path);
	if (!File.is_open())
	{
		std::cerr << "Can't read XML file: " << Path << std::endl;
		return;
	}

	std::stringstream Buffer;
	Buffer << File.rdbuf();
	std::string FileContents = Buffer.str();
	File.close();
	ObjectsXML.parse<0>(&FileContents[0]);

	rapidxml::xml_node<> *ObjectsNode = ObjectsXML.first_node();
	if (!ObjectsNode)
	{
		std::cerr << "Invalid Tileset XML format" << std::endl;
		return;
	}

	for (rapidxml::xml_node<> *Child = ObjectsNode->first_node("Object"); Child != nullptr; Child = Child->next_sibling("Object"))
	{
		InteractableObject Object;

		Object.Position.x = std::stoi(Child->first_node("X")->value()) * Map.TileWidth;
		Object.Position.y = std::stoi(Child->first_node("Y")->value()) * Map.TileHeight;
		Object.Size.x = std::stoi(Child->first_node("Width")->value());
		Object.Size.y = std::stoi(Child->first_node("Height")->value());
		Object.TextureLocation = Child->first_node("Path")->value();

		AddInteractableObject(Object);
	}
}

void Game::CloseGame() // Game has ended, bye 👋
{
	Map.UnloadTileTextures();
	Player.UnloadPlayerTexture();
	CloseWindow();
}
