#include <raylib.h>
#include <functional>
#include <iostream>
#include "Player.h"

using namespace std;

class Game {
public:
	Game(std::function<int()> mainLoop);
	~Game();
	Player player;

private:
	
};
