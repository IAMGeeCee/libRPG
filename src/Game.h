#include <raylib.h>
#include <functional>
#include <iostream>
#include "Player.h"
#include "Map.h"

using namespace std;

class Game {
public:
	Game();
	~Game();
	void StartGame(std::function<int()> mainLoop);
	Player player;
  	Map map;  
private:
	float deltaTime;
};
