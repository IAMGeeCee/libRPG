#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <functional>
#include <iostream>
#include <list>
#include "Player.h"
#include "Map.h"
#include "InteractableObject.h"

class Game // Main game class
{
public:
	Game();	 // Created
	~Game(); // Destroyed

	void StartGame(std::function<int()> mainLoop); // Main function that will start the game and open a window
	void CloseGame();							   // End the game
	Player Player;								   // All the settings for the player
	Map Map;									   // All the settings for the map
	std::list<InteractableObject> InteractableObjects;
private:
	float DeltaTime;		  // Get the frame time
	void DetectKeys();		  // Function to detect key presses such as esc or f11
};

#endif