#include <raylib.h>
#include <functional>
#include <iostream>

using namespace std;

class Game {
public:
	Game(std::function<int()> mainLoop);
	~Game();

private:
	
};
