#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <functional>
#include <iostream>
#include <list>
#include <string>
#include "Player.h"
#include "Map.h"
#include "InteractableObject.h"

typedef enum{
	MOUSE_BUTTON = 1,
	KEYBOARD_KEY = 2,
} InputType;

class Game // Main game class
{
public:
	Game();	 // Created
	~Game(); // Destroyed

	Player Player; // All the settings for the player
	Map Map;	   // All the settings for the map

	void StartGame(std::function<int()> mainLoop); // Main function that will start the game and open a window
	void CloseGame();							   // End the game

	void AddInteractableObject(InteractableObject Object); // Adds an InteractableObject to the list
	void LoadInteractableObjecsFromXML(std::string Path);  // Bulk load InteractableObjects from an xml file
	InputType InteractInputType = MOUSE_BUTTON;
	KeyboardKey InteractKey = KEY_Q;
	MouseButton InteractMouseButton = MOUSE_BUTTON_LEFT;
private:
	void DetectInput();									 // Function to detect key presses such as esc or f11
	std::vector<InteractableObject> InteractableObjects; // List of interactableObject
};

#endif